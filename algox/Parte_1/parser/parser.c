#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Matheus Martins Batista - 2019005687

void ERRO(char *token){
    printf("ERRO\n %s", token);
    exit(1);
}

char *proxtoken(FILE *arquivo) {
    char linha[1024];
    if (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remova o caractere de nova linha (se houver)
        if (linha[strlen(linha) - 1] == '\n') {
            linha[strlen(linha) - 1] = '\0';
        }
        // Aloque dinamicamente memória para armazenar a linha lida
        char *linha_dinamica = (char *)malloc(strlen(linha) + 1);
        strcpy(linha_dinamica, linha);
        printf("%s\n", linha_dinamica);
        return linha_dinamica;
    } else {
        return NULL;  // Retorna NULL se atingir o final do arquivo
    }
}

//TERMINAIS
int ID(char *token){
    if (strcmp(token, "[ID]") == 0) {
        return 1;
    }
    return 0;
}

int VIRGULA(char *token){
    if (strcmp(token, "[VIRGULA]") == 0) {
        return 1;
    }
    return 0;
}

int INICIO(char *token){
    if (strcmp(token, "[INICIO]") == 0) {
        return 1;
    }
    return 0;
}

int LEIA(char *token){
    if (strcmp(token, "[LEIA]") == 0) {
        return 1;
    }
    return 0;
}

int ESCREVA(char *token){
    if (strcmp(token, "[ESCREVA]") == 0) {
        return 1;
    }
    return 0;
}

int LITERAL(char *token){
    if (strcmp(token, "[LITERAL]") == 0) {
        return 1; 
    }
    return 0;
}

int ATRIB(char *token){
    if (strcmp(token, "[ATRIB]") == 0) {
        return 1; 
    }
    return 0;
}

void COMMENT(char *token, FILE *arquivo){
    if (strcmp(token, "[COMENT]") == 0){
        token = proxtoken(arquivo);
        COMMENT(token, arquivo);
    }
    token = proxtoken(arquivo);
    return;
}

int TIPO(char *token){
    if(strcmp(token, "[INTEIRO]") == 0)
        return 1;
    if(strcmp(token, "[REAL]") == 0)
        return 1;
    if(strcmp(token, "[CADEIA]") == 0)
        return 1;
    if(strcmp(token, "[CARACTER]") == 0)
        return 1;
    if(strcmp(token, "[LISTA_INT]") == 0)
        return 1;
    if(strcmp(token, "[LISTA_REAL]") == 0)
        return 1;

    return 0;       
}

int NUMERO_INT(char *token){
    if(strcmp(token, "[NUMERO_INT]") == 0)
        return 1;
    return 0;
}

int NUMERO_REAL(char *token){
    if(strcmp(token, "[NUMERO_REAL]") == 0)
        return 1;
    return 0;
}

int OPERADOR(char *token){
    if(strcmp(token, "[SOMA]") == 0)
        return 1;
    if(strcmp(token, "[SUB]") == 0)
        return 1;
    if(strcmp(token, "[MULT]") == 0)
        return 1;
    if(strcmp(token, "[DIV]") == 0)
        return 1;
    return 0;
}

int COND_SE(char *token){
    if(strcmp(token, "[SE]") == 0)
        return 1;
    return 0;
}

int COND_ENQUANTO(char *token){
    if(strcmp(token, "[ENQUANTO]") == 0)
        return 1;
    return 0;
}

int ENTAO(char *token){
    if(strcmp(token, "[ENTAO]") == 0)
        return 1;
    return 0;
}

int NEGACAO(char *token){
    if(strcmp(token, "[NEGACAO]") == 0)
        return 1;
    return 0;
}

int FIM_ENQUANTO(char *token){
    if(strcmp(token, "[FIM_ENQUANTO]") == 0)
        return 1;
    return 0;
}

int FIM_SE(char *token){
    if(strcmp(token, "[FIM_SE]") == 0)
        return 1;
    return 0;
}

int RELACIONAL(char *token){
    if(strcmp(token, "[MENOR_OU_IGUAL]") == 0)
        return 1;
    if(strcmp(token, "[IGUAL]") == 0)
        return 1;
    return 0;
}


int FIM(char *token){
    printf("FIM\n");
    if(strcmp(token, "[FIM]") == 0)
        return 1;
    return 0;
}

//Não terminais

int EXPR(char *token, FILE *arquivo){
    if(ID(token)){
        token = proxtoken(arquivo);
        if(OPERADOR(token)){
            token = proxtoken(arquivo);
            if(ID(token)){
                token = proxtoken(arquivo);
                return 1;
            }else{
                ERRO(token);
            }
        }
        return 1;
    }
    if(NUMERO_INT(token))
        return 1;
    if(NUMERO_REAL(token))
        return 1;
    if(NUMERO_INT(token))
        return 1;
    else
        return 0;
}

void DECLARACOES_LINHA(char *token, FILE *arquivo){
    printf("DECLARACOES_LINHA\n");
    if(VIRGULA(token)){
        token = proxtoken(arquivo);
        if(ID(token)){
            token = proxtoken(arquivo);
            DECLARACOES_LINHA(token, arquivo);
        }
    }
    return;
}

int DECLARACOES(char *token, FILE *arquivo){
    if(TIPO(token)){
        token = proxtoken(arquivo);
        if(ID(token)){
            token = proxtoken(arquivo);
            DECLARACOES_LINHA(token, arquivo);
            DECLARACOES(token, arquivo);
        }
    }
    return 1;
}

int LER(char *token, FILE *arquivo){
    if(VIRGULA(token)){
        token = proxtoken(arquivo);
        if(ID(token)){
            token = proxtoken(arquivo);
            LER(token, arquivo);
        }
    }
    return 1;
}

int BOOLEANO(char *token){
    if(strcmp(token, "[OU]") == 0)
        return 1;
    if(strcmp(token, "[E]") == 0)
        return 1;
    return 0;
}

void EXPR_COND(char *token, FILE *arquivo){
    if(NEGACAO(token)){
        token = proxtoken(arquivo);
        if(EXPR(token, arquivo)){
            token = proxtoken(arquivo);
            if(RELACIONAL(token)){
                token = proxtoken(arquivo);
                if(EXPR(token, arquivo)){
                    token = proxtoken(arquivo);
                    if(BOOLEANO(token)){
                        token = proxtoken(arquivo);
                        EXPR_COND(token, arquivo);
                    }
                }
            }
        }
    }
    if(EXPR(token, arquivo)){
        token = proxtoken(arquivo);
        if(RELACIONAL(token)){
            token = proxtoken(arquivo);
            if(EXPR(token, arquivo)){
                token = proxtoken(arquivo);
                if(BOOLEANO(token)){
                    token = proxtoken(arquivo);
                    EXPR_COND(token, arquivo);
                }
            }
        }
    }
}

void ALGORITMO(char *token, FILE *arquivo){
    
    if(LEIA(token)){
        token = proxtoken(arquivo);
        if(ID(token)){
            token = proxtoken(arquivo);
            LER(token, arquivo);
        }
    }
    if(ESCREVA(token)){
        token = proxtoken(arquivo);
        if(LITERAL(token)){
            token = proxtoken(arquivo);
            if(VIRGULA(token)){
                token = proxtoken(arquivo);
                if(ID(token)){
                    token = proxtoken(arquivo);
                    ALGORITMO(token, arquivo);
                }
            }
        }
        if(ID(token)){
            token = proxtoken(arquivo);
            if(VIRGULA(token)){
                token = proxtoken(arquivo);
                if(LITERAL(token)){
                    token = proxtoken(arquivo);
                    ALGORITMO(token, arquivo);
                }
            }
        }
    }
    if(ID(token)){
        token = proxtoken(arquivo);
        if(ATRIB(token)){
            token = proxtoken(arquivo);
            if(EXPR(token, arquivo)){
                token = proxtoken(arquivo);
                ALGORITMO(token, arquivo);
            }
        }
    }
    if(COND_SE(token)){
        token = proxtoken(arquivo);
        EXPR_COND(token, arquivo);
        token = proxtoken(arquivo);
        if(ENTAO(token)){
            token = proxtoken(arquivo);
            ALGORITMO(token, arquivo);
            FIM_SE(token);
        }
    }
    if(COND_ENQUANTO(token)){
        token = proxtoken(arquivo);
        EXPR_COND(token, arquivo);
        token = proxtoken(arquivo);
        ALGORITMO(token, arquivo);
        FIM_ENQUANTO(token);
    }
}


int ASD_ALGOX(char *token, FILE *arquivo){
    if (strcmp(token, "[PROGRAMA]") == 0) {
        token = proxtoken(arquivo);
        if(ID(token)){
            token = proxtoken(arquivo);
            if(INICIO(token)){
                token = proxtoken(arquivo);
                COMMENT(token, arquivo);
                token = proxtoken(arquivo);
                DECLARACOES(token, arquivo);
                token = proxtoken(arquivo);
                COMMENT(token, arquivo);
                token = proxtoken(arquivo);
                ALGORITMO(token, arquivo);
                token = proxtoken(arquivo);
            }
        }
        FIM(token);
    }else{
        ERRO(token);
    }
    return 0;
}

int main() {
    FILE *arquivo = fopen("fatorial.out", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char *token = proxtoken(arquivo);
    ASD_ALGOX(token, arquivo);

    free(token);  // Libere a memória alocada dinamicamente quando não for mais necessária

    fclose(arquivo);

    return 0;
}