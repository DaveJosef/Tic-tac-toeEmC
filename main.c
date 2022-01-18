/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

const char PONTOS_MAX = 2;
const char VAZIO = '.';

void zerarMatriz(char *matriz, int a, int l) {
    int i, j;
    for (i = 0; i < a; i++) {
        for (j = 0; j < l; j++) {
            matriz[i * l + j] = '.';
        }
    }
}

void imprimirMatriz(char *matriz, int a, int l) {
    int i, j;
    for (i = 0; i < a; i++) {
        for (j = 0; j < l; j++) {
            printf(" %c", matriz[i * l + j]);
        }
        printf("\n");
    }
}

void informarPlayer(char player) {
    printf("Vez do player %c:\n", player);
}

char trocarPlayer(char player) {
    switch (player) {
        case 'x':
            return 'o';
        case 'o':
            return 'x';
    }
}

int converterNumToInt(char numero) {
    return numero - 48;
}

void validarEscolha(char *matriz, int a, int l, int i, int j, char player) {
    if (matriz[i * l + j] != VAZIO) {
        printf(" Em %d, %d ja temos %c\n", i + 1, j + 1, trocarPlayer(player));
    }
}

int verificarCompletudeHor(char *matriz, int i, int a, int l, char player) {
    int j;
    for (j = 0; j < l; j++) {
        if (matriz[i * l + j] != player) {
            return 0;
        }
    }
    return 1;
}

int verificarCompletudeVer(char *matriz, int j, int a, int l, char player) {
    int i;
    for (i = 0; i < a; i++) {
        if (matriz[i * l + j] != player) {
            return 0;
        }
    }
    return 1;
}
/*
int verificarCompletudeDiagPrin(int iOff, int jOff, char *matriz, int tam, char player) {
    int i, j;
    for (i = 0 + iOff; i < tam - abs(jOff); i++) {
        j = i + jOff;
        if (matriz[i * tam + j] != player) {
            return 0;
        }
    }
    return 1;
}
*/
int verificarCompletudeDiagPrin(int i, int j, char *matriz, int a, int l, char player) {
    printf("\nDetectado %c em %d, %d\n", matriz[i * l + j], i, j);
    if (matriz[i * l + j] != player) return 0;
    if (i + 1 < a && j + 1 < l) {
        return verificarCompletudeDiagPrin(i + 1, j + 1, matriz, a, l, player);
    }
    return 1;
}
/*
int verificarCompletudeDiagSec(int iOff, int jOff, char *matriz, int tam, char player) {
    int i, j;
    j = tam - 1 + jOff;
    for (i = 0 + iOff; i < tam - abs(jOff); i++) {
        if (matriz[i * tam + j] != player) {
            return 0;
        }
        j--;
    }
    return 1;
}
*/
int verificarCompletudeDiagSec(int i, int j, char *matriz, int a, int l, char player) {
    printf("\nDetectado %c em %d, %d\n", matriz[i * l + j], i, j);
    if (matriz[i * l + j] != player) return 0;
    if (i + 1 < a && j - 1 >= 0) {
        return verificarCompletudeDiagSec(i + 1, j - 1, matriz, a, l, player);
    }
    return 1;
}

int verificarCompletude(char *matriz, int a, int l) {
    int i, j;
    for (i = 0; i < a; i++) {
        for (j = 0; j < l; j++) {
            if (matriz[i * l + j] == VAZIO)
                return 0;
        }
    }
    return 1;
}

int recuperarIndPlayer(char player) {
    switch (player) {
        case 'x':
            return 0;
        case 'o':
            return 1;
    }
}

void informarPlacar(char player, int *pontos) {
    printf("%d/%d x %d/%d\n", pontos[recuperarIndPlayer(player)], PONTOS_MAX, pontos[recuperarIndPlayer(trocarPlayer(player))], PONTOS_MAX);
}

void informarJogo(char *matriz, int a, int l, char player, int *pontos) {
    printf("Jogo: ");
    informarPlacar(player, pontos);
    imprimirMatriz(matriz, a, l);
}

void processarFim(char *matriz, int a, int l, int *pontos, char player) {
    if (pontos[0] >= PONTOS_MAX || pontos[1] >= PONTOS_MAX)
        printf("Parabéns! %c ganhou!", player);
    else if (verificarCompletude(matriz, a, l))
        printf("Deu vea!\n");
    /*
    if (PONTOS_MAX > 1)
        printf(" Com %d pontos!\n", pontos[recuperarIndPlayer(player)]);
    */
}

int somarPontos(char *matriz, int a, int l, int diagOffsetMax, char player) {
    int soma = 0;
    int i, j;
    for (i = 0; i < a; i++) {
        soma += verificarCompletudeHor(matriz, i, a, l, player);
    }
    for (j = 0; j < l; j++) {
        soma += verificarCompletudeVer(matriz, j, a, l, player);
    }
    soma += verificarCompletudeDiagPrin(0, 0, matriz, a, l, player);
    j = 0;
    for (i = 1; i <= diagOffsetMax; i++) {
        printf("\ni, j: %d, %d\n", i, j);
        soma += verificarCompletudeDiagPrin(i, j, matriz, a, l, player);
    }
    i = 0;
    for (j = 1; j <= diagOffsetMax; j++) {
        printf("\ni, j: %d, %d\n", i, j);
        soma += verificarCompletudeDiagPrin(i, j, matriz, a, l, player);
    }
    soma += verificarCompletudeDiagSec(0, l - 1, matriz, a, l, player);
    j = l - 1;
    for (i = 1; i <= diagOffsetMax; i++) {
        printf("\ni, j: %d, %d\n", i, j);
        soma += verificarCompletudeDiagSec(i, j, matriz, a, l, player);
    }
    i = 0;
    for (j = l - 1 - diagOffsetMax; j < l - 1; j++) {
        printf("\ni, j: %d, %d\n", i, j);
        soma += verificarCompletudeDiagSec(i, j, matriz, a, l, player);
    }
    printf("\nsoma de pontos de %c: %d\n", player, soma);
    return soma;
}

void rodarJogo(char *matriz, int a, int l, int player) {
    int pontos[2];
    pontos[0] = 0;
    pontos[1] = 0;
    do {
        char linhacoluna[2];
        informarJogo(matriz, a, l, player, pontos);
        informarPlayer(player);
        int i = 0;
        int j = 0;
        do {
            printf(" Informe linha e coluna nessa ordem e sem espaco: ");
            scanf("%s", linhacoluna);
            i = converterNumToInt(linhacoluna[0]) - 1;
            j = converterNumToInt(linhacoluna[1]) - 1;
            validarEscolha(matriz, a, l, i, j, player);
        } while(matriz[i * l + j] != VAZIO);
        matriz[i * l + j] = player;
        pontos[recuperarIndPlayer(player)] = somarPontos(matriz, a, l, a - 3, player);
        if (pontos[0] < PONTOS_MAX && pontos[1] < PONTOS_MAX && !verificarCompletude(matriz, a, l))
            player = trocarPlayer(player);
        system("clear");
    } while(pontos[0] < PONTOS_MAX && pontos[1] < PONTOS_MAX && !verificarCompletude(matriz, a, l));
    informarJogo(matriz, a, l, player, pontos);
    informarPlayer(player);
    processarFim(matriz, a, l, pontos, player);
}

void criarDiagonalPrin(int i, int j, char *matriz, int a, int l, char player) {
    matriz[i * l + j] = player;
    if (i + 1 < a && j + 1 < l) {
        criarDiagonalPrin(i + 1, j + 1, matriz, a, l, player);
    }
}

void criarDiagonalSec(int i, int j, char *matriz, int a, int l, char player) {
    matriz[i * l + j] = player;
    if (i + 1 < a && j - 1 >= 0) {
        criarDiagonalSec(i + 1, j - 1, matriz, a, l, player);
    }
}

void testeGameLoop(char *matriz, int a, int l) {
    zerarMatriz(matriz, a, l);
    rodarJogo(matriz, a, l, 'x');
}

void testeCriarSequencia(char *matriz, int a, int l) {
    int i, j, player;
    zerarMatriz(matriz, a, l);
    printf("Jogo Antes: \n");
    imprimirMatriz(matriz, a, l);
    i = 1;
    j = l - 1;
    player = 'x';
    //criarDiagonalPrin(i, j, matriz, a, l, player);
    criarDiagonalSec(i, j, matriz, a, l, player);
    printf("Jogo Depois: \n");
    imprimirMatriz(matriz, a, l);
}

void testeDetectarSequencia(char *matriz, int a, int l) {
    int i, j, player;
    zerarMatriz(matriz, a, l);
    i = 1;
    j = l - 1;
    player = 'x';
    //criarDiagonalPrin(i, j, matriz, a, l, player);
    criarDiagonalPrin(0, 0, matriz, a, l, trocarPlayer(player));
    criarDiagonalPrin(0, 1, matriz, a, l, player);
    printf("Jogo: \n");
    imprimirMatriz(matriz, a, l);
    //printf("\nDiagonal secundaria preenchida: %d\n", verificarCompletudeDiagSec(0, l - 2, matriz, a, l, player));
    printf("\nDiagonal principal preenchida: %d\n", verificarCompletudeDiagPrin(0, 0, matriz, a, l, player));
    printf("\nSoma de pontos de %c: %d", trocarPlayer(player), somarPontos(matriz, a, l, 1, trocarPlayer(player)));
}

int main()
{
    char m[9];
    
    testeGameLoop(m, 3, 3);

    //testeCriarSequencia(m, 5, 5);

    //testeDetectarSequencia(m, 5, 5);
    
    int a = 5;
    int l = 5;
    
    /*
    zerarMatriz(m, a, l);
    imprimirMatriz(m, a, l);
    int c = 0;
    do {
        int i, j;
        for (j = 0; j < l - 1; j++) {
            criarDiagonalSec(0, j, m, a, l, 'x');
            system("clear");
            imprimirMatriz(m, a, l);
            getchar();
        }
        criarDiagonalSec(0, l - 1, m, a, l, 'x');
            system("clear");
            imprimirMatriz(m, a, l);
            getchar();
        for (i = 1; i < a; i++) {
            criarDiagonalSec(i, l - 1, m, a, l, 'x');
            system("clear");
            imprimirMatriz(m, a, l);
            getchar();
        }
    
        for (j = 0; j < l - 1; j++) {
            criarDiagonalSec(0, j, m, a, l, 'o');
            system("clear");
            imprimirMatriz(m, a, l);
            getchar();
        }
        criarDiagonalSec(0, l - 1, m, a, l, 'o');
            system("clear");
            imprimirMatriz(m, a, l);
            getchar();
        for (i = 1; i < a; i++) {
            criarDiagonalSec(i, l - 1, m, a, l, 'o');
            system("clear");
            imprimirMatriz(m, a, l);
            getchar();
        }
    } while (1);
    */
    
    return 0;
}
