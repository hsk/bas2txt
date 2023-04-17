all:
	ocamlyacc parser.mly
	rm -rf parser.mli
	ocamllex lexer.mll
	ocamlfind ocamlc -package ppx_deriving.show -o msxbasc syntax.ml parser.ml lexer.ml comp.ml main.ml
	rm -rf parser.ml lexer.ml *.cm*
tests: all
	./msxbasc examples/1.bas > a.c && gcc a.c && ./a.out | diff examples/1.txt -
	./msxbasc examples/2.bas > a.c && gcc a.c && ./a.out | diff examples/2.txt -
	./msxbasc examples/3.bas > a.c && gcc a.c && ./a.out | diff examples/3.txt -
	./msxbasc examples/4.bas > a.c && gcc a.c && ./a.out | diff examples/4.txt -
	./msxbasc examples/5.bas > a.c && gcc a.c && ./a.out | diff examples/5.txt -
	./msxbasc examples/6.bas > a.c && gcc a.c && ./a.out | diff examples/6.txt -
	./msxbasc examples/6_1.bas > a.c && gcc a.c && ./a.out | diff examples/6.txt -
	./msxbasc examples/6_2.bas > a.c && gcc a.c && ./a.out | diff examples/6.txt -
	./msxbasc examples/6_3.bas > a.c && gcc a.c && ./a.out | diff examples/6.txt -
	rm -rf a.out
clean:
	rm -rf parser.ml lexer.ml *.cm* msxbasc a.c a.out
	cd ../;make clean

msx1:
	cp examples/1.bas examples/autoexec.bas
	openmsx -machine Panasonic_FS-A1ST -diska examples
msx2:
	cp examples/2.bas examples/autoexec.bas
	openmsx -machine Panasonic_FS-A1ST -diska examples
msx3:
	cp examples/3.bas examples/autoexec.bas
	openmsx -machine Panasonic_FS-A1ST -diska examples
msx4:
	cp examples/4.bas examples/autoexec.bas
	openmsx -machine Panasonic_FS-A1ST -diska examples
msx5:
	cp examples/5.bas examples/autoexec.bas
	openmsx -machine Panasonic_FS-A1ST -diska examples
msx6:
	cp examples/6.bas examples/autoexec.bas
	openmsx -machine Panasonic_FS-A1ST -diska examples
msx6_3:
	cp examples/6_3.bas examples/autoexec.bas
	openmsx -machine Panasonic_FS-A1ST -diska examples
