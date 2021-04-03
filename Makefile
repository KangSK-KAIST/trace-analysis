CC := clang++-7
CCFLAGS := -Wall -Werror

.PHONY: all
all: main

include src/reader/makefile.mk
include src/parser/makefile.mk

main: src/main.cc build/reader.o build/parser.o
	$(CC) $(CCFLAGS) -o build/main $^

.PHONY: clean
clean:
	rm -rf build