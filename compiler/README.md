# Simple MSX BASIC Compiler

Syntax

```
program   ::= lines
lines     ::= line | line lines
line      ::= INT stmt EOL
stmt      ::= GOTO INT | IF expr GOTO INT | IF expr THEN INT | IF expr THEN stmt
            | PRINT expr
            | VAR = expr
expr      ::= INT | STRING | VAR
            | expr +  expr
            | expr -  expr
            | expr <  expr
            | expr <= expr
            | expr >  expr
            | expr >= expr
```
