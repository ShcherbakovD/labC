wr9: wr9.o
	gcc wr9.o -o wr9
wr9.o : wr9.c
	gcc -c wr9.c
clean:
	rm wr9.o

cleanall:
	find $(path) -type f -name "*.txt" -delete
	rm wr9 wr9.o
