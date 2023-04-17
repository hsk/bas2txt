all:
	ocamlyacc parser.mly
	rm -rf parser.mli
	ocamllex lexer.mll
	ocamlfind ocamlc -package ppx_deriving.show -o msxbasc syntax.ml parser.ml lexer.ml comp.ml main.ml
	rm -rf parser.ml lexer.ml *.cm*
tests: all
	./msxbasc examples/1.bas > a.c && gcc a.c && ./a.out
	rm -rf a.c a.out
clean:
	rm -rf parser.ml lexer.ml *.cm* msxbasc a.c a.out

msx:
	cp examples/1.bas examples/autoexec.bas
	openmsx -machine Panasonic_FS-A1ST -diska examples
