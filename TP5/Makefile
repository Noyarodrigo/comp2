CC= gcc
CFLAGS= -Wall -g
LDLIBS=-pthread
TARGETS= servidor

all: $(TARGETS)

servidor: main.c obtenerargumentos.c respuesta.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

test: cliente servidor
	./servidor

clean:
	rm $(TARGETS) *.o servidor
