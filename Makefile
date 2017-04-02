VER = current

# On Debian, the util-linux version of rename is called "rename.ul".
# On Arch, it is just called "rename"
ifneq ("$(wildcard /usr/bin/rename.ul)", "")
	RENAME = rename.ul
else
	RENAME = rename
endif

release: vicwebsite qldwebsite source
	tar -cJf parliamenttracker_website_$(VER).tar.xz assembly council index *html LICENSE qld/index qld/index.html qld/divisions parliamenttracker_source_$(VER).tar.xz

vicrelease: vicwebsite source
	tar -cJf parliamenttracker_website_vic-$(VER).tar.xz assembly council index *html LICENSE parliamenttracker_source_$(VER).tar.xz

qldrelease: qldwebsite source
	tar -cJf parliamenttracker_website_qld-$(VER).tar.xz LICENSE qld/index.html qld/index qld/divisions parliamenttracker_source_$(VER).tar.xz

vicwebsite: parliamenttracker
	ulimit -s 65536 && ./parliamenttracker docx/*docx

qldwebsite:
	cd qld && python3 ./extract.py

parliamenttracker:
	gcc -o parliamenttracker -lz gather.c

docs: vicdocs qlddocs

vicdocs:
	cd docx &&  \
	wget -w 3 -i proceedings && \
	$(RENAME) "?Open" "" *Open ; \

qlddocs:
	cd qld/hansard && \
	./getHansards.sh

source:
	tar -cJf parliamenttracker_source_$(VER).tar.xz *c *html assembly.data.* council.data.* questions.data docx/proceedings Makefile qld/extract.py qld/hansard/hansard qld/hansard/getHansards.sh qld/hansard/pdf2txt.py README LICENSE

clean:
	rm -rf assembly council index parliamenttracker a.out qld/divisions qld/index qld/index.html *xz
