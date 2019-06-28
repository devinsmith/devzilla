# Makefile for libraptorbase

.PHONY: all clean

#C_SRCS = motif/nsXtManageWidget.c

SRCS = nsWinWidgetFactory.cpp

OBJS = $(C_SRCS:.c=.o) $(SRCS:.cpp=.o)
DEPS = $(C_SRCS:.c=.d) $(SRCS:.cpp=.d)

INCLUDES = -I../../../nsprpub/lib/libc/include -I../../../nsprpub/pr/include \
					 -I../../../xpcom/public -I../../public -I../../../base/src \
					 -I../../../gfx/public -I../../../nsprpub/lib/ds
CFLAGS = -Wall -g3 -D_IMPL_NS_WIDGET

CC = gcc
AR? = ar
RM = del /Q 2>NUL

LIB = raptorwidget
SHARED_LIB = $(LIB).dll
LDFLAGS += -L../../../nsprpub/pr/src -L../../../nsprpub/lib/libc/src \
		-L../../../nsprpub/lib/ds -Wl,--out-implib,lib$(LIB).a


all: $(SHARED_LIB)

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared -o $@ $(OBJS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(SHARED_LIB)

# Include automatically generated dependency files
-include $(DEPS)
