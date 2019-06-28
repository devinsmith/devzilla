# Makefile for libraptorgfx

.PHONY: all clean

SRCS = nsColor.cpp nsColorNames.cpp nsColorNamesRGB.cpp nsFont.cpp \
			 nsRect.cpp nsDeviceContext.cpp \
			 nsTransform2D.cpp nsImageRenderer.cpp nsImageRequest.cpp 
#			 nsImageNetContextSync.cpp

MOTIF = motif/nsFontMetricsMotif.cpp motif/nsGfxFactoryMotif.cpp \
			 motif/nsDeviceContextMotif.cpp motif/nsRenderingContextMotif.cpp \
			 motif/nsImageMotif.cpp motif/nsRegionMotif.cpp

OBJS = $(SRCS:.cpp=.o) $(MOTIF:.cpp=.o)
DEPS = $(SRCS:.cpp=.d) $(MOTIF:.cpp=.d)

INCLUDES = -I../../nsprpub/lib/libc/include -I../../nsprpub/pr/include \
					 -I../../xpcom/public -I../public -I. -I../../base/src \
					 -I../../include -I../../nsprpub/lib/ds -I../../widget/public \
					 -I../../modules/libimg/public -I../../modules/libutil/public \
					 -I../../view/public
CFLAGS = -Wall -g3

CC? = gcc
AR? = ar
RM = rm -f

ifeq ($(OS),Windows_NT)
	CC = gcc
	RM = del /Q 2>NUL
endif

LIB = libgfxmotif
SHARED_LIB = $(LIB).so
STATIC_LIB = $(LIB).a

all: $(SHARED_LIB)

$(STATIC_LIB): $(OBJS)
	$(RM) $(STATIC_LIB)
	$(AR) cru $(STATIC_LIB) $(OBJS)
	ranlib $(STATIC_LIB)

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared -o $@ $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDES) -fpic -MMD -MP -MT $@ -o $@ -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(SHARED_LIB)

# Include automatically generated dependency files
-include $(DEPS)
