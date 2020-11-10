# Makefile for apprunner

.PHONY: all clean

CPP_SRCS = nsAppRunner.cpp nsSetupRegistry.cpp

OBJS = $(CPP_SRCS:.cpp=.o)
DEPS = $(CPP_SRCS:.cpp=.d)

INTERNAL_CFLAGS = -Wall -g3 -DXP_UNIX -I../../widget/public \
	-I../../base/public \
	-I../../base/src -I../../nsprpub/pr/include -I../../xpcom/public \
	-I../../nsprpub/lib/ds -I../../modules/libpref/public \
	-I../../include -I../../js/src -I../../webshell/public \
	-I../../nsprpub/lib/libc/include -I../../gfx/public \
	-I../../view/public -I../../network/public -I../appshell/public \
	-I../../network/module -fPIC

CPPFLAGS += -MMD -MP -MT $@
LDFLAGS = -L../../xpcom/src -L../../nsprpub/lib/ds \
	-L../../nsprpub/pr/src -L../../nsprpub/lib/libc/src \
	-L../appshell/src \
	-L../../network/module \
	-L../../base/src \
	-L../../js/src \
	-L../../modules/libimg/src \
	-L../../modules/libreg/src \
	-L../../modules/libutil/src \
	-Wl,--no-as-needed
#LIBS = -lnsappshell -lmoznetlib -lraptorbase -lxpcom -lmozjs -lplds -limg -lmozreg -lmozutil -lnspr -lnsprc -lXm -lX11 -lXt -ldl
LIBS = -lmoznetlib -lraptorbase -lxpcom -lmozjs -lplds -limg -lmozreg -lmozutil -lnspr -lnsprc -lXm -lX11 -lXt -ldl
EXE = apprunner


all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) -pthread -rdynamic $(INTERNAL_CFLAGS) -o $(EXE) $(OBJS) $(LDFLAGS) $(LIBS)

.c.o:
	$(CC) $(INTERNAL_CFLAGS) $(CPPFLAGS) -o $@ -c $<

.cpp.o:
	$(CXX) $(INTERNAL_CFLAGS) -std=c++11 $(DEP_CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)
	rm -f $(EXE)

# Include automatically generated dependency files
-include $(DEPS)
