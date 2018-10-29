CC= gcc
CFLAGS= -Wall -pthread
LDFLAGS=-pthread
TARGETS= servidor

all: $(TARGETS)

servidor: main.c obtenerargumentos.c parse.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS) $(LDFLAGS)

test: cliente servidor
	./servidor

clean:
	rm $(TARGETS) *.o servidor
