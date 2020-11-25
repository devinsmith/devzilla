# Makefile for libraptorgfx
# It's kind of a pain to link a static archive into a shared object, so we
# just create the shared object directly.

.PHONY: all clean

# Shared components
SRCS = nsColor.cpp nsColorNames.cpp nsColorNamesRGB.cpp nsFont.cpp \
			 nsRect.cpp nsDeviceContext.cpp \
			 nsTransform2D.cpp nsImageRenderer.cpp nsImageRequest.cpp

# Platform specific components
# XLIB sources
XLIB_SRCS = xlib/nsDeviceContextSpecFactoryX.cpp xlib/nsDeviceContextXlib.cpp \
	xlib/nsFontMetricsXlib.cpp xlib/nsImageXlib.cpp xlib/nsRenderingContextXlib.cpp \
	xlib/nsDeviceContextSpecXlib.cpp xlib/nsDrawingSurfaceXlib.cpp \
	xlib/nsGfxFactoryXlib.cpp xlib/nsRegionXlib.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

TOOLKIT = xlib
#TOOLKIT = motif

INCLUDES = -I../../nsprpub/lib/libc/include -I../../nsprpub/pr/include \
					 -I../../xpcom/public -I../public -I. -I../../base/src \
					 -I../../include -I../../nsprpub/lib/ds -I../../widget/public \
					 -I../../modules/libimg/public -I../../modules/libutil/public \
					 -I../../view/public -I../../dom/public -I$(TOOLKIT)
CFLAGS = -Wall -g3

CC? = gcc
AR? = ar
RM = rm -f

DEFINES = -D_IMPL_NS_GFX
LIB = libraptorgfx
SHARED_LIB = $(LIB).so
STATIC_LIB = $(LIB).a
PLATFORM_LIB = $(TOOLKIT)/libgfxplatform.a

ifeq ($(OS),Windows_NT)
	CC = gcc
	RM = del /Q 2>NUL
	SHARED_LIB = $(LIB).dll
	TOOLKIT = win32
	DEFINES += -DXP_WIN -DXP_PC -D_IMPL_NS_GFXNONXP
	LDFLAGS += -Wl,--out-implib,$(LIB).a -L../../base/src -lraptorbase \
		-L../../modules/libimg/src -L../../modules/libutil/src \
		-L../../nsprpub/pr/src -L../../nsprpub/lib/libc/src \
		-L../../xpcom/src \
		-L../../nsprpub/lib/ds -limg -lmozutil -lplds -lnsprc \
		-lxpcom -lnspr -lwsock32
else
	CFLAGS += -fpic
	SRCS += $(XLIB_SRCS)
endif


build: $(SHARED_LIB)

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared -o $@ $(OBJS) $(LDFLAGS)
	cp $(SHARED_LIB) ../../xpfe/bootstrap

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDES) $(DEFINES) -MMD -MP -MT $@ -o $@ -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(SHARED_LIB)

# Include automatically generated dependency files
-include $(DEPS)
