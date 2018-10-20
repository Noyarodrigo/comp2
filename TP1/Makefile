CFLAGS=-Wall
dividir: dividir.c
	gcc -o dividir dividir.c -lm

unir: unir.c
	gcc -o unir unir.c -lm

test:
	./dividir -n 3 -i CONSIGNA -o n;./unir -i n -o N;./dividir -s 400 -i CONSIGNA -o s ;./unir -i s -o S;diff CONSIGNA N; diff CONSIGNA S

clean:	
	rm s-* n-* N S

