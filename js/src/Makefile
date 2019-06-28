# Makefile for libraptorbase

.PHONY: all clean

C_SRCS = jsapi.c jsarena.c jsarray.c jsatom.c jsbool.c jscntxt.c jsdate.c \
	jsdbgapi.c jsdtoa.c jsemit.c jsexn.c jsfun.c jsgc.c jshash.c jsinterp.c \
	jslock.c jslog2.c jslong.c jsmath.c jsnum.c jsobj.c jsopcode.c jsparse.c \
	jsprf.c jsregexp.c jsscan.c jsscope.c jsscript.c jsstr.c jsutil.c \
	jsxdrapi.c prmjtime.c
CPP_SRCS =

OBJS = $(C_SRCS:.c=.o) $(CPP_SRCS:.cpp=.o)
DEPS = $(C_SRCS:.c=.d) $(CPP_SRCS:.cpp=.d)

INCLUDES = -I../../nsprpub/lib/libc/include -I../../nsprpub/pr/include \
					 -I../../xpcom/public -I../public -I../../include \
					 -I../../nsprpub/lib/ds -I../../libutil/public \
					 -I../../libimg/public -I../../lib/liblayer/include \
					 -I../../security/freenav
CFLAGS = -Wall -g3 -DJS_THREADSAFE -DJS_HAVE_LONG_LONG \
				 -DEXPORT_JS_API -DNSPR_LOCK

CC? = gcc
AR? = ar
RM = rm -f


LIB = libmozjs
SHARED_LIB = $(LIB).so
STATIC_LIB = $(LIB).a
LDFLAGS =
DEFINES =

ifeq ($(OS),Windows_NT)
	CC = gcc
	SHARED_LIB = $(LIB).dll
	DEFINES += -DXP_PC
	LDFLAGS += -L../../nsprpub/pr/src -lnspr -Wl,--out-implib,$(LIB).a -lwsock32 -lwinmm
else
	DEFINES += -DXP_UNIX
endif

all: $(SHARED_LIB)

$(STATIC_LIB): $(OBJS)
	$(RM) $(STATIC_LIB)
	$(AR) cru $(STATIC_LIB) $(OBJS)
	ranlib $(STATIC_LIB)

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared -o $@ $(OBJS) $(LDFLAGS) -lm

.c.o:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -fpic -MMD -MP -MT $@ -o $@ -c $<

.cpp.o:
	$(CXX) $(CFLAGS) $(DEFINES) $(INCLUDES) -fpic -MMD -MP -MT $@ -o $@ -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(SHARED_LIB)

# Include automatically generated dependency files
-include $(DEPS)
