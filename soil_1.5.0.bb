SECTION = "devel/chicken"
DESCRIPTION = "Lightweight, simple library for loading image files into OpenGL-friendly format."
LICENSE = "BSD"
LIC_FILES_CHKSUM = "file://soil.meta;md5=60cb16d9bec8814902a0dc3a6d75af23"
DEPENDS_append_class-cross = " virtual/libgl-native"
DEPENDS_append_class-crosssdk = " virtual/libgl-native"
DEPENDS_append_class-nativesdk = " nativesdk-virtual/libgl"
DEPENDS = " virtual/libgles2"

SRC_URI = "http://code.call-cc.org/egg-tarballs/4/soil/soil-${PV}.tar.gz"

SRC_URI[md5sum] = "bbdd87b4250bfa5d44a5f9ff318dd80d"
SRC_URI[sha256sum] = "dca76a0c9dbed797a0ea75c84db9ef81e9d3c99e6ef040e4e32e1e55be28df18"

S = "${WORKDIR}/soil-${PV}"

# inherit chicken_install

do_compile() {
	 oe_runmake -C soil-src
}

do_install() {
	oe_runmake 'DESTDIR=${D}' install
}

BBCLASSEXTEND = "cross crosssdk nativesdk"
