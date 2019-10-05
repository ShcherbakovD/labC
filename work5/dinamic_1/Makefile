wr5_2:wr5_2.c str_option.c
	gcc -c -fPIC str_option.c
	gcc -shared str_option.o -o libstr_option.so
	gcc -c wr5_2.c
	gcc wr5_2.o -L. -lstr_option -o wr5_2
clean:
	rm str_option.o
cleanall:
	rm str_option.o wr5_2 libstr_option.so wr5_2.o
