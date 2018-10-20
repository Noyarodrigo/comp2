CFLAGS= -Wall
all: ejecutable
tp3: main.c mayus.c imprimir.c
	gcc $(CFLAGS) -o $@ $^ -pthread

test: tp3 
	./tp3 -f big.txt
	
clean:	
	rm tp3 *.o
