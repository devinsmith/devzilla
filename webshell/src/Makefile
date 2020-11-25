# Makefile for libraptorwebwidget

.PHONY: all clean

SRCS = nsDLLFactory.cpp nsDocLoader.cpp nsWebShell.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

INCLUDES = -I../../nsprpub/lib/libc/include -I../../nsprpub/pr/include \
					 -I../../xpcom/public -I../public -I. -I../../base/src \
					 -I../../include -I../../nsprpub/lib/ds -I../../widget/public \
					 -I../../modules/libimg/public -I../../modules/libutil/public \
					 -I../../modules/plugin/nglsrc -I../../modules/plugin/public \
					 -I../../view/public -I../../gfx/public -I../../modules/libpref/public \
					 -I../../js/src -I../../network/module -I../../layout/base/public \
					 -I../../network/public
CFLAGS = -Wall -g3

CC? = gcc
AR? = ar
RM = rm -f

ifeq ($(OS),Windows_NT)
	CC = gcc
endif

LIB = libraptorwebwidget
SHARED_LIB = $(LIB).so
STATIC_LIB = $(LIB).a

all: $(SHARED_LIB)

$(STATIC_LIB): $(OBJS)
	$(RM) $(STATIC_LIB)
	$(AR) cru $(STATIC_LIB) $(OBJS)
	ranlib $(STATIC_LIB)

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared -o $@ $(OBJS)
	cp $(SHARED_LIB) ../../xpfe/bootstrap

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDES) -fpic -MMD -MP -MT $@ -o $@ -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(SHARED_LIB)

# Include automatically generated dependency files
-include $(DEPS)
