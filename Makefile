.POSIX:
.SUFFIXES:

include config.mk

DWLCPPFLAGS = -I. -Iinclude -Ibuild -DWLR_USE_UNSTABLE -D_POSIX_C_SOURCE=200809L \
	-DVERSION=\"$(VERSION)\" $(XWAYLAND)
DWLDEVCFLAGS = -O3 -march=native -fno-plt -pipe \
	-Wpedantic -Wall -Wextra -Wdeclaration-after-statement \
	-Wno-unused-parameter -Wshadow -Wunused-macros -Werror=strict-prototypes \
	-Werror=implicit -Werror=return-type -Werror=incompatible-pointer-types \
	-Wfloat-conversion

PKGS      = wayland-server xkbcommon libinput pixman-1 fcft $(XLIBS)
DWLCFLAGS = `$(PKG_CONFIG) --cflags $(PKGS)` $(WLR_INCS) $(DWLCPPFLAGS) $(CFLAGS) $(DWLDEVCFLAGS)
LDLIBS    = `$(PKG_CONFIG) --libs $(PKGS)` $(WLR_LIBS) -lm $(LIBS)

all: dwl

dwl: build/dwl.o build/util.o build/status.o
	$(CC) build/dwl.o build/util.o build/status.o $(DWLCFLAGS) $(LDFLAGS) $(LDLIBS) -o $@

build/dwl.o: src/dwl.c include/client.h config.h config.mk build/cursor-shape-v1-protocol.h \
	build/pointer-constraints-unstable-v1-protocol.h build/wlr-layer-shell-unstable-v1-protocol.h \
	build/wlr-output-power-management-unstable-v1-protocol.h build/xdg-shell-protocol.h build/tearing-control-v1-protocol.h | build
	$(CC) $(CPPFLAGS) $(DWLCFLAGS) -o $@ -c src/dwl.c

build/util.o: src/util.c include/util.h | build
	$(CC) $(CPPFLAGS) $(DWLCFLAGS) -o $@ -c src/util.c

build/status.o: status/status.c status/status.h config.h | build
	$(CC) $(CPPFLAGS) $(DWLCFLAGS) -o $@ -c status/status.c

WAYLAND_SCANNER   = `$(PKG_CONFIG) --variable=wayland_scanner wayland-scanner`
WAYLAND_PROTOCOLS = `$(PKG_CONFIG) --variable=pkgdatadir wayland-protocols`

build/cursor-shape-v1-protocol.h: | build
	$(WAYLAND_SCANNER) enum-header \
		$(WAYLAND_PROTOCOLS)/staging/cursor-shape/cursor-shape-v1.xml $@
build/pointer-constraints-unstable-v1-protocol.h: | build
	$(WAYLAND_SCANNER) enum-header \
		$(WAYLAND_PROTOCOLS)/unstable/pointer-constraints/pointer-constraints-unstable-v1.xml $@
build/wlr-layer-shell-unstable-v1-protocol.h: | build
	$(WAYLAND_SCANNER) enum-header \
		protocols/wlr-layer-shell-unstable-v1.xml $@
build/wlr-output-power-management-unstable-v1-protocol.h: | build
	$(WAYLAND_SCANNER) server-header \
		protocols/wlr-output-power-management-unstable-v1.xml $@
build/xdg-shell-protocol.h: | build
	$(WAYLAND_SCANNER) server-header \
		$(WAYLAND_PROTOCOLS)/stable/xdg-shell/xdg-shell.xml $@
build/tearing-control-v1-protocol.h: | build
	$(WAYLAND_SCANNER) server-header \
		$(WAYLAND_PROTOCOLS)/staging/tearing-control/tearing-control-v1.xml $@

build:
	mkdir -p build

config.h:
	cp config.def.h $@

clean:
	rm -rf dwl build

dist: clean
	mkdir -p dwl-$(VERSION)
	cp -R LICENSE* Makefile CHANGELOG.md README.md include \
		config.def.h config.mk protocols garbage src status dwl.desktop \
		dwl-$(VERSION)
	tar -caf dwl-$(VERSION).tar.gz dwl-$(VERSION)
	rm -rf dwl-$(VERSION)

install: dwl
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f dwl $(DESTDIR)$(PREFIX)/bin/dwl
	chmod 755 $(DESTDIR)$(PREFIX)/bin/dwl
	mkdir -p $(DESTDIR)$(MANDIR)/man1
	cp -f garbage/dwl.1 $(DESTDIR)$(MANDIR)/man1/dwl.1
	chmod 644 $(DESTDIR)$(MANDIR)/man1/dwl.1
	mkdir -p $(DESTDIR)$(DATADIR)/wayland-sessions
	cp -f dwl.desktop $(DESTDIR)$(DATADIR)/wayland-sessions/dwl.desktop
	chmod 644 $(DESTDIR)$(DATADIR)/wayland-sessions/dwl.desktop

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/dwl $(DESTDIR)$(MANDIR)/man1/dwl.1 \
		$(DESTDIR)$(DATADIR)/wayland-sessions/dwl.desktop
