build/parser.o: src/parser/general_parser.cc
	mkdir -p build
	$(CC) $(CCFLAGS) -c -o build/parser.o src/parser/general_parser.cc