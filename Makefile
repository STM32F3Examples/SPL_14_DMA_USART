.PHONY: test clean dist_clean test_clean
all: build
build:
	$(MAKE) --directory=./gcc
burn:
	$(MAKE) --directory=./gcc burn
test:
	$(MAKE) --directory=./tests test
clean:
	$(MAKE) --directory=./gcc clean
test_clean:
	$(MAKE) --directory=./tests clean
dist_clean: clean
	$(MAKE) --directory=./tests dist_clean
