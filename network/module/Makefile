# Makefile for libmoznetlib

.PHONY: all clean

SRCS = nsLoadAttribs.cpp nsHttpUrl.cpp nsHttpURLFactory.cpp \
			 nsNetFactory.cpp nsNetService.cpp nsNetThread.cpp \
			 nsStubContext.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

INCLUDES = -I../../nsprpub/lib/libc/include -I../../nsprpub/pr/include \
					 -I../../xpcom/public -I../public -I. -I../../base/src \
					 -I../../include -I../../nsprpub/lib/ds -I../../widget/public \
					 -I../../modules/libimg/public -I../../modules/libutil/public \
					 -I../../view/public -I../../modules/libpref/public \
					 -I../../js/src -I../protocol/http -I../main -I../public \
					 -I../../lib/liblayer/include -I../protocol/sockstub \
					 -I../protocol/file -I../protocol/ftp -I../protocol/about \
					 -I../protocol/gopher -I../protocol/remote -I../cnvts \
					 -I../cache
DEFINES= -DNETSCAPE
CFLAGS = -Wall -g3

CC? = gcc
AR? = ar
RM = rm -f

LDFLAGS = -L../cnvts -L../protocol/file -L../protocol/http -lnetcnvts \
					-lfileurl -lhttpurl

LIB = libmoznetlib
SHARED_LIB = $(LIB).so
STATIC_LIB = $(LIB).a

ifeq ($(OS),Windows_NT)
	CC = gcc
	SHARED_LIB = $(LIB).dll
	DEFINES += -D_IMPL_NS_NET -DXP_PC -DXP_WIN
	LDFLAGS += -Wl,--out-implib,$(LIB).a -lwsock32 -lwinmm
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
