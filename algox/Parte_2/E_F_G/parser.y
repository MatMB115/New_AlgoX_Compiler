%define parse.error verbose
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.tab.h"

extern FILE *yyin;
extern FILE *yyout;
extern int lineno;
extern int yylex();
extern char *yytext;

int currentType;

void yyerror (const char *s) {
	extern int yylineno;
  	printf("Erro %s na linha %d\n", s, yylineno+1);
}

int yyparse(void);

int yylex(void);

int main() {
	// inicializa tabela hash
	init_hash_table();
	
	yyparse();

	// armazena a tabela de símbolos em um arquivo de saída
	yyout = fopen("symbols_table.out", "a");
	symtab_dump(yyout);
	fclose(yyout);	

	return 0;
}
%}

%token ABRE_PAR            ENQUANTO
%token ENTAO               ESCREVA
%token FECHA_PAR           FIM_ENQUANTO
%token FIM_SE              FIM
%token INICIO              LEIA
%token OPERADOR_ADICAO     OPERADOR_AND
%token OPERADOR_ATRIBUICAO OPERADOR_DIVISAO
%token OPERADOR_IGUAL      OPERADOR_MENOR_IGUAL
%token OPERADOR_NOT        OPERADOR_OR
%token OPERADOR_PRODUTO    OPERADOR_SUBTRACAO
%token PROGRAMA            SE
%token TIPO_CADEIA         TIPO_CARACTER
%token TIPO_INTEIRO        TIPO_LISTA_INT
%token TIPO_LISTA_REAL     TIPO_REAL
%token VIRGULA             CONSTANTE_INTEIRA
%token CONSTANTE_REAL      VARIAVEL
%token VARIAVEL_LISTA      CADEIA

%union {
	int ival;
}

%type <ival> TIPO_LISTA TIPO_UNICO

%%

INIT: 		ALGOX {printf("\nSintaxe correta!\n");}

ALGOX      : PROGRAMA VARIAVEL INICIO  DECLARACOES ALGORITMO FIM
;

DECLARACOES:  TIPO_UNICO VARIAVEL DECLARACOES_REC DECLARACOES 
			| TIPO_LISTA VARIAVEL_LISTA DECLARACOES_LISTA_REC DECLARACOES 
			| 
;

DECLARACOES_REC: VIRGULA VARIAVEL DECLARACOES_REC 
				|
;

DECLARACOES_LISTA_REC: 	VIRGULA VARIAVEL_LISTA DECLARACOES_LISTA_REC 
						|
;

TIPO_UNICO:   TIPO_INTEIRO { currentType = 1; }
			| TIPO_REAL { currentType = 2; }
			| TIPO_CARACTER { currentType = 3; }
			| TIPO_CADEIA { currentType = 3; }
;

TIPO_LISTA:   TIPO_LISTA_INT { currentType = 51; }
			| TIPO_LISTA_REAL { currentType = 52; }
;

ALGORITMO:    LER
			| ESCREVER
			| ATRIBUI
			| COND_SE
			| COND_ENQUANTO
			|
;

LER: 		  LEIA VARIAVEL LER_REC ALGORITMO
            | LEIA VARIAVEL_LISTA LER_LISTA_REC ALGORITMO
;

LER_REC:      VIRGULA VARIAVEL LER_REC
			|
;

LER_LISTA_REC: VIRGULA VARIAVEL_LISTA LER_LISTA_REC
			|
;

ESCREVER:      ESCREVA CADEIA ALGORITMO
			|  ESCREVA VARIAVEL ALGORITMO
			|  ESCREVA VARIAVEL_LISTA ALGORITMO
			|  ESCREVA CADEIA VIRGULA VARIAVEL ALGORITMO
			|  ESCREVA VARIAVEL VIRGULA CADEIA ALGORITMO
			|  ESCREVA VARIAVEL_LISTA VIRGULA CADEIA ALGORITMO
			|  ESCREVA VARIAVEL_LISTA VIRGULA VARIAVEL ALGORITMO
			|  ESCREVA VARIAVEL_LISTA VIRGULA VARIAVEL_LISTA ALGORITMO
;

ATRIBUI:      VARIAVEL OPERADOR_ATRIBUICAO EXPRE ALGORITMO
			| VARIAVEL_LISTA OPERADOR_ATRIBUICAO EXPRE ALGORITMO
;

EXPRE:		   ABRE_PAR EXPRE FECHA_PAR
			|  CONSTANTE_INTEIRA
			|  CONSTANTE_REAL
			|  VARIAVEL
			|  VARIAVEL OPERADOR_ARITMETICO VARIAVEL
			|  VARIAVEL OPERADOR_ARITMETICO CONSTANTE_INTEIRA
			|  VARIAVEL OPERADOR_ARITMETICO CONSTANTE_REAL
			|  CONSTANTE_INTEIRA OPERADOR_ARITMETICO CONSTANTE_INTEIRA
			|  CONSTANTE_REAL OPERADOR_ARITMETICO CONSTANTE_REAL
			|  CONSTANTE_INTEIRA OPERADOR_ARITMETICO VARIAVEL
			|  CONSTANTE_REAL OPERADOR_ARITMETICO VARIAVEL
;

OPERADOR_ARITMETICO:  OPERADOR_ADICAO
					| OPERADOR_SUBTRACAO
					| OPERADOR_PRODUTO
					| OPERADOR_DIVISAO
;

COND_SE:      SE EXPRE_COND ENTAO ALGORITMO FIM_SE ALGORITMO
;

EXPRE_COND:   OPERADOR_NOT EXPRE RELACIONAL EXPRE BOOLEANO
			| EXPRE RELACIONAL EXPRE BOOLEANO
;

BOOLEANO:	 OPERADOR_AND EXPRE_COND
			| OPERADOR_OR EXPRE_COND
			|
;

RELACIONAL:   OPERADOR_IGUAL
			| OPERADOR_MENOR_IGUAL
;

COND_ENQUANTO: ENQUANTO EXPRE_COND ALGORITMO FIM_ENQUANTO ALGORITMO
;

%%

