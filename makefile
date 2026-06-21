Target: add.o apc.o div.o main.o mul.o sub.o mod.o pow.o
	gcc -o a.out add.o apc.o div.o main.o mul.o sub.o mod.o pow.o

add.o: add.c
	gcc -c add.c

apc.o: apc.c
	gcc -c apc.c

div.o: div.c
	gcc -c div.c

main.o: main.c
	gcc -c main.c

mul.o: mul.c
	gcc -c mul.c

sub.o: sub.c
	gcc -c sub.c

mod.o: mod.c
	gcc -c mod.c

pow.o: pow.c
	gcc -c pow.c

clean:
	rm -f *.o a.out *.exe