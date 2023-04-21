all:
	gcc -o bas2txt bas2txt.c
	gcc -o txt2bas txt2bas.c
	./bas2txt dsk/b.bas
	./txt2bas dsk/a.bas dsk/c.bas
	hexdump -C dsk/b.bas > b.txt
	hexdump -C dsk/c.bas > c.txt
	./bas2txt dsk/c.bas
	diff b.txt c.txt
test:
	./txt2bas dsk/d.bas dsk/e.bas
	hexdump -C dsk/e.bas > e.txt
	hexdump -C dsk/f.bas > f.txt
	diff e.txt f.txt


m:
	openmsx -machine Panasonic_FS-A1ST -diska dsk
d:
	./txt2bas dsk/d.bas dsk/e.bas
	openmsx -machine Panasonic_FS-A1ST -diska dsk
clean:
	rm -f b.txt c.txt bas2txt txt2bas
