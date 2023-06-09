{ open Parser }
rule token = parse
| [' ' '\t']+                                               { token lexbuf }
| ('\n'|"\r\n")+                                            { Syntax.log "eol\n"; EOL }
| ['0'-'9']+   as i                                         { Syntax.log "int %s\n" i; INT(int_of_string i) }
| '"' ([^ '"']+ as s) '"'                                   { Syntax.log "string %s\n" s; STRING s }
| ":"                                                       { COLON }
| "+"                                                       { ADD }
| "-"                                                       { SUB }
| "<"                                                       { LT }
| "<="                                                      { LE }
| ">"                                                       { GT }
| ">="                                                      { GE }
| "="                                                       { EQ }
| ['e''E']['l''L']['s''S']['e''E']                          { ELSE }
| ['g''G']['o''O']['t''T']['o''O']                          { GOTO }
| ['i''I']['f''F']                                          { IF }
| ['p''P']['r''R']['i''I']['n''N']['t''T']                  { Syntax.log "print\n"; PRINT }
| ['t''T']['h''H']['e''E']['n''N']                          { THEN }
| ['A'-'Z''a'-'z']+ as i                                    { ID i }
| eof                                                       { Syntax.log "eof\n"; EOF }
