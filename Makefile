# Makefile for devzilla

DEPTH = .
topsrcdir = .
srcdir = .

include $(DEPTH)/config/autoconf.mk

DIRS = nsprpub \
	 $(NULL)

DIRS += xpcom \
	 lib \
	 $(NULL)

DIRS += modules/libutil \
	 js \
	 modules/libpref \
	 modules/libimg \
	 base \
	 network \
	 gfx \
	 view \
	 widget \
	 webshell

DIRS += xpfe

include $(DEPTH)/config/config.mk
include $(DEPTH)/config/rules.mk

real_all: all

real_export: export

real_libs: libs

real_install: install

real_clobber: clobber

real_depend: depend


