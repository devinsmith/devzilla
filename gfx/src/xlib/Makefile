# Makefile for libgfxplatform

.PHONY: all clean

SRCS = nsDeviceContextSpecFactoryX.cpp nsDeviceContextXlib.cpp \
			 nsFontMetricsXlib.cpp nsImageXlib.cpp nsRenderingContextXlib.cpp \
			 nsDeviceContextSpecXlib.cpp nsDrawingSurfaceXlib.cpp \
			 nsGfxFactoryXlib.cpp nsRegionXlib.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

INCLUDES = -I../../../nsprpub/lib/libc/include -I../../../nsprpub/pr/include \
					 -I../../../xpcom/public -I../../public -I. -I.. \
					 -I../../../base/src -I../../../include -I../../../nsprpub/lib/ds \
					 -I../../../widget/public -I../../../dom/public \
					 -I../../../modules/libimg/public -I../../../modules/libutil/public \
					 -I../../../view/public
CFLAGS = -Wall -g3 -fpic

CC? = gcc
AR? = ar
RM = rm -f

ifeq ($(OS),Windows_NT)
	CC = gcc
	RM = del /Q 2>NUL
endif

LIB = libgfxplatform
STATIC_LIB = $(LIB).a

all: $(STATIC_LIB)

$(STATIC_LIB): $(OBJS)
	$(RM) $(STATIC_LIB)
	$(AR) cru $(STATIC_LIB) $(OBJS)
	ranlib $(STATIC_LIB)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDES) -fpic -MMD -MP -MT $@ -o $@ -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(STATIC_LIB)

# Include automatically generated dependency files
-include $(DEPS)
