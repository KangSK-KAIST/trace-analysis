build/analyzer.o: build/general_analyzer.o
	cp build/general_analyzer.o build/analyzer.o

build/general_analyzer.o: src/analyzer/general_analyzer.cc
	mkdir -p build
	$(CC) $(CCFLAGS) -c -o build/general_analyzer.o src/analyzer/general_analyzer.cc