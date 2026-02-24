# PA3-cpp


### Lexer

Skips whitespaces

### Grammar
```
expression := term ((+|-) term)*
term       := factor ((*|/) factor)*
factor     := NUMBER
            | VARIABLE
            | '-' factor
            | '(' expression ')'
```

This grammar was decided because it enforces order of precedence by structure of the AST.
Addition and subtraction will always be higher up the tree (with lower precedence), than multiplication and division. This is due to the fact that term can never reach expression, unless through parenthesis, only then will addition/subtraction be enclosed with higher precedence.


### Parsing 

Implamented as a recursive descent down parcer.
The parser is naturaly right recursive so it doesn't loop indefinately. 
This is done by using loops for kleene star of expression and term.

Left associativity is enforced because each new operator combines the previously constructed subtree as its left operand.

Unery minus will be explicetly handled by the parser, using context of the expression. It will have a higher operator precedence than regular SUBTRACTION. 

### Running the Progam

All make commands will be run from the projects root. 
Names of output files and inputs files for the base compiler (base version), will not need to include paths, just the name. Make sure that input file exists in 'expressions' folder before using it. 