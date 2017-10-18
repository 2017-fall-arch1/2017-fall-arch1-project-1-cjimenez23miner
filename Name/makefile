all: pocahontas

CFLAGS=-g -O3

# Symbols helpful for understanding the productions
#   $@ is the production's target
#   $^ are the production's prerequisites

pocahontas: pocahontas.c
	cc -o $@ $^

pocahontas.o: pocahontas.c pocahontas.h
	cc -c $(CFLAGS) pocahontas.c

clean:
	rm -f *.o pocahontas

demo: pocahontas
	./pocahontas
