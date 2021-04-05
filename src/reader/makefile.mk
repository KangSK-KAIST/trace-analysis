build/alibaba_reader.o: src/reader/alibaba_reader.cc
	mkdir -p build
	$(CC) $(CCFLAGS) -c -o build/alibaba_reader.o src/reader/alibaba_reader.cc

build/alibaba_full_reader.o: src/reader/alibaba_full_reader.cc
	mkdir -p build
	$(CC) $(CCFLAGS) -c -o build/alibaba_full_reader.o src/reader/alibaba_full_reader.cc