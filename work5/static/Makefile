wr5_1: libstr_option.a
	gcc wr5_1.c -L. -lstr_option -o wr5_1

libstr_option.a: str_option.o
	ar rc libstr_option.a str_option.o
	ranlib libstr_option.a

str_option.o: str_option.c
	gcc -c str_option.c

clean:
	rm str_option.o
	
cleanall:
	rm str_option.o wr5_1 libstr_option.a

