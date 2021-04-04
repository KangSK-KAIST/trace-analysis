build/reader.o: build/snia_parser.o
	cp build/snia_parser.o build/parser.o

build/snia_reader.o: src/reader/snia_reader.cc
	mkdir -p build
	$(CC) $(CCFLAGS) -c -o build/snia_reader.o src/reader/snia_reader.cc