build/dependent_saver.o: src/saver/dependent_saver.cc
	mkdir -p build
	$(CC) $(CCFLAGS) -c -o build/dependent_saver.o src/saver/dependent_saver.cc