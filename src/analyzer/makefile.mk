build/analyzer.o: src/analyzer/general_analyzer.cc
	mkdir -p build
	$(CC) $(CCFLAGS) -c -o build/analyzer.o src/analyzer/general_analyzer.cc