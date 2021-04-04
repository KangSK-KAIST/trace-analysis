build/parser.o: build/general_parser.o
	cp build/general_parser.o build/parser.o

build/general_parser.o: src/parser/general_parser.cc
	mkdir -p build
	$(CC) $(CCFLAGS) -c -o build/general_parser.o src/parser/general_parser.cc