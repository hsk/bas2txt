%{
open Syntax
%}
%token<int> INT
%token EOF EOL GOTO PRINT
%type<Syntax.prog> program
%start program
%%
program   : lines EOF                   { $1 }
lines     : line                        { [$1] } 
          | line lines                  { $1::$2 }
line      : INT stmt EOL                { ($1, $2) }
stmt      : GOTO INT                    { Goto($2) }
          | PRINT expr                  { Print $2 }
expr      : INT                         { Int $1 }
