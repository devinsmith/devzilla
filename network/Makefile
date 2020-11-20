# network master makefile

build:
	@(cd client && $(MAKE))
	@(cd main && $(MAKE))
	@(cd mimetype && $(MAKE))
	@(cd protocol && $(MAKE))
	@(cd module && $(MAKE))
	@(cd util && $(MAKE))

clean:
	@(cd client && $(MAKE) clean)
	@(cd main && $(MAKE) clean)
	@(cd mimetype && $(MAKE) clean)
	@(cd protocol && $(MAKE) clean)
	@(cd module && $(MAKE) clean)
	@(cd util && $(MAKE) clean)

