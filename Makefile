libcutil: ./src/vector.c
	gcc -c -Wall -Werror -fpic ./src/vector.c
	gcc -shared -o libcutil.so vector.o

test: ./test/test_vector.c ./src/vector.c
	gcc -Wall -Werror -o run_tests ./test/test_vector.c ./src/vector.c -lcheck
	./run_tests

.PHONY: test

clean:
	rm run_tests *.o *.so
