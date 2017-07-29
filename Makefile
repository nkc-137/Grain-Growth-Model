output: new.o
	gcc new.o -o executable -lm
new.o: new.c set.h voronoi.h
	gcc -c new.c
clean:
	rm -f *.o executable
run:
	./executable
