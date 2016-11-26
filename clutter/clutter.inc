SUMMARY = "Graphics library for creating hardware-accelerated user interfaces"
HOMEPAGE = "http://www.clutter-project.org/"
LICENSE = "LGPLv2.1+"

inherit clutter

DEPENDS = "pango glib-2.0 json-glib atk udev cogl-1.0 "
PACKAGE_BEFORE_PN += "${PN}-examples"
AUTOTOOLS_AUXDIR = "${S}/build"

EDEPENDS_X11 = "virtual/libx11 libxi libxfixes"
EDEPENDS_GLX = "virtual/libgl"
EDEPENDS_EGL = "virtual/egl"
EDEPENDS_WAYLAND = "wayland libxkbcommon gdk-pixbuf"

EDEPENDS_EVDEV = "libxkbcommon"
ERDEPENDS_EVDEV = "xkeyboard-config"

# Disable pretty much everything, override in platform specific set up
#EXTRA_OECONF += "\
#		 --with-gles=1.1		\
#		 --with-flavour=eglnative	\
#		 --with-imagebackend=internal	\
#		 --with-x=no			\
#		 --host=arm-poky-linux-gnueabi \
#		PKG_CONFIG="${STAGING_DIR_NATIVE}/usr/bin/pkg-config" \
#	    	"
#do_configure_prepend() {
#	sed -i 's/default_ofile=libtool/default_ofile=${host_alias}-libtool/g' configure
#}

#export ac_cv_func_malloc_0_nonnull="yes"
# --build=x86_64-linux
#			--with-libtool-sysroot="${STAGING_DIR_HOST}" 
#			PKG_CONFIG="${STAGING_DIR_NATIVE}/usr/bin/pkg-config" 
#			PKG_CONFIG_PATH="${STAGING_LIBDIR}/pkgconfig" 
#			CFLAGS="--sysroot=${STAGING_DIR_HOST} -L${STAGING_LIBDIR}" 
do_configure() {
	echo "${STAGING_DIR_HOST}"
#	sed -i 's/default_ofile=libtool/default_ofile=${host_alias}-libtool/g' configure
#	sed -i 's/$(SHELL) $(top_builddir)\/libtool/$(SHELL) $(top_builddir)\/${host_alias}-libtool/g' configure
	./configure --with-flavour=eglnative \
			--host=arm-poky-linux-gnueabi \
			--with-gles=2.0	\
			--with-x=no	\
			--with-imagebackend=internal \
}

PACKAGECONFIG[x11] = "--enable-x11-backend,--disable-x11-backend,${EDEPENDS_X11}"
PACKAGECONFIG[glx] = ",,${EDEPENDS_X11} ${EDEPENDS_GLX}"
PACKAGECONFIG[egl] = "--enable-egl-backend,--disable-egl-backend,${EDEPENDS_EGL}"
PACKAGECONFIG[evdev] = "--enable-evdev-input,--disable-evdev-input,${EDEPENDS_EVDEV},${ERDEPENDS_EVDEV}"
PACKAGECONFIG[wayland] = "--enable-wayland-backend,--disable-wayland-backend,${EDEPENDS_WAYLAND}"
PACKAGECONFIG[wayland-compositor] = "--enable-wayland-compositor,--disable-wayland-compositor,wayland"

# Default configuration, distros might want to override
PACKAGECONFIG ??= "${@base_contains('DISTRO_FEATURES', 'wayland', 'wayland', '', d)} \
                   ${@base_contains('DISTRO_FEATURES', 'x11', 'glx x11', '', d)}"

FILES_${PN}-dbg += "${libdir}/clutter/examples/.debug"
FILES_${PN}-examples = "${libdir}/clutter/examples"

INSANE_SKIP_${PN} = "installed-vs-shipped "

#do_configure_prepend() {
#	# see https://bugzilla.gnome.org/show_bug.cgi?id=661128 for this
#	touch -t 200001010000 ${S}/po/clutter-1.0.pot
#}
