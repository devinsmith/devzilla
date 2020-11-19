# Makefile for libnsappshell

.PHONY: all clean

SRCS = nsAppShellFactory.cpp nsAppShellService.cpp nsCommandLineService.cpp \
			 nsWebShellWindow.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

INTERNAL_CFLAGS = -Wall -g3 -DXP_UNIX -I../../../widget/public \
	-I../../../base/src -I../../../nsprpub/pr/include -I../../../xpcom/public \
	-I../../../nsprpub/lib/ds -I../../../modules/libpref/public \
	-I../../../include -I../../../js/src -I../../../webshell/public \
	-I../../../nsprpub/lib/libc/include -I../../../gfx/public \
	-I../../../view/public -I../../../network/module -I../public \
	-I../../../layout/base/public -I../../../network/public -fPIC

CC? = gcc
AR? = ar
RM = rm -f

ifeq ($(OS),Windows_NT)
	CC = gcc
endif

LIB = libnsappshell
SHARED_LIB = $(LIB).so
STATIC_LIB = $(LIB).a
LDFLAGS = -L../../../base/src -lraptorbase

all: $(SHARED_LIB)

$(STATIC_LIB): $(OBJS)
	$(RM) $(STATIC_LIB)
	$(AR) cru $(STATIC_LIB) $(OBJS)
	ranlib $(STATIC_LIB)

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared -o $@ $(OBJS) $(LDFLAGS)

.c.o:
	$(CC) $(INTERNAL_CFLAGS) $(CPPFLAGS) -o $@ -c $<

.cpp.o:
	$(CXX) $(INTERNAL_CFLAGS) -std=c++11 $(DEP_CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(SHARED_LIB)

# Include automatically generated dependency files
-include $(DEPS)
