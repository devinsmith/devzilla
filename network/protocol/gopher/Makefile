# Makefile for libgophurl

.PHONY: all clean

SRCS = mkgopher.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

INCLUDES = -I../../../nsprpub/lib/libc/include -I../../../nsprpub/pr/include \
					 -I../../../xpcom/public -I../public -I. -I../../../base/src \
					 -I../../../include -I../../../nsprpub/lib/ds -I../../../widget/public \
					 -I../../../modules/libimg/public -I../../../modules/libutil/public \
					 -I../../../modules/libpref/public -I../../../view/public \
					 -I../../../js/src -I../protocol/http -I../../../modules/security/freenav \
					 -I../../../lib/liblayer/include -I../../main -I../protocol/file \
					 -I../../mimetype -I../remote \
					 -I../protocol/ftp -I../protocol/about -I../protocol/gopher \
					 -I../protocol/js -I../protocol/dataurl \
					 -I../cache -I../../../network/cache -I../http
DEFINES= -DNETSCAPE -DSTANDALONE_IMAGE_LIB
CFLAGS = -Wall -g3

CC? = gcc
AR? = ar
RM = rm -f

LIB = libgophurl
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
	$(CC) -shared -o $@ $(OBJS) $(LDFLAGS)
	cp $(SHARED_LIB) ../../../xpfe/bootstrap

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
