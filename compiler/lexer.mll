{ open Parser }
rule token = parse
| [' ' '\t']+                                               { token lexbuf }
| ('\n'|"\r\n")+                                            { Syntax.log "eol\n"; EOL }
| ['0'-'9']+   as i                                         { Syntax.log "int %s\n" i; INT(int_of_string i) }
| '"' ([^ '"']+ as s) '"'                                   { Syntax.log "string %s\n" s; STRING s }
| "+"                                                       { ADD }
| "<"                                                       { LT }
| "="                                                       { EQ }
| ['i''I']['f''F']                                          { IF }
| ['g''G']['o''O']['t''T']['o''O']                          { GOTO }
| ['p''P']['r''R']['i''I']['n''N']['t''T']                  { Syntax.log "print\n"; PRINT }
| ['A'-'Z''a'-'z']+ as i                                    { ID i }
| eof                                                       { Syntax.log "eof\n"; EOF }
