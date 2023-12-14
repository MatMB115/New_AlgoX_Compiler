%{

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "symbol.tab.h"
  #include "parser.tab.h"
  extern FILE *yyin;
	extern FILE *yyout;
  extern int currentType;
  int lineno = 1;

  void yyerror();
  int yywrap(void) { return 1; }
%}

ABRE                     "("
ENQUANTO                 "ENQUANTO"
ENTAO                    "ENTAO"
ESCREVA                  "ESCREVA"
FECHA                    ")"
FIM                      "FIM"
FIM_ENQUANTO             "FIM_ENQUANTO"
FIM_SE                   "FIM_SE"
INICIO                   "INICIO"
LEIA                     "LEIA"
OPERADOR_ADICAO          "+"
OPERADOR_AND             ".E."
OPERADOR_ATRIBUICAO      ":="
OPERADOR_DIVISAO         "\\"
OPERADOR_IGUAL           ".I."
OPERADOR_MENOR_IGUAL     ".M."
OPERADOR_NOT             ".N."
OPERADOR_OR              ".OU."
OPERADOR_PRODUTO         "*"
OPERADOR_SUBTRACAO       "-"
PROGRAMA                 "PROGRAMA"
SE                       "SE"
TIPO_CADEIA              "CADEIA"
TIPO_CARACTER            "CARACTER"
TIPO_INTEIRO             "INTEIRO"
TIPO_LISTA_INT           "LISTA_INT"
TIPO_LISTA_REAL          "LISTA_REAL"
TIPO_REAL                "REAL"
VIRGULA                  ","
DIGITO                   ([0-9])
CONSTANTE_INTEIRA        ({DIGITO}+)
CONSTANTE_REAL           ({DIGITO}+(","{DIGITO}+)?)
LETRA                    ([a-zA-Z])
PALAVRA                  ([a-zA-Z_-])
VARIAVEL                 ({LETRA}({PALAVRA}|{CONSTANTE_INTEIRA})*)
VARIAVEL_LISTA           ({VARIAVEL}"["({VARIAVEL}|{CONSTANTE_INTEIRA})"]")
CADEIA                   (\'[^'\r\n]+\')
COMENTARIO               (\{.*\})
WHITESPACES              ([ \t]+)
NEWLINE                  (\r\n|\n|\r)

%%

{ABRE}                     { return ABRE_PAR; }
{ENQUANTO}                 { return ENQUANTO; }
{ENTAO}                    { return ENTAO; }
{ESCREVA}                  { return ESCREVA; }
{FECHA}                    { return FECHA_PAR; }
{FIM_ENQUANTO}             { return FIM_ENQUANTO; }
{FIM_SE}                   { return FIM_SE; }
{FIM}                      { return FIM; }
{INICIO}                   { return INICIO; }
{LEIA}                     { return LEIA; }
{OPERADOR_ADICAO}          { return OPERADOR_ADICAO; }
{OPERADOR_AND}             { return OPERADOR_AND; }
{OPERADOR_ATRIBUICAO}      { return OPERADOR_ATRIBUICAO; }
{OPERADOR_DIVISAO}         { return OPERADOR_DIVISAO; }
{OPERADOR_IGUAL}           { return OPERADOR_IGUAL; }
{OPERADOR_MENOR_IGUAL}     { return OPERADOR_MENOR_IGUAL; }
{OPERADOR_NOT}             { return OPERADOR_NOT; }
{OPERADOR_OR}              { return OPERADOR_OR; }
{OPERADOR_PRODUTO}         { return OPERADOR_PRODUTO; }
{OPERADOR_SUBTRACAO}       { return OPERADOR_SUBTRACAO; }
{PROGRAMA}                 { return PROGRAMA; }
{SE}                       { return SE; }
{TIPO_CADEIA}              { return TIPO_CADEIA; }
{TIPO_CARACTER}            { return TIPO_CARACTER; }
{TIPO_INTEIRO}             { return TIPO_INTEIRO; }
{TIPO_LISTA_INT}           { return TIPO_LISTA_INT; }
{TIPO_LISTA_REAL}          { return TIPO_LISTA_REAL; }
{TIPO_REAL}                { return TIPO_REAL; }
{VIRGULA}                  { return VIRGULA; }
{CONSTANTE_INTEIRA}        { return CONSTANTE_INTEIRA; }
{CONSTANTE_REAL}           { return CONSTANTE_REAL; }
{VARIAVEL}                 { insert(yytext, strlen(yytext), indefinido, lineno);
                              return VARIAVEL; }
{VARIAVEL_LISTA}           { insert(yytext, strlen(yytext), indefinido, lineno);
                              return VARIAVEL_LISTA; }
{CADEIA}                   { return CADEIA; }
{COMENTARIO}               // Pula os trechos comentados
{WHITESPACES}              // Pula os espaços em branco
{NEWLINE}                  { lineno += 1; }

%%
