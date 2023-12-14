# ALGOX - Análise Léxica e Sintática
Conforme as diretrizes propostas para execução do projeto 1, esse trabalho é constítuido de três etapas:

 - [x] Análise Léxica - implemente um analisador léxico para a linguagem Algox utilizando flex;
 - [x] Construção da Gramática | Árvore Sintática - projete uma estrutura de árvore sintática para Algox apropriada para a geração por um analisador sintático;
 - [x] Implemente um analisador sintático descendente para Algox;

## Análise Léxica
Para desenvolver o analisador léxico utilizou-se:

    Flex 2.6.4
    GNU Make 4.4.1
    GCC 13.2.1
    IDE VSCode

Os programas exemplo fornecidos pelo documento do projeto estão na pasta [exemplos](/algox/Parte_1/exemplos/), os arquivos .in são processados pelo analisador léxico e resultam nos arquivo de saída .out com os tokens na pasta [tokens](/algox/Parte_1/tokens/). Os arquivos .out possuem a sequência de tokens necessários para a execução da próxima etapa.

Os processos de compilação e execução foram automatizados utilizando um makefile. Todavia, é possível realizar a compilação do Flex e do programa em C pelo GCC via terminal.

## Construção da Gramática | Árvore Sintática
### Gramática desenvolvida para a linguagem Algox
    ALGOX → PROGRAMA ID INICIO COMENT DECLARACOES COMENT ALGORITMO FIM
    DECLARACOES → TIPO ID DECLARACOES’ DECLARACOES | ε
    DECLARACOES’ → VIRGULA ID DECLARACOES’ | ε
    ALGORITMO → LER | ESCREVER | ATRIBUI | COND_SE | COND_ENQUANTO | ε
    LER → LEIA ID LER’ ALGORITMO
    LER’ → VIRGULA ID LER’ | ε
    ESCREVER → ESCREVA LITERAL VIRGULA ID ALGORITMO | ESCREVA ID VIRGULA LITERAL ALGORITMO
    ATRIBUI → ID ATRIB EXPR ALGORITMO
    EXPR → ABRE_PAR EXPR FECHA_PAR | NUMERO_INT | NUMERO_REAL | ID | ID OPERADOR ID
    OPERADOR → SOMA | SUB | DIV | MULT
    COND_SE → SE EXPR_COND ENTAO ALGORITMO FIM_SE
    EXPR_COND → NEGACAO EXPR RELACIONAL EXPR BOOLEANO | EXPR RELACIONAL EXPR BOOLEANO
    BOOLEANO → OU EXPR_COND | E EXPR_COND | ε
    RELACIONAL→ MENOR_OU_IGUAL | IGUAL
    COND_ENQUANTO→ ENQUANTO EXPR_COND ALGORITMO FIM_ENQUANTO
    NEGAGAO → “.N.”
    PROGRAMA → "PROGRAMA"
    INICIO → "INICIO"
    COMENT → ABRE_COL LITERAL FECH_COL
    FIM → "FIM"
    TIPO → "INTEIRO" | "REAL" | "CADEIA" | "CARACTER" | "LISTA_INT" | "LISTA_REAL"
    ID → LETRA (DIGITO | NUMERO)* | LETRA (DIGITO | NUMERO)* ABRE_COL DIGITO FECHA_COL
    VIRGULA → ","
    LEIA → "LEIA"
    ESCREVA → "ESCREVA"
    LITERAL → (LETRA | DIGITO)*
    ATRIB → ":="
    ABRE_PAR → "("
    FECHA_PAR → ")"
    ABRE_COL → "["
    FECHA_COL → "]"
    NUMERO_INT → (DIGITO)+
    NUMERO_REAL → (DIGITO)+ "." (DIGITO)*
    SOMA → "+"
    SUB → "-"
    MULT → "*"
    DIV → "/"
    SE → "SE"
    ENTAO → "ENTAO"
    FIM_SE → "FIM_SE
    MENOR_OU_IGUAL → ".M."
    IGUAL → ".I."
    OU → ".O."
    E → ".E."
    FIM_ENQUANTO → "FIM_ENQUANTO"
    LETRA → a-zA-Z
    DIGITO → 0-9

### Árvore sintática obtida
![árvore](/algox/Parte_1/arvore.png)

## Analisador Sintático Descendente
O analisador sintático foi implementado em C.

## Instruções para execução

```bash

# ANTES DE EXECUTAR O PROJETO, se criou arquivos residuais de uma execução anterior, limpe esses arquivo com o comando abaixo no diretório ALGOX

$ make cleanall

# Na raiz do projeto execute o make

$ make

# A análise léxica ocorrerá com Flex gerando os dois arquivos de saída na pasta parser
# Abra esse diretório
$ cd parser

# Execute o makefile presente na pasta do parser para realizar a análise sintática
$ make

```
***
    Matheus Martins Batista - 2019005687 - Compiladores