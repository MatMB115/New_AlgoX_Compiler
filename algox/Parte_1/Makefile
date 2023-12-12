CC = gcc
CFLAGS = -pedantic-errors
LDFLAGS = 

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
LEX_FILE = *.lex
LEX_OUTPUT = lex.yy.c
EXECUTABLE = main.exe

EXAMPLES_DIR = exemplos
TOKENS_DIR = tokens

# Lista de arquivos de entrada dinâmica
EXAMPLE_FILES = $(wildcard $(EXAMPLES_DIR)/*.in)
TOKEN_FILES = $(patsubst $(EXAMPLES_DIR)/%.in, $(TOKENS_DIR)/%.out, $(EXAMPLE_FILES))

all: $(EXECUTABLE)
	$(foreach token_file, $(TOKEN_FILES), ./$(EXECUTABLE) < $(patsubst $(TOKENS_DIR)/%.out, $(EXAMPLES_DIR)/%.in, $(token_file)) > $(token_file);)

$(EXECUTABLE): $(OBJECTS) $(LEX_OUTPUT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(LEX_OUTPUT): $(LEX_FILE)
	flex $(LEX_FILE)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o

cleanall: clean
	rm -f $(EXECUTABLE) $(LEX_OUTPUT) $(TOKEN_FILES) main.exe lex.yy.c

run: $(EXECUTABLE)
	./$(EXECUTABLE)