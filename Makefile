SHELL = /bin/sh

PREFIX ?= /usr/local
LIBDIR = $(PREFIX)/lib

EXTFLAGS = -fPIC -shared
EXTLIBS = $(shell pkg-config --cflags --libs webkit2gtk-4.0 glib-2.0 gio-2.0 libsoup-3.0)

all: blockit.so

blockit.so: blockit.c resources/gschema.c resources/gschema.h
	$(CC) blockit.c resources/gschema.c -o blockit.so $(EXTFLAGS) $(EXTLIBS) $(CFLAGS)

resources/gschema.c: resources/gschema.xml resources/gui.glade resources/scripts/*
	glib-compile-resources --generate-source --target=resources/gschema.c resources/gschema.xml

resources/gschema.h: resources/gschema.xml resources/gui.glade resources/scripts/*
	glib-compile-resources --generate-header --target=resources/gschema.h resources/gschema.xml

install: all
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp -f blockit.so $(DESTDIR)$(LIBDIR)
	chmod 755 $(DESTDIR)$(LIBDIR)/blockit.so

uninstall:
	rm -f $(DESTDIR)$(LIBDIR)/blockit.so

clean:
	rm -f blockit.so resources/gschema.c resources/gschema.h

.PHONY: all install uninstall clean
