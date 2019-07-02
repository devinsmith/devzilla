# Makefile for libraptorgfx

.PHONY: all clean

SRCS = nsColor.cpp nsColorNames.cpp nsColorNamesRGB.cpp nsFont.cpp \
			 nsRect.cpp nsDeviceContext.cpp \
			 nsTransform2D.cpp nsImageRenderer.cpp nsImageRequest.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

INCLUDES = -I../../nsprpub/lib/libc/include -I../../nsprpub/pr/include \
					 -I../../xpcom/public -I../public -I. -I../../base/src \
					 -I../../include -I../../nsprpub/lib/ds -I../../widget/public \
					 -I../../modules/libimg/public -I../../modules/libutil/public \
					 -I../../view/public
CFLAGS = -Wall -g3

CC? = gcc
AR? = ar
RM = rm -f

TOOLKIT = motif
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
	LDFLAGS += -Wl,--out-implib,$(LIB).a -L../../base/src -lraptorbase
else
	CFLAGS += -fpic
endif


build: $(PLATFORM_LIB) $(SHARED_LIB)

$(PLATFORM_LIB):
	@(cd $(TOOLKIT) && $(MAKE))

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared -o $@ $(OBJS) $(LDFLAGS)

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
