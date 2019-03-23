include ../incl.mk

unit_test :


mem_test :


var_array_test : var_array_test.o
	$(CC) -o var_array_test var_array_test.o

var_array_test.o : var_array_test.c variable_array.h
	$(CC) -c var_array_test.c

clean :
	rm var_array_test.o
	rm var_array_test

memcheck : var_array_test
	valgrind --leak-check=full ./var_array_test
