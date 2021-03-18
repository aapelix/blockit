#include <webkit2/webkit-web-extension.h>
#include <sys/socket.h>
#include <sys/un.h>

// TODO get rid of global variables
int sock;
GtkWidget *settings;
GtkWidget *enabled;
JSCContext *js_context;

static gboolean web_page_send_request(WebKitWebPage *web_page, WebKitURIRequest *request, WebKitURIResponse *redirected_response, gpointer user_data)
{
	if (!gtk_switch_get_state(GTK_SWITCH(enabled)))
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
	// server returns '1' if the resource is an ad
	return buffer[0] == '1';
}

static void document_loaded_callback(WebKitWebPage *web_page, gpointer user_data)
{
	const gchar *uri = webkit_web_page_get_uri(web_page);

	if (g_str_has_prefix(uri, "blockit://settings"))
		gtk_widget_show_all(settings);

	if (!gtk_switch_get_state(GTK_SWITCH(enabled)))
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

static void web_page_created_callback(WebKitWebExtension *extension, WebKitWebPage *web_page, gpointer user_data)
{
	WebKitFrame *frame = webkit_web_page_get_main_frame(web_page);
	js_context = webkit_frame_get_js_context(frame);

	g_signal_connect(web_page, "send-request", G_CALLBACK(web_page_send_request), NULL);
	g_signal_connect(web_page, "document-loaded", G_CALLBACK(document_loaded_callback), NULL);
}

void pick_elem(GtkWidget *widget, gpointer *data)
{
	gchar *script;
	g_file_get_contents("script.js", &script, NULL, NULL);
	jsc_context_evaluate(js_context, script, -1);
}

void hide_settings(GtkWidget *widget, gpointer *data)
{
	gtk_widget_hide(widget);
}

G_MODULE_EXPORT void webkit_web_extension_initialize(WebKitWebExtension *extension)
{
	sock = socket(AF_UNIX, SOCK_STREAM, 0);

	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	memset(addr.sun_path, 0, sizeof(addr.sun_path));
	strcpy(addr.sun_path, "/tmp/ars");

	// spawn server if it's not running
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		gchar *argv[] = {"adblock-rust-server", NULL};
		gint out;

		// "disable" extension if server can't be started
		if (!g_spawn_async_with_pipes(NULL, argv, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, NULL, &out, NULL, NULL))
			return;

		GIOChannel *out_chan = g_io_channel_unix_new(out);
		gchar *line;
		g_io_channel_read_line(out_chan, &line, NULL, NULL, NULL);
		g_free(line);
		g_io_channel_unref(out_chan);
		connect(sock, (struct sockaddr *)&addr, sizeof(addr));
	}

	g_signal_connect(extension, "page-created", G_CALLBACK(web_page_created_callback), NULL);

	GtkBuilder *builder = gtk_builder_new_from_file("gui.glade");
	settings = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	gtk_builder_connect_signals(builder, NULL);

	enabled = GTK_WIDGET(gtk_builder_get_object(builder, "enabled"));
}
