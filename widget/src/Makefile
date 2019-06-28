# Makefile for widgets
#
.PHONY: build clean

TOOLKIT = motif
ifeq ($(OS),Windows_NT)
	TOOLKIT = win
endif

build:
	@(cd $(TOOLKIT) && $(MAKE))

clean:
	@(cd $(TOOLKIT) && $(MAKE) clean)

