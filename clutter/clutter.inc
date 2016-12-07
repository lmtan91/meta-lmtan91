SUMMARY = "Graphics library for creating hardware-accelerated user interfaces"
HOMEPAGE = "http://www.clutter-project.org/"
LICENSE = "LGPLv2.1+"

inherit clutter 

DEPENDS = "pango glib-2.0 json-glib atk udev cogl-1.0 "
# PACKAGE_BEFORE_PN += "${PN}-examples"
# AUTOTOOLS_AUXDIR = "${S}/build"
PACKAGES = "${PN}" 

# EDEPENDS_X11 = "virtual/libx11 libxi libxfixes"
EDEPENDS_X11 = "virtual/libx11 libxi "
EDEPENDS_GLX = "virtual/libgl"
EDEPENDS_EGL = "virtual/egl"
EDEPENDS_WAYLAND = "wayland libxkbcommon gdk-pixbuf"

EDEPENDS_EVDEV = "libxkbcommon"
ERDEPENDS_EVDEV = "xkeyboard-config"

# Disable pretty much everything, override in platform specific set up

do_configure() {
	./configure --prefix=/usr --with-flavour=eglnative \
			--host=arm-poky-linux-gnueabi \
			--with-json=internal \
			--with-gles=2.0	\
			--with-x=no	\
			--with-imagebackend=internal \
}

do_install_append() {
	chrpath -d ${D}${libdir}/libclutter-eglnative-0.8.so.0.808.0
}

PACKAGECONFIG[x11] = "--enable-x11-backend,--disable-x11-backend,${EDEPENDS_X11}"
PACKAGECONFIG[glx] = ",,${EDEPENDS_X11} ${EDEPENDS_GLX}"
PACKAGECONFIG[egl] = "--enable-egl-backend,--disable-egl-backend,${EDEPENDS_EGL}"
PACKAGECONFIG[evdev] = "--enable-evdev-input,--disable-evdev-input,${EDEPENDS_EVDEV},${ERDEPENDS_EVDEV}"
PACKAGECONFIG[wayland] = "--enable-wayland-backend,--disable-wayland-backend,${EDEPENDS_WAYLAND}"
PACKAGECONFIG[wayland-compositor] = "--enable-wayland-compositor,--disable-wayland-compositor,wayland"


INSANE_SKIP_${PN} = "installed-vs-shipped dev-so"

FILES_${PN} = "${libdir}/lib*.so* \
		${includedir}/*/*/*.h \
		${includedir}/*/*/*/*.h \
"		 
FILES_${PN}-dbg += "${libdir}/.debug"

