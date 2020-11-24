# Makefile for libmoznetwork

.PHONY: all clean

CPP_SRCS =
SRCS = jsautocf.c jscookie.c mkautocf.c mkconect.c mkhelp.c mkfsort.c \
			 mkgeturl.c mkmessag.c mkpadpac.c mkparse.c \
			 mkselect.c mksockrw.c mksort.c mkstream.c mktrace.c mkutils.c \
			 prefetch.c

OBJS = $(SRCS:.c=.o) $(CPP_SRCS:.cpp=.o)
DEPS = $(SRCS:.c=.d) $(CPP_SRCS:.cpp=.d)

INCLUDES = -I../../nsprpub/lib/libc/include -I../../nsprpub/pr/include \
					 -I../../xpcom/public -I../public -I. -I../../base/src \
					 -I../../include -I../../nsprpub/lib/ds -I../../widget/public \
					 -I../../modules/libimg/public -I../../modules/libutil/public \
					 -I../../view/public -I../../modules/libpref/public \
					 -I../../js/src -I../protocol/http -I../../modules/security/freenav \
					 -I../../lib/liblayer/include -I../mimetype -I../cache -I../client \
					 -I../cnvts -I../util -I../../sun-java/stubs/include
DEFINES= -DNETSCAPE -DMODULAR_NETLIB -DMOZILLA_CLIENT
CFLAGS = -Wall -g3

CC? = gcc
AR? = ar
RM = rm -f

LIB = libmoznetwork
SHARED_LIB = $(LIB).so
STATIC_LIB = $(LIB).a

ifeq ($(OS),Windows_NT)
	CC = gcc
	SHARED_LIB = $(LIB).dll
	DEFINES += -D_IMPL_NS_NET -DXP_PC -DXP_WIN
	LDFLAGS = -Wl,--out-implib,$(LIB).a -lwsock32 -lwinmm
endif


all: $(SHARED_LIB)

$(STATIC_LIB): $(OBJS)
	$(RM) $(STATIC_LIB)
	$(AR) cru $(STATIC_LIB) $(OBJS)
	ranlib $(STATIC_LIB)

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared -o $@ $(OBJS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -fPIC -MMD -MP -MT $@ -o $@ -c $<

.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDES) $(DEFINES) -fPIC -MMD -MP -MT $@ -o $@ -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(SHARED_LIB)

# Include automatically generated dependency files
-include $(DEPS)
