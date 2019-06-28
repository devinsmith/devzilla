# Makefile for libimg

.PHONY: all clean

# no ipng support because it's based on old png.

SRCS = color.cpp colormap.cpp dither.cpp gif.cpp if.cpp ilclient.cpp \
			 ilNetReader.cpp il_util.cpp jpeg.cpp scale.cpp xbm.cpp xpcompat.cpp

CXX? = g++
AR? = ar
RM = rm -f

DEFINES = -DSTANDALONE_IMAGE_LIB

LIB = libimg
SHARED_LIB = $(LIB).so
STATIC_LIB = $(LIB).a

ifeq ($(OS),Windows_NT)
	CC = gcc
	SHARED_LIB = $(LIB).dll
	LD_FLAGS += -L../../../nsprpub/lib/libc/src -L../../../nsprpub/pr/src \
		-L../../libutil/src \
		-lnsprc -lnspr -lmozutil -lwsock32 -lwinmm
else
	DEFINES += -D_PR_PTHREADS -DLINUX
endif

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

INCLUDES = -I../public -I../../../nsprpub/pr/include \
					 -I../../../nsprpub/lib/libc/include -I../../../include \
					 -I../../../xpcom/public -I../../libutil/public -I../../../nsprpub/pr/include/md
CFLAGS = -Wall -O2 -fpic


all: $(SHARED_LIB)

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared -o $@ $(OBJS) $(LD_FLAGS) -ljpeg

$(STATIC_LIB): $(OBJS)
	$(RM) $(STATIC_LIB)
	$(AR) cru $(STATIC_LIB) $(OBJS)
	ranlib $(STATIC_LIB)

.cpp.o:
	$(CXX) $(CFLAGS) $(DEFINES) $(INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(STATIC_LIB)
	$(RM) $(SHARED_LIB)

# Include automatically generated dependency files
-include $(DEPS)
