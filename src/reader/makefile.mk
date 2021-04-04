build/reader.o: build/snia_reader.o
	cp build/snia_reader.o build/reader.o

build/snia_reader.o: src/reader/snia_reader.cc
	mkdir -p build
	$(CC) $(CCFLAGS) -c -o build/snia_reader.o src/reader/snia_reader.cc