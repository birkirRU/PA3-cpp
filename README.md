# PA3-cpp

Expression compiler and evaluator: Part 1 builds an AST from an expression and writes it to a file; Part 2 reads an AST file and evaluates it (optionally with variables).

---

## How to compile and run

**All commands below are run from the project root** (the folder that contains `src/` and this README).

### Build

```bash
cd src
make all
```

This builds two binaries:

- `src/compiler/compilation` — Part 1 (expression → AST file)
- `src/compiler/evaluation` — Part 2 (AST file → value)

From the project root you can also run:

```bash
cd src && make all && cd ..
```

### Part 1: Compile expression to AST

Run from the **project root**.

- **Two arguments** (output AST file, input expression file):
  ```bash
  ./src/compiler/compilation <ast_output> <expression_input>
  ```
  The expression is read from `src/expressions/<expression_input>`. The AST is written to `src/ast/<ast_output>`.
- **One argument** (output AST file only): the expression is read from **stdin**.
  ```bash
  ./src/compiler/compilation result.ast
  2+7*(1+3+4*2) ctrl d
  ```
  The program writes stdin to `src/expressions/stdin_input.txt` and then parses it, to write to std in, press ´ctrl d´ after typing expression.
- **No arguments**: uses the default expression file `src/expressions/input.txt` and writes the AST to `src/ast/output.txt`.

Example (two arguments):

```bash
./src/compiler/compilation result.ast input.txt
```

### Part 2: Evaluate AST

Run from the **project root**.

- **One argument** (AST file): evaluate the AST and print the result. No variables.
  ```bash
  ./src/read_ast/evaluation result.ast
  ```
  The program reads the AST from `src/ast/<ast_file>`.
- **Two arguments** (AST file and `var`): same as above, but variables are taken from the fixed file `src/read_ast/vars.txt` (format: one line per variable, `name=value`, e.g. `x=7`).
  ```bash
  ./src/read_ast/evaluation result.ast var
  ```
  The second argument must be exactly `var`; any other second argument is rejected.

Example with variables:

```bash
./src/read_ast/evaluation result.ast var
```

---

## AST file format

The AST is stored in a **prefix (S-expression) style**: each node is either a leaf or `(operator child ...)`.

- **Numbers**: written as the digit string, e.g. `42`.
- **Variables**: written as the identifier, e.g. `x`.
- **Binary operators** (`+`, `-`, `*`, `/`): `(op left right)` with a single space after the operator and between operands.  
Example: `(+ 2 (* 3 4))` for the expression `2 + 3*4`.
- **Unary minus**: `(- operand)` with no space after `-`.  
Example: `(- 5)` for `-5`.

The evaluator reads this format by tokenizing the AST file with the same lexer and then interpreting the token stream as a prefix tree: after an opening `(`, the next token is the operator or unary `-`, followed by the operands (which can be sub-expressions, numbers, or identifiers).

**Example:** For the expression `2+7*(1+3+4*2)`, the AST file might look like:

```
(+ 2 (* 7 (+ (+ 1 3) (* 4 2))))
```

---

## Additional features implemented

Beyond the base version (50%), the following are implemented:

1. **Whitespace insensitive (5%)**
  The lexer skips spaces, newlines, and tabs. Input can be split across lines and still be parsed.
2. **Modern C++ tree (5%)**
  The AST is a literal tree of nodes (numbers, variables, unary/binary operators) linked with `**std::unique_ptr`**. There is no manual `new`/`delete`; ownership and cleanup are handled by smart pointers.
3. **Variables (15%)**
  - Expressions can contain identifiers (lowercase letters), which become variable leaves in the AST.  
  - Part 2 can load variable values from a file when called with the second argument `var`, which uses the fixed path `src/read_ast/vars.txt`.  
  - Each line in the variable file is `name=value` (e.g. `x=7`). Missing variables used in the AST are reported with a clear error message.
4. **Extra operations (10%)**
  Supported operators: addition (`+`), subtraction (`-`), multiplication (`*`), division (`/`, integer division as in C++), and **unary minus** (e.g. `(-3-12)/5`). Precedence and associativity match the grammar below.
5. **Error handling (~10%)**
  - **Compiler:** Input file not found; output file not writable; parse errors (unexpected character, missing `)`, unexpected end of input); invalid or too many arguments.  
  - **Evaluator:** AST file not found; variable file not found when using `var`; missing variable; invalid number in variable file; division by zero; 64-bit overflow in arithmetic; invalid or truncated AST.  
   Errors are reported on stderr with a single, clear message per case; the program exits with status 1.

**Not implemented:** AST optimisations, high-speed (linear-time) parsing for very large inputs.

---

## Implementation details

### Lexer

- Reads from a file (given by path) and tokenizes into: numbers, identifiers (lowercase), operators `+ - * /`, parentheses `( )`, and a sentinel end token.
- **Skips all whitespace** (spaces, newlines, tabs) between tokens.
- Unrecognized characters produce an **ERROR** token (with the character stored); the token stream is passed to the parser so it can report “Unexpected character: …”.

### Grammar

The syntax is defined so that precedence and associativity come from the structure of the AST:

```
expression  :=  term ((+ | -) term)*
term        :=  factor ((* | /) factor)*
factor      :=  NUMBER
             |  VARIABLE
             |  '-' factor
             |  '(' expression ')'
```

- **Precedence:** Multiplication and division bind tighter than addition and subtraction; unary minus applies to a single factor.
- **Associativity:** Binary operators are left-associative (each new operator takes the previously built subtree as its left operand).
- The parser is implemented as a **recursive-descent** parser with loops for the `*` parts of the grammar, so it is naturally right-recursive and does not loop indefinitely.

### Parsing

- Implemented in the parser (e.g. `_expr`, `_term`, `_factor`). The AST is built as the parse proceeds using `std::make_unique` for nodes.
- Unary minus is handled inside `_factor` and has higher precedence than binary subtraction.
- **Header files** contain only declarations; implementations are in `.cpp` files.

### Evaluator

- Reads the AST file and tokenizes it with the same lexer, then evaluates the token stream as a **prefix expression**: after `(`, the next token is the operator (or unary `-`), followed by the operands. Recursive evaluation with a single index into the token list yields the result.
- Variables are looked up in a map loaded from `src/read_ast/vars.txt` when the second argument is `var`. Division uses C++ integer division; overflow is checked for 64-bit signed arithmetic.

---


