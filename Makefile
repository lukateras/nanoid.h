MANDOC ?= mandoc
PREFIX ?= /usr/local

root := $(DESTDIR)$(PREFIX)
bin := $(root)/bin
inc := $(root)/include
man1 := $(root)/share/man/man1
man3 := $(root)/share/man/man3

all: nanoidgen

clean:
	rm -f nanoidgen

install: nanoidgen
	install -d $(bin) $(inc) $(man1) $(man3)
	install -m 755 nanoidgen $(bin)/nanoidgen
	install -m 644 nanoid.h $(inc)/nanoid.h
	install -m 644 nanoidgen.1 $(man1)/nanoidgen.1
	install -m 644 nanoid.3 $(man3)/nanoid.3

uninstall:
	rm -f $(bin)/nanoidgen $(inc)/nanoid.h $(man1)/nanoidgen.1 $(man3)/nanoid.3

.PHONY: all clean install uninstall

nanoidgen.pdf: nanoidgen.1 nanoid.3
	$(MANDOC) -T pdf nanoidgen.1 nanoid.3 > $@
