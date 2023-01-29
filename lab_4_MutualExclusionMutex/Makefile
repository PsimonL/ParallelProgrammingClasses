# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

start: clean pub

# zaleznosci i komendy
program: pub.o 
	$(LOADER) $(OPT) pub.o -o pub $(LIB)

# jak uzyskac plik fork.o ?
program.o: pub.c
	$(CCOMP) -c $(OPT) pub.c $(INC) 

clean:
	rm -f *.o pub
