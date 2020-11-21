# network master makefile

build:
	@(cd cache && $(MAKE))
	@(cd client && $(MAKE))
	@(cd cnvts && $(MAKE))
	@(cd main && $(MAKE))
	@(cd mimetype && $(MAKE))
	@(cd protocol && $(MAKE))
	@(cd module && $(MAKE))
	@(cd util && $(MAKE))

clean:
	@(cd cache && $(MAKE) clean)
	@(cd client && $(MAKE) clean)
	@(cd cnvts && $(MAKE) clean)
	@(cd main && $(MAKE) clean)
	@(cd mimetype && $(MAKE) clean)
	@(cd protocol && $(MAKE) clean)
	@(cd module && $(MAKE) clean)
	@(cd util && $(MAKE) clean)

