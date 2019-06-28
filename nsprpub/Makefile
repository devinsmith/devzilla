# nspr master makefile

MOD_DEPTH = .

DIRS = pr lib

ifdef MOZILLA_CLIENT
PR_CLIENT_BUILD = 1
PR_CLIENT_BUILD_UNIX = 1
endif

#include $(MOD_DEPTH)/config/rules.mk

build:
	@(cd lib && $(MAKE))
	@(cd pr && $(MAKE))

clean:
	@(cd lib && $(MAKE) clean)
	@(cd pr && $(MAKE) clean)

