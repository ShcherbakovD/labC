wr5_3: libstr_option.so
	gcc wr5_3.c -o wr5_3 -ldl

libstr_option.so: str_option.o
	gcc -shared str_option.o -o libstr_option.so

str_option.o: str_option.c
	gcc -c -fPIC str_option.c

clean:
	rm str_option.o
	
cleanall:
	rm str_option.o wr5_3 libstr_option.so
