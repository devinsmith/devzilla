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
	-I../../network/module -I../../modules/plugin/nglsrc \
	-I../../modules/plugin/public -fPIC

CPPFLAGS += -MMD -MP -MT $@
LDFLAGS = -L../../xpcom/src -L../../nsprpub/lib/ds \
	-L../../nsprpub/pr/src -L../../nsprpub/lib/libc/src \
	-L../appshell/src -L../../modules/libpref/src \
	-L../../network/module -L../../network/main \
	-L../../base/src \
	-L../../js/src \
	-L../../modules/libimg/src \
	-L../../modules/libreg/src \
	-L../../modules/libutil/src -L../../network/protocol/gopher \
	-L../../network/protocol/file -L../../network/protocol/http \
	-L../../network/protocol/about -L../../network/protocol/ftp \
	-L../../network/protocol/remote \
	-L../../lib/xp -L../../network/cache -L../../network/mimetype \
	-L../../lib/libpwcac -L../../network/cnvts \
	-L../../modules/security/freenav \
	-Wl,--no-as-needed
LIBS = -lxp -lfileurl -lhttpurl -labouturl -lpref -lnetcache -lnetcnvts \
			 -lmozmimetypes -lmoznetwork -lmoznetlib -lftpurl -lgophurl \
			 -lraptorbase -lxpcom -lmozjs -lsecfree -lremoturl \
			 -lplds -limg -lmozreg -lpwcac \
			 -lmozutil -lnspr -lnsprc -ldl -lz
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
