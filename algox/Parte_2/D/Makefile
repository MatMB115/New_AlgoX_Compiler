# Martins's Makefile

# Comandos para Flex e Bison
FLEX = flex
BISON = bison

# Nome do executável
TARGET = algox

# Fontes do Flex e Bison
LEX_SOURCE = tokenizer.lex
YACC_SOURCE = parser.y

# Arquivos gerados pelo Flex e Bison
LEX_OUTPUT = lex.yy.c
YACC_OUTPUT = parser.tab.c
YACC_HEADER = parser.tab.h

# Lista de arquivos de entrada na pasta exemplos
INPUT_FILES := $(wildcard ../exemplos/*.in)

all: $(TARGET)

$(TARGET): $(LEX_OUTPUT) $(YACC_OUTPUT)
	gcc -o $(TARGET) $(LEX_OUTPUT) $(YACC_OUTPUT) -lfl -ly

$(LEX_OUTPUT): $(LEX_SOURCE) $(YACC_OUTPUT)
	$(FLEX) $(LEX_SOURCE)

$(YACC_OUTPUT): $(YACC_SOURCE)
	$(BISON) -d $(YACC_SOURCE)

clean:
	rm -f $(LEX_OUTPUT) $(YACC_OUTPUT) $(YACC_HEADER) $(TARGET)

run: $(TARGET)
	@for file in $(INPUT_FILES); do \
		echo "Executando analisador do AlgoX para o exemplo $$file:"; \
		./$(TARGET) < $$file; \
	done