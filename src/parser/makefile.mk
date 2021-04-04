build/parser.o: build/snia_parser.o
	cp build/snia_parser.o build/parser.o

build/snia_parser.o: src/parser/snia_parser.cc
	mkdir -p build
	$(CC) $(CCFLAGS) -c -o build/snia_parser.o src/parser/snia_parser.cc