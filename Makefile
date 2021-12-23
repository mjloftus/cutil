vector: vector.c main.c
	gcc -o test.a vector.c main.c

test: ./test/test_vector.c
	gcc -o run_tests ./test/test_vector.c -lcheck
	./run_tests

.PHONY: test

clean:
	rm run_tests
