#include <webkitgtk-4.1/webkit2/webkit-web-extension.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "resources/gschema.h"

int sock;
GtkWidget *settings;
GtkWidget *enabled;
JSCContext *js_context;
const gchar *zap_js;
const gchar *block_js;
const gchar *config_dir;

/**
 * WebKitGTK API callback function that gets called when a new request is about to be sent to the server ('send-request' signal). It's used to catch potentially unwanted requests and block them if the filtering server deems them unwanted.
 */
static gboolean web_page_send_request(WebKitWebPage *web_page, WebKitURIRequest *request, WebKitURIResponse *redirected_response, gpointer user_data)
{
    if (!gtk_switch_get_active(GTK_SWITCH(enabled)))
        return FALSE;

    const char *request_uri = webkit_uri_request_get_uri(request);
    const char *page_uri = webkit_web_page_get_uri(web_page);

    gchar *path;
    g_uri_split(request_uri, G_URI_FLAGS_NONE, NULL, NULL, NULL, NULL, &path, NULL, NULL, NULL);

    const gchar *res_type;
    if (g_str_has_suffix(path, ".js"))
        res_type = "script";
    else if (g_str_has_suffix(path, ".css"))
        res_type = "stylesheet";
    else if (g_str_has_suffix(path, ".jpg") || g_str_has_suffix(path, ".png") || g_str_has_suffix(path, ".svg") || g_str_has_suffix(path, ".gif"))
        res_type = "image";
    else if (g_str_has_suffix(path, ".ttf") || g_str_has_suffix(path, ".otf") || g_str_has_suffix(path, ".woff") || g_str_has_suffix(path, ".woff2"))
        res_type = "font";
    else
        res_type = "other";

    g_free(path);

    gchar *req = g_strdup_printf("n %s %s %s\n", request_uri, page_uri, res_type);
    write(sock, req, strlen(req));
    g_free(req);
    gchar buffer[1] = {0};
    read(sock, buffer, 1);
    return buffer[0] == '1';
}

/**
 * WebKitGTK API callback function that gets called when the DOM document of a webpage has been loaded (signal 'document-loaded'). Used for opening the settings window, but also for getting lists of ids and classes that are present on the given webpage which are sent to the server for filtering. The resulting CSS rule is also injected into the webpage through this function.
 */
static void document_loaded_callback(WebKitWebPage *web_page, gpointer user_data)
{
    const gchar *uri = webkit_web_page_get_uri(web_page);

    if (g_str_has_suffix(uri, "blockit://settings") || g_str_has_suffix(uri, "blockit//settings"))
        gtk_widget_show(settings);

    if (!gtk_switch_get_active(GTK_SWITCH(enabled)))
        return;

    JSCValue *classes = jsc_context_evaluate(js_context, "Array.from(new Set([].concat.apply([], Array.from(document.getElementsByTagName('*')).map(elem => Array.from(elem.classList))))).join('\t')", -1);
    JSCValue *ids = jsc_context_evaluate(js_context, "Array.from(document.getElementsByTagName('*')).map(elem => elem.id).filter(elem => elem).join('\t')", -1);
    gchar *req = g_strdup_printf("c %s %s %s\n", uri, jsc_value_to_string(ids), jsc_value_to_string(classes));
    write(sock, req, strlen(req));
    g_free(req);

    GString *res = g_string_new("");
    char *end = NULL;

    do
    {
        gchar buffer[1024] = {0};
        read(sock, buffer, 1023);
        end = strchr(buffer, '\n');
        if (end)
            *end = 0;
        g_string_append(res, buffer);
    } while (!end);

    if (res->len > 1)
    {
        g_string_prepend(res, "var link = document.createElement('link');"
                            "link.rel = 'stylesheet';"
                            "link.href = 'a';"
                            "document.head.appendChild(link);"
                            "window.onload = function () { link.sheet.insertRule(`");
        g_string_append(res, "`); }");
        jsc_context_evaluate(js_context, res->str, -1);
        g_string_free(res, TRUE);
    }
}

/**
 * WebKitGTK API callback function that gets called when a new message is sent to the Javascript console ('console-message-sent' signal). Used for catching a specific message from the 'block element' interface that specifies the filter rule that should be added to the custom filter lists file for permanent blocking.
 */
static void console_message_sent_callback(WebKitWebPage *web_page, WebKitConsoleMessage *console_message, gpointer user_data)
{
    const gchar *msg = webkit_console_message_get_text(console_message);

    if (g_str_has_prefix(msg, "blockit "))
    {
        const char *page_uri = webkit_web_page_get_uri(web_page);

        gchar *path;
        g_uri_split(page_uri, G_URI_FLAGS_NONE, NULL, NULL, &path, NULL, NULL, NULL, NULL, NULL);

        gchar *uri = g_strconcat("file:///", g_get_user_config_dir(), "/ars/lists/custom", NULL);
        GFile *file = g_file_new_for_uri(uri);
        g_free(uri);
        GFileOutputStream *stream = g_file_append_to(file, G_FILE_CREATE_NONE, NULL, NULL);
        gchar *buf = g_strconcat("\n", path, msg + 8, "\n", NULL);
        g_output_stream_write(G_OUTPUT_STREAM(stream), buf, strlen(buf), NULL, NULL);
        g_free(buf);
    }
}

/**
 * WebKitGTK API callback function that gets called every time a WebKitWebPage is created ('page-created' signal). Used for getting the main frame and Javascript context of the webpage. Also for connecting to other signals - 'send-request', 'document-loaded' and 'console-message-sent'.
 */
static void web_page_created_callback(WebKitWebExtension *extension, WebKitWebPage *web_page, gpointer user_data)
{
    WebKitFrame *frame = webkit_web_page_get_main_frame(web_page);
    js_context = webkit_frame_get_js_context(frame);

    g_signal_connect(web_page, "send-request", G_CALLBACK(web_page_send_request), NULL);
    g_signal_connect(web_page, "document-loaded", G_CALLBACK(document_loaded_callback), NULL);
    g_signal_connect(web_page, "console-message-sent", G_CALLBACK(console_message_sent_callback), NULL);
}

/**
 * Entry point of the extension. Used for connecting to the server socket. If it's not running, it will try to automatically start it if possible.
 */
G_MODULE_EXPORT void webkit_web_extension_initialize(WebKitWebExtension *extension)
{
    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    memset(addr.sun_path, 0, sizeof(addr.sun_path));
    strcpy(addr.sun_path, "/tmp/ars");

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        gchar *argv[] = {"adblock-rust-server", NULL};
        gint out;

        if (!g_spawn_async_with_pipes(NULL, argv, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, NULL, &out, NULL, NULL))
        {
            GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_NONE, "adblock-rust-server could not be started");
            gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "adblock-rust-server isn't running and couldn't be started.");
            gtk_widget_show(dialog);
            return;
        }

        GIOChannel *out_chan = g_io_channel_unix_new(out);
        gchar *line;
        g_io_channel_read_line(out_chan, &line, NULL, NULL, NULL);
        g_free(line);
        g_io_channel_unref(out_chan);
        connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    }

    config_dir = g_get_user_config_dir();

    GBytes *bytes = g_resources_lookup_data("/resources/scripts/zap.js", G_RESOURCE_LOOKUP_FLAGS_NONE, NULL);
    zap_js = g_bytes_get_data(bytes, NULL);

    bytes = g_resources_lookup_data("/resources/scripts/block.js", G_RESOURCE_LOOKUP_FLAGS_NONE, NULL);
    block_js = g_bytes_get_data(bytes, NULL);

    GtkBuilder *builder = gtk_builder_new_from_resource("/resources/gui.glade");
    gtk_builder_connect_signals(builder, NULL);
    settings = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    enabled = GTK_WIDGET(gtk_builder_get_object(builder, "enabled"));

    g_signal_connect(extension, "page-created", G_CALLBACK(web_page_created_callback), NULL);
}
