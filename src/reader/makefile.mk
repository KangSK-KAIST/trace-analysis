build/snia_reader.o: src/reader/snia_reader.cc
	mkdir -p build
	$(CC) $(CCFLAGS) -c -o build/snia_reader.o src/reader/snia_reader.cc

build/alibaba_reader.o: src/reader/alibaba_reader.cc
	mkdir -p build
	$(CC) $(CCFLAGS) -c -o build/alibaba_reader.o src/reader/alibaba_reader.cc