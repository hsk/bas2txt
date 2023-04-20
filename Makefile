all:
	gcc -o bas2txt bas2txt.c
	gcc -o txt2bas txt2bas.c
	./bas2txt ex001/b.bas
	./txt2bas ex001/a.bas ex001/c.bas
	hexdump -C ex001/b.bas > b.txt
	hexdump -C ex001/c.bas > c.txt
	./bas2txt ex001/c.bas b
	diff b.txt c.txt
m:
	openmsx -machine Panasonic_FS-A1ST -diska dsk
d:
	./txt2bas dsk/d.bas dsk/e.bas
	openmsx -machine Panasonic_FS-A1ST -diska dsk
clean:
	rm -f b.txt c.txt bas2txt txt2bas
