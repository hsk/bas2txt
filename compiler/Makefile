all:
	ocamlyacc parser.mly
	rm -rf parser.mli
	ocamllex lexer.mll
	ocamlfind ocamlc -package ppx_deriving.show -o msxbasc syntax.ml parser.ml lexer.ml comp.ml main.ml
	rm -rf parser.ml lexer.ml *.cm*
tests: all
	./msxbasc examples/2.bas > a.c && gcc a.c && ./a.out | diff examples/2.txt -
	./msxbasc examples/1.bas > a.c && gcc a.c && ./a.out | diff examples/1.txt -
	rm -rf a.c a.out
clean:
	rm -rf parser.ml lexer.ml *.cm* msxbasc a.c a.out

msx1:
	cp examples/1.bas examples/autoexec.bas
	openmsx -machine Panasonic_FS-A1ST -diska examples
msx2:
	cp examples/2.bas examples/autoexec.bas
	openmsx -machine Panasonic_FS-A1ST -diska examples
