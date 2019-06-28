# Makefile for libutil

.PHONY: all clean

C_SRCS = obs.c

OBJS = $(C_SRCS:.c=.o)
DEPS = $(C_SRCS:.c=.d)

INCLUDES = -I../../../nsprpub/lib/libc/include -I../../../nsprpub/pr/include \
					 -I../../../xpcom/public -I../public -I../../../include \
					 -I../../../js/src -I../../../nsprpub/lib/ds -I../../libutil/public \
					 -I../../libimg/public -I../../../lib/liblayer/include \
					 -I../../security/freenav
CFLAGS = -Wall -g3 -DXP_UNIX -DJS_THREADSAFE -DSTANDALONE_IMAGE_LIB

CC? = gcc
AR? = ar
RM = rm -f

LIB = libmozutil
SHARED_LIB = $(LIB).so
STATIC_LIB = $(LIB).a
LDFLAGS =

ifeq ($(OS),Windows_NT)
	CC = gcc
	SHARED_LIB = $(LIB).dll
	LDFLAGS += -L../../../nsprpub/pr/src -lnspr -Wl,--out-implib,$(LIB).a
endif


all: $(STATIC_LIB)

$(STATIC_LIB): $(OBJS)
	$(RM) $(STATIC_LIB)
	$(AR) cru $(STATIC_LIB) $(OBJS)
	ranlib $(STATIC_LIB)

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared -o $@ $(OBJS) $(LDFLAGS)

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
