%option noyywrap

%{
    #include <stdio.h>
    //Matheus Martins Batista - 2019005687
%}

LETRAS [a-zA-Z_]\w*
DIGITOS [0-9]+
COMENTARIO \{[^}]*\}
ID ({LETRAS}({LETRAS}|{DIGITOS})*|{LETRAS}({LETRAS}|{DIGITOS})*\[{DIGITOS}+\])
QUEBRALINHA \n

%%

PROGRAMA" "                     { printf("[PROGRAMA]\n");}
INICIO                          { printf("[INICIO]\n");}
FIM                             { printf("[FIM]\n");}
LEIA" "                         { printf("[LEIA]\n"); }
ESCREVA" "                      { printf("[ESCREVA]\n"); }
'[^']*'                         { printf("[LITERAL]\n"); }
LISTA_INT" "                    { printf("[LISTA_INT]\n"); }
LISTA_REAL" "                   { printf("[LISTA_REAL]\n"); }
\[                              { printf("[ABRE_COL]\n"); }
\]                              { printf("[FECHA_COL]\n"); }
\(                              { printf("[ABRE_PAR]\n"); }
\)                              { printf("[FECHA_PAR]\n"); }
SE                              { printf("[SE]\n"); }
ENTAO                           { printf("[ENTAO]\n"); }
FIM_SE                          { printf("[FIM_SE]\n"); }
ENQUANTO                        { printf("[ENQUANTO]\n"); }
FIM_ENQUANTO                    { printf("[FIM_ENQUANTO]\n"); }
{DIGITOS}+                    { printf("[NUMERO_INT]\n"); }
{DIGITOS}+"."{DIGITOS}+     { printf("[NUMERO_REAL]\n"); }
{COMENTARIO}                    { printf("[COMENT]\n");}
INTEIRO" "                      { printf("[INTEIRO]\n"); }
{ID}(,{ID})*                    { printf("[ID]\n"); }
REAL" "                         { printf("[REAL]\n"); }
CARACTER" "                     { printf("[CARACTER]\n"); }
CADEIA" "                       { printf("[CADEIA]\n"); }
,                               { printf("[VIRGULA]\n"); }
":="                            { printf("[ATRIB]\n"); }
"+"                             { printf("[SOMA]\n"); }
"-"                             { printf("[SUB]\n"); }
"*"                             { printf("[MULT]\n"); }
"/"                             { printf("[DIV]\n"); }
".M."                           { printf("[MENOR_OU_IGUAL]\n"); }
".I."                           { printf("[IGUAL]\n"); }
".O."                           { printf("[OU]\n"); }
".E."                           { printf("[E]\n"); }
".N."                           { printf("[NEGACAO]\n"); }
.                               { /* Outros caracteres */ }
{QUEBRALINHA}                   { /* Ignorar as quebras de linha*/ }

%%
int main(int argc, char *argv[]) {
    yylex();
    return 0;
}
