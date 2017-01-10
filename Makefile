VER = current

# On Debian, the util-linux version of rename is called "rename.ul".
# On Arch, it is just called "rename"
ifneq ("$(wildcard /usr/bin/rename.ul)", "")
	RENAME = rename.ul
else
	RENAME = rename
endif

release: website source
	tar -cJf parliamenttracker_website_$(VER).tar.xz assembly council index *html LICENSE parliamenttracker_source_$(VER).tar.xz

website: parliamenttracker
	./parliamenttracker docx/*docx

parliamenttracker:
	gcc -o parliamenttracker -lz gather.c

docs:
	cd docx &&  \
	wget -w 3 --no-check-certificate -i proceedings && \
	$(RENAME) "?Open" "" *Open ; \

source:
	tar -cJf parliamenttracker_source_$(VER).tar.xz *c *html assembly.data.* council.data.* questions.data docx/proceedings Makefile README LICENSE

clean:
	rm -rf assembly council index parliamenttracker a.out *xz
