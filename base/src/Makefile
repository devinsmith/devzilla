# Makefile for libraptorbase

.PHONY: all clean

SRCS = nsCRT.cpp nsString.cpp nsVoidArray.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

INCLUDES = -I../../nsprpub/lib/libc/include -I../../nsprpub/pr/include \
					 -I../../xpcom/public -I../public -I.
CFLAGS = -Wall -O2

CC? = gcc
AR? = ar
RM = rm -f

LIB = libraptorbase
SHARED_LIB = $(LIB).so
STATIC_LIB = $(LIB).a

ifeq ($(OS),Windows_NT)
	CC = gcc
	SHARED_LIB = $(LIB).dll
	DEFINES += -D_IMPL_NS_BASE -DWIN32_LEAN_AND_MEAN
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
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -fPIC -MMD -MP -MT $@ -o $@ -c $<

.cpp.o:
	$(CXX) $(CFLAGS) $(DEFINES) $(INCLUDES) -fPIC -MMD -MP -MT $@ -o $@ -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(SHARED_LIB)

# Include automatically generated dependency files
-include $(DEPS)
