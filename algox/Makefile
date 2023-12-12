# Martin's Makefile

CC = gcc
CFLAGS = -pedantic-errors
LDFLAGS = 

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
LEX_FILE = *.lex
LEX_OUTPUT = lex.yy.c
EXECUTABLE = main.exe

all: $(EXECUTABLE)
	./$(EXECUTABLE) < programas/fatorial.in > parser/fatorial.out
	./$(EXECUTABLE) < programas/lista.in > parser/lista.out
$(EXECUTABLE): $(OBJECTS) $(LEX_OUTPUT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(LEX_OUTPUT): $(LEX_FILE)
	flex $(LEX_FILE)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o

cleanall: clean
	rm -f $(EXECUTABLE) $(LEX_OUTPUT) parser/fatorial.out parser/lista.out

run: $(EXECUTABLE)
	./$(EXECUTABLE)
