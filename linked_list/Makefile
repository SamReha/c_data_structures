ll_test : ll_test.o
	gcc -o ll_test ll_test.o -g

ll_test.o : ll_test.c double_linked_list.h
	gcc -c ll_test.c -g

clean :
	rm ll_test.o
	rm ll_test

memcheck : ll_test
	valgrind --leak-check=full ./ll_test
