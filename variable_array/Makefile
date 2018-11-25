var_array_test : var_array_test.o
	gcc -o var_array_test var_array_test.o -g

var_array_test.o : var_array_test.c variable_array.h
	gcc -c var_array_test.c -g

clean :
	rm var_array_test.o
	rm var_array_test

memcheck : var_array_test
	valgrind --leak-check=full ./var_array_test
