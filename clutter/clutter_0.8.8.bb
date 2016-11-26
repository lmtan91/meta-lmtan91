require clutter.inc

LIC_FILES_CHKSUM = "file://COPYING;md5=7fbc338309ac38fefcd64b04bb903e34"

SRC_URI[archive.md5sum] = "20f9ab406a9fa261a0a3379eb6f43625"
SRC_URI[archive.sha256sum] = "b37404aed9a901807fd5553e7b72b4036b4c6953018751516875f7481f89dff8"

SRC_URI = "http://pkgs.fedoraproject.org/repo/pkgs/clutter/clutter-0.8.8.tar.bz2/md5/20f9ab406a9fa261a0a3379eb6f43625/clutter-0.8.8.tar.bz2;name=archive \
		file://clutter-compilation-error.patch \
		file://clutter-use-host-alias-libtool-instead.patch  \
"

