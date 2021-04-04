CC := clang++-7
CCFLAGS := -Wall -Werror -O0 -g -D_FORTIFY_SOURCE=2 -DDEBUG -DLOGGING
# CCFLAGS := -O2 -DLOGGING

.PHONY: all
all: main

include src/reader/makefile.mk
include src/parser/makefile.mk
include src/analyzer/makefile.mk

main: src/main.cc build/reader.o build/parser.o build/analyzer.o
	$(CC) $(CCFLAGS) -o build/main $^

.PHONY: clean
clean:
	rm -rf build