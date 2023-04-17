# simple msx basic compiler

syntax

```
program   ::= lines
lines     ::= line | line lines
line      ::= INT stmt EOL
stmt      ::= GOTO INT | PRINT expr
expr      ::= INT | STRING
```
