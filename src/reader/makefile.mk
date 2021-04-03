build/reader.o: src/reader/raw_file_reader.cc
	mkdir -p build
	$(CC) $(CCFLAGS) -c -o build/reader.o src/reader/raw_file_reader.cc