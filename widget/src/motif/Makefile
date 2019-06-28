# Makefile for libraptorbase

.PHONY: all clean

C_SRCS = nsXtManageWidget.c

SRCS = Motifdlldeps.cpp nsMotifWidgetFactory.cpp \
			 nsAppShell.cpp nsToolkit.cpp nsWindow.cpp \
			 nsXtEventHandler.cpp nsMenu.cpp nsMenuBar.cpp \
			 nsMenuItem.cpp

OBJS = $(C_SRCS:.c=.o) $(SRCS:.cpp=.o)
DEPS = $(C_SRCS:.c=.d) $(SRCS:.cpp=.d)

INCLUDES = -I../../../nsprpub/lib/libc/include -I../../../nsprpub/pr/include \
					 -I../../../xpcom/public -I../../public -I. -I../../../base/src \
					 -I../../../gfx/public -I../../../nsprpub/lib/ds
CFLAGS = -Wall -g3

CC? = gcc
AR? = ar
RM = rm -f

ifeq ($(OS),Windows_NT)
	CC = gcc
	RM = del /Q 2>NUL
endif

LIB = libwidgetmotif
SHARED_LIB = $(LIB).so
STATIC_LIB = $(LIB).a

all: $(SHARED_LIB)

$(STATIC_LIB): $(OBJS)
	$(RM) $(STATIC_LIB)
	$(AR) cru $(STATIC_LIB) $(OBJS)
	ranlib $(STATIC_LIB)

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared -o $@ $(OBJS) -lXm -lXt -lX11

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
