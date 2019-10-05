wr8: wr8.o
	gcc wr8.o -o wr8
wr8.o : wr8.c
	gcc -c wr8.c
clean:
	rm wr8.o

cleanall:
	find $(path) -type f -name "*.txt" -delete
	rm wr8 wr8.o

