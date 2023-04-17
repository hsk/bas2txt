%{
open Syntax
%}
%token<int> INT
%token<string> STRING ID
%token EOF EOL LT LE EQ ADD GOTO IF PRINT
%type<Syntax.prog> program
%start program
%%
program   : lines EOF                   { $1 }
lines     : line                        { [$1] } 
          | line lines                  { $1::$2 }
line      : INT stmt EOL                { ($1, $2) }
stmt      : GOTO INT                    { Goto($2) }
          | PRINT expr                  { Print $2 }
          | ID EQ expr                  { Assign($1,$3) }
          | IF expr GOTO INT            { If($2,Goto $4,Unit) }
expr      : INT                         { Int $1 }
          | STRING                      { String $1 }
          | ID                          { Var $1 }
          | expr ADD expr               { Add($1,$3) }
          | expr LT expr                { Lt($1,$3) }
          | expr LE expr                { Le($1,$3) }
