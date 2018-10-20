CC= gcc
CFLAGS= -Wall
TARGETS= cliente servidor

all: $(TARGETS)

cliente: cliente.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

servidor: servidor.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

test: cliente servidor
	./servidor
	./cliente -u http://www.um.edu.ar -t telefono
		
clean:	
	rm $(TARGETS) *.o
