COMP = compiler/compilation
EVAL = compiler/evaluation
# source files live under src/compiler; compiler.cpp was removed so only list existing .cpp files
COMP_FILES = compiler/main.cpp compiler/ast.cpp compiler/lexer.cpp compiler/parcer.cpp
# evaluator appears not implemented yet; leave empty or use placeholder
EVAL_FILES = read_ast/main.cpp compiler/lexer.cpp

CXXFLAGS = -Wall -Wextra -O0 -g3 -fno-omit-frame-pointer -D_GLIBXX_DEBUG

# build binaries
$(COMP): $(COMP_FILES)
	g++ $(CXXFLAGS) $(COMP_FILES) -o $(COMP)

$(EVAL): $(EVAL_FILES)
	g++ $(CXXFLAGS) $(EVAL_FILES) -o $(EVAL)

# convenience phony targets
comp: $(COMP)

eval: $(EVAL)

all: $(COMP) $(EVAL)

run-comp: $(COMP)
	./$(COMP)

run-eval: $(EVAL)
	./$(EVAL)

clean-comp:
	rm -f $(COMP)
	rm -rf *.dSYM

clean-eval:
	rm -f $(EVAL)
	rm -rf *.dSYM

.PHONY: all make-comp make-eval run-comp run-eval clean-comp clean-eval