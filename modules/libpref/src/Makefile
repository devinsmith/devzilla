# Makefile for libpref

.PHONY: all clean

C_SRCS = prefapi.c
CPP_SRCS = nsPref.cpp

OBJS = $(C_SRCS:.c=.o) $(CPP_SRCS:.cpp=.o)
DEPS = $(C_SRCS:.c=.d) $(CPP_SRCS:.cpp=.d)

INCLUDES = -I../../../nsprpub/lib/libc/include -I../../../nsprpub/pr/include \
					 -I../../../xpcom/public -I../public -I../../../include \
					 -I../../../js/src -I../../../nsprpub/lib/ds -I../../libutil/public \
					 -I../../libimg/public -I../../../lib/liblayer/include \
					 -I../../security/freenav

CC? = gcc
AR? = ar
RM = rm -f

DEFINES = -DJS_THREADSAFE -DNO_SECURITY

LIB = libpref
SHARED_LIB = $(LIB).so
STATIC_LIB = $(LIB).a

ifeq ($(OS),Windows_NT)
	CC = gcc
	DEFINES += -DXP_PC -DXP_WIN
	SHARED_LIB = $(LIB).dll
	LD_FLAGS += -L../../../nsprpub/pr/src -L../../../js/src \
	    -L../../../nsprpub/lib/libc/src -L../../../nsprpub/lib/ds \
	    -L../../../xpcom/src \
			-lmozjs -lnspr -lnsprc -lplds -lxpcom -Wl,--out-implib,$(LIB).a \
			-lwsock32 -lwinmm
#	C_SRCS += win/winfunc.c
else
	DEFINES += -DXP_UNIX
	C_SRCS += unix/unixpref.c
endif

CFLAGS = -Wall -g3 $(DEFINES)


all: $(SHARED_LIB)

$(STATIC_LIB): $(OBJS)
	$(RM) $(STATIC_LIB)
	$(AR) cru $(STATIC_LIB) $(OBJS)
	ranlib $(STATIC_LIB)

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared -o $@ $(OBJS) $(LD_FLAGS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -fpic -MMD -MP -MT $@ -o $@ -c $<

.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDES) -fpic -MMD -MP -MT $@ -o $@ -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(SHARED_LIB)

# Include automatically generated dependency files
-include $(DEPS)
