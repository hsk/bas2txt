{ open Parser }
rule token = parse
| [' ' '\t']+                                               { token lexbuf }
| ('\n'|"\r\n")+                                            { Syntax.log "eol\n"; EOL }
| ['0'-'9']+   as i                                         { Syntax.log "int %s\n" i; INT(int_of_string i) }
| ['g''G']['o''O']['t''T']['o''O']                          { GOTO }
| ['p''P']['r''R']['i''I']['n''N']['t''T']                  { Syntax.log "print\n"; PRINT }
| eof                                                       { Syntax.log "eof\n"; EOF }
