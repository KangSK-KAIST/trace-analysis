CC := clang++-7
# CCFLAGS := -Wall -Werror -O0 -g -D_FORTIFY_SOURCE=2 -DDEBUG -DLOGGING
CCFLAGS := -O2

.PHONY: all
all: main_snia main_ali

include src/reader/makefile.mk
include src/parser/makefile.mk
include src/analyzer/makefile.mk
include src/saver/makefile.mk

main_snia: src/main.cc build/snia_reader.o build/parser.o build/analyzer.o build/dependent_saver.o
	$(CC) $(CCFLAGS) -o build/main_snia $^

main_ali: src/main.cc build/alibaba_reader.o build/parser.o build/analyzer.o build/dependent_saver.o
	$(CC) $(CCFLAGS) -o build/main_ali $^

.PHONY: clean
clean:
	rm -r build