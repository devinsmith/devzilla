# The contents of this file are subject to the Mozilla Public License
# Version 1.0 (the "License"); you may not use this file except in
# compliance with the License. You may obtain a copy of the License
# at http://www.mozilla.org/MPL/
# 
# Software distributed under the License is distributed on an "AS IS"
# basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See 
# the License for the specific language governing rights and 
# limitations under the License.
# 
# The Original Code is this file as it was released upon August 6, 1998.
#
# The Initial Developer of this code under the MPL is Christopher
# Seawood, <cls@seawood.org>.  Portions created by Christopher Seawood 
# are Copyright (C) 1998 Christopher Seawood.  All Rights Reserved.

# A netscape style .mk file for autoconf builds

USE_AUTOCONF 	= 1
MOZILLA_CLIENT	= 1
NO_MDUPDATE	= 1

MOZ_TOOLKIT	= gtk
MOZ_SECURITY 	= 
MOZ_JAVA	= 
MOZ_OJI		= 
MOZ_NETCAST	= 	
MOZ_DEBUG	= 
MOZILLA_GPROF	= 
BUILD_PROFILE	= 
MOZ_DARK	= 
MOZ_EDITOR	= 
UNIX_SKIP_ASSERTS = 
NO_UNIX_ASYNC_DNS = 
NO_SHARED_LIB	= 
NO_NETSCAPE_SHARED = 
NO_STATIC_LIB	= 
NO_NETSCAPE_STATIC = 
ENABLE_TESTS	= 
MOZ_USER_DIR	= \".mozilla\"
SMART_MAIL	= 
DOM		= 
MOZ_MAIL_COMPOSE = 
NO_UNIX_LDAP	= 1

MOZ_NATIVE_ZLIB	= 1
MOZ_NATIVE_JPEG	= 1
MOZ_NATIVE_PNG	= 1

# Should the extra CFLAGS only be added in Makefile.ins that need them? 
OS_CFLAGS	= -pipe $(DSO_CFLAGS)
OS_INCLUDES	= $(NSPR_CFLAGS) $(JPEG_CFLAGS) $(PNG_CFLAGS) $(ZLIB_CFLAGS)
OS_LIBS		=  -lfl -lnsl -lutil -lresolv -ldl -lm -lc 
DEFINES		=  -DUSE_AUTOCONF=1 -DMOZILLA_CLIENT=1 -DSTDC_HEADERS=1 -DHAVE_ST_BLKSIZE=1 -DHAVE_ST_RDEV=1 -DHAVE_TM_ZONE=1 -DHAVE_DIRENT_H=1 -DSTDC_HEADERS=1 -DHAVE_SYS_WAIT_H=1 -DTIME_WITH_SYS_TIME=1 -DHAVE_FCNTL_H=1 -DHAVE_LIMITS_H=1 -DHAVE_MALLOC_H=1 -DHAVE_PATHS_H=1 -DHAVE_STRINGS_H=1 -DHAVE_UNISTD_H=1 -DHAVE_SYS_FILE_H=1 -DHAVE_SYS_IOCTL_H=1 -DHAVE_SYS_TIME_H=1 -DHAVE_GETOPT_H=1 -DHAVE_SYS_CDEFS_H=1 -DHAVE_LIBC=1 -DHAVE_LIBM=1 -DHAVE_LIBDL=1 -DHAVE_LIBRESOLV=1 -DHAVE_LIBUTIL=1 -DHAVE_LIBNSL=1 -DHAVE_LIBFL=1 -DHAVE_ALLOCA_H=1 -DHAVE_ALLOCA=1 -DHAVE_UNISTD_H=1 -DHAVE_GETPAGESIZE=1 -DHAVE_MMAP=1 -DRETSIGTYPE=void -DHAVE_STRCOLL=1 -DHAVE_STRFTIME=1 -DHAVE_UTIME_NULL=1 -DHAVE_VPRINTF=1 -DHAVE_FTIME=1 -DHAVE_GETCWD=1 -DHAVE_GETHOSTNAME=1 -DHAVE_GETWD=1 -DHAVE_MKDIR=1 -DHAVE_MKTIME=1 -DHAVE_PUTENV=1 -DHAVE_RMDIR=1 -DHAVE_SELECT=1 -DHAVE_SOCKET=1 -DHAVE_STRCSPN=1 -DHAVE_STRDUP=1 -DHAVE_STRERROR=1 -DHAVE_STRSPN=1 -DHAVE_STRSTR=1 -DHAVE_STRTOL=1 -DHAVE_STRTOUL=1 -DHAVE_UNAME=1 -DHAVE_QSORT=1 -DHAVE_SNPRINTF=1 -DHAVE_REMAINDER=1 -DHAVE_GETTIMEOFDAY=1 -DGETTIMEOFDAY_TWO_ARGS=1 -DHAVE_SYSERRLIST=1 -DHAVE_IOS_BINARY=1 -DHAVE_IOS_BIN=1 

XCFLAGS		=  -I/usr/X11R6/include
XLDFLAGS	=  -L/usr/X11R6/lib
XLIBS		= -lXmu -lXt -lSM -lICE -lXext -lX11 

CC		= cc
CXX		= c++
GNU_CC		= 1
GNU_CXX		= 1

ACEMACS		= /usr/bin/xemacs
ACPERL		= /usr/bin/perl
ACRANLIB	= ranlib
ACWHOAMI	= /usr/bin/whoami
ACUNZIP		= /usr/bin/unzip
ACZIP		= /usr/bin/zip

OBJDIR_TAG	= _AC
OBJDIR_NAME	= .

ifdef MOZ_NATIVE_JPEG
JPEG_CFLAGS	= 
JPEG_LIBS	= -ljpeg 
JPEG_REQUIRES	=
else
JPEG_CFLAGS	= -I$(DIST)/public/jpeg
JPEG_LIBS	= $(DIST)/lib/libjpeg.a
JPEG_REQUIRES	= jpeg
endif

ifdef MOZ_NATIVE_ZLIB
ZLIB_CFLAGS	= 
ZLIB_LIBS	= -lz 
ZLIB_REQUIRES	=
else
ZLIB_CFLAGS	= -I$(DIST)/public/zlib
ZLIB_LIBS	= $(DIST)/lib/libzlib.a
ZLIB_REQUIRES	= zlib
endif

ifdef MOZ_NATIVE_PNG
PNG_CFLAGS	= 
PNG_LIBS	= -lpng 
PNG_REQUIRES	=
else
PNG_CFLAGS	= -I$(DIST)/public/png
PNG_LIBS	= $(DIST)/lib/libpng.a
PNG_REQUIRES	= png
endif

NSPR_CFLAGS	= 
NSPR_LIBS	= -lplds21 -lplc21 -lnspr21 

ifndef NO_SHARED_LIB
BUILD_UNIX_PLUGINS      = 1
DSO_CFLAGS              = -fPIC
MKSHLIB			= $(CC) $(DSO_LDOPTS)
DSO_LDOPTS		= -shared -Wl,-h -Wl,$(@:$(OBJDIR)/%.$(DLL_SUFFIX)=%.$(DLL_SUFFIX))
DLL_SUFFIX		= so
endif

GTK_CONFIG	= /usr/local/bin/gtk-config
TK_MOTIF_CFLAGS	= 
TK_MOTIF_LIBS	= 
TK_GTK_CFLAGS	= -I/usr/local/include -I/usr/X11R6/include -I/usr/local/gnome/lib/glib/include -I/usr/local/gnome/include
TK_GTK_LIBS	= -L/usr/local/lib -L/usr/X11R6/lib -lgtk -lgdk -L/usr/local/gnome/lib -rdynamic -lgmodule -lglib -ldl -lXext -lX11 -lm

MOZ_NATIVE_MAKEDEPEND	= /usr/X11R6/bin/makedepend

# XXX - these need to be cleaned up and have real checks added -cls
NGLAYOUT_PLUGINS=1 
CM_BLDTYPE=dbg 
AWT_11=1 
MODULAR_NETLIB=1 
MOZ_BITS=32 
MOZ_GOLD=1 
OS_TARGET=Linux
STANDALONE_IMAGE_LIB=1 

