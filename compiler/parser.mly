%{
open Syntax
%}
%token<int> INT
%token<string> STRING ID
%token EOF EOL COLON LT LE GT GE EQ ADD SUB ELSE GOTO IF PRINT THEN
%type<Syntax.prog> program
%start program
%%
program   : lines EOF                   { $1 }
lines     : line                        { [$1] } 
          | line lines                  { $1::$2 }
line      : INT stmts EOL               { ($1, $2) }
stmts     : stmt                        { $1 }
          | stmt COLON stmts            { Multi($1,$3) }
stmt      : GOTO INT                    { Goto($2) }
          | PRINT expr                  { Print $2 }
          | ID EQ expr                  { Assign($1,$3) }
          | IF expr GOTO INT else_stmt  { If($2,Goto $4,$5) }
          | IF expr THEN INT else_stmt  { If($2,Goto $4,$5) }
          | IF expr THEN stmts else_stmt{ If($2,$4,$5) }
else_stmt :                             { Unit }
          | ELSE INT                    { Goto $2 }
          | ELSE stmts                  { $2 }
expr      : INT                         { Int $1 }
          | STRING                      { String $1 }
          | ID                          { Var $1 }
          | expr ADD expr               { Bin(Add,$1,$3) }
          | expr SUB expr               { Bin(Sub,$1,$3) }
          | expr LT expr                { Bin(Lt,$1,$3) }
          | expr LE expr                { Bin(Le,$1,$3) }
          | expr GT expr                { Bin(Gt,$1,$3) }
          | expr GE expr                { Bin(Ge,$1,$3) }
