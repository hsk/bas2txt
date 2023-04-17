let parse file =
  let f = open_in file in
  Parser.program Lexer.token (Lexing.from_channel f)


let _ =
  let prog = parse Sys.argv.(1) in
  Syntax.log "%s\n" (Syntax.show_prog prog);
  Comp.compile prog;
  ()
