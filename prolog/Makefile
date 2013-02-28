PC=$(shell which gplc)
RM=$(shell which rm) -rf

all: flu line extra

test: all
	./flu && ./line && ./extra

clean:
	$(RM) flu line extra

.PHONY: all test clean

%: %.pl
	$(PC) $< -o $@
	./$@
