# Makefile for widget test

.PHONY: all clean

SRCS = main.cpp nsWidgetTest.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

CC? = gcc
CXX? = g++

# Dependencies
DEP_INCLUDES = -I../../../xpcom/public -I../../../nsprpub/pr/include \
	-I../../../base/src -I../../public -I../../../nsprpub/lib/ds \
	-I../../../gfx/public
DEP_LIBS = -L../../../xpcom/src -L../../../base/src -lxpcom -lraptorbase

CFLAGS = -Wall -g3 -I.

EXE = widget

ifeq ($(OS),Windows_NT)
	DEFINES += -D_IMPL_NS_COM -DWIN32_LEAN_AND_MEAN
	EXE = widget.exe
	SHARED_LIB = xpcom.dll
	LD_FLAGS += -L../../nsprpub/pr/src -L../../nsprpub/lib/libc/src \
		-L../../nsprpub/lib/ds -Wl,--out-implib,$(LIB).a \
		-lnsprc -lplds -lnspr -lwsock32 -lwinmm
	ifeq ($(SHELL),sh.exe)
		# Executing under cmd.exe
		RM = del /Q 2>NUL
	endif
else
	DEP_LIBS += -L../../../nsprpub/pr/src -L../../../nsprpub/lib/libc/src \
			-L../../../nsprpub/lib/ds -lnsprc -lplds -lnspr -pthread -ldl
endif

all: $(EXE)

$(EXE): $(OBJS)
#	$(CXX) -mwindows -static $(CFLAGS) -o $(EXE) $(OBJS) $(DEP_LFLAGS) $(DEP_LIBS)
	$(CXX) $(CFLAGS) -o $(EXE) $(OBJS) $(DEP_LFLAGS) $(DEP_LIBS)

.cpp.o:
	$(CXX) $(CFLAGS) $(DEP_INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

clean:
	rm -f $(OBJS) $(EXE) $(DEPS)

# Include automatically generated dependency files
-include $(DEPS)
