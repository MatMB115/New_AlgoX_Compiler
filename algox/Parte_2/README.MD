# ALGOX - Análise Léxica e Sintática Ascendente

## Construção da Gramática
     De acordo com o Trabalho proposto, deve-se estruturar  a gramática referente a linguagem ALGOX para a realização dos itens D, E, F e G. A gramática desenvolvida para AlgoX está presente no seção abaixo:
### Gramática AlgoX
    ALGOX → PROGRAMA VARIAVEL INICIO DECLARACOES ALGORITMO FIM

    DECLARACOES → TIPO_UNICO VARIAVEL DECLARACOES_REC DECLARACOES 
    | TIPO_LISTA VARIAVEL_LISTA DECLARACOES_LISTA_REC DECLARACOES | ε

    DECLARACOES_REC → VIRGULA VARIAVEL DECLARACOES_REC | ε

    DECLARACOES_LISTA_REC → VIRGULA VARIAVEL_LISTA DECLARACOES_LISTA_REC | ε

    ALGORITMO → LER | ESCREVER | ATRIBUI | COND_SE | COND_ENQUANTO | ε

    LER → LEIA VARIAVEL LER_REC ALGORITMO | LEIA VARIAVEL_LISTA LER_LISTA_REC ALGORITMO
    
    LER_REC → VIRGULA VARIAVEL LER_REC | ε

    LER_LISTA_REC → VIRGULA VARIAVEL_LISTA LER_LISTA_REC | ε
    
    ESCREVER → ESCREVA VARIAVEL ALGORITMO | ESCREVA CADEIA ALGORITMO | ESCREVA VARIAVEL_LISTA ALGORITMO 
    | ESCREVA CADEIA VIRGULA VARIAVEL ALGORITMO | ESCREVA VARIAVEL VIRGULA CADEIA ALGORITMO 
    | ESCREVA VARIAVEL_LISTA VIRGULA CADEIA ALGORITMO | ESCREVA VARIAVEL_LISTA VIRGULA VARIAVEL ALGORITMO 
    | ESCREVA VARIAVEL_LISTA VIRGULA VARIAVEL_LISTA ALGORITMO

    ATRIBUI → VARIAVEL OPERADOR_ATRIBUICAO EXPRE ALGORITMO | VARIAVEL_LISTA OPERADOR_ATRIBUICAO EXPRE ALGORITMO
    
    EXPRE → ABRE_PAR EXPRE FECHA_PAR | CONSTANTE_INTEIRA | CONSTANTE_REAL | VARIAVEL 
    | VARIAVEL OPERADOR_ARITMETICO VARIAVEL VARIAVEL OPERADOR_ARITMETICO CONSTANTE_INTEIRA 
    | VARIAVEL OPERADOR_ARITMETICO CONSTANTE_REAL | CONSTANTE_INTEIRA OPERADOR_ARITMETICO CONSTANTE_INTEIRA 
    | CONSTANTE_REAL OPERADOR_ARITMETICO CONSTANTE_REAL | CONSTANTE_INTEIRA OPERADOR_ARITMETICO VARIAVEL 
    | CONSTANTE_REAL OPERADOR_ARITMETICO VARIAVEL

    OPERADOR_ARITMETICO →  OPERADOR_ADICAO | OPERADOR_DIVISAO | OPERADOR_PRODUTO | OPERADOR_SUBTRACAO

    COND_SE → SE EXPRE_COND ENTAO ALGORITMO FIM_SE ALGORITMO

    EXPRE_COND → OPERADOR_NOT EXPRE RELACIONAL EXPRE BOOLEANO | EXPRE RELACIONAL EXPRE BOOLEANO

    BOOLEANO → OPERADOR_OR EXPRE_COND | OPERADOR_AND EXPRE_COND | ε

    RELACIONAL → OPERADOR_MENOR_IGUAL | OPERADOR_IGUAL

    COND_ENQUANTO → ENQUANTO EXPRE_COND ALGORITMO FIM_ENQUANTO ALGORITMO

    TIPO_UNICO → TIPO_CADEIA | TIPO_CARACTER | TIPO_INTEIRO | TIPO_REAL

    TIPO_LISTA → TIPO_LISTA_REAL | TIPO_LISTA_INT

## Item D)
Implementação com Yacc/Bison do analisador sintático ascendente está presente na pasta [D](/algox/Parte_2/D/). Para executar a parte D do projeto, deve-se seguir as instruções abaixo:

```bash

# Na raiz do projeto execute o make para compilar o FLEX, Bison/Yacc e o programa com GCC

$ make

# Após compilar poderá executar o programa diretamente (recomenda-se passar o caminho do arquivo do programa exemplo)

$ ./algox < ../exemplos/fatorial.in

# Para facilitar a execução dos exemplos, pode-se utilizar o comando abaixo

$ make run

# Se desejar limpar os arquivos resíduais da compilação poderá executar

$ make clean

```

## Item E) - F) - G)
Implementação do analisador semântido + tabela de símbolos está presente na pasta [E_&_F](/algox/Parte_2/E_F_G). Para executar, deve-se seguir as instruções abaixo:

```bash

# Na raiz do projeto execute o make para compilar o FLEX, Bison/Yacc, a tabela de simbolos e o programa com GCC

$ make

# Após compilar poderá executar o programa diretamente (recomenda-se passar o caminho do arquivo do programa exemplo)

$ ./algox < ../exemplos/fatorial.in

# Para facilitar a execução dos exemplos, pode-se utilizar o comando abaixo

$ make run

# Se desejar limpar os arquivos resíduais da compilação poderá executar

$ make clean

```


***
    Alison Mesquita Maciel - 2018011367
    Gabriel Ciriaco Fortiniano - 2021009763
    Matheus Martins Batista - 2019005687
