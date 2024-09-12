#include <stdlib.h>
#include <stdio.h>

typedef struct No {
    int valor;
    struct No *esq, *dir;
    int altura;
} Folha;

Folha* novaFolha(int input);
int maior(int altura1, int altura2);
int getAltura(Folha *folha);
int fatorBalanceamento(Folha *folha);
void preOrder(Folha *raiz);
void inOrder(Folha *raiz);
Folha* inserir(Folha *raiz, int input);
Folha* girarEsquerda(Folha *raiz);
Folha* girarDireita(Folha *raiz);
Folha* giroDuploEsquerdo(Folha *raiz);
Folha* giroDuploDireito(Folha *raiz);
Folha* balancear(Folha *raiz);
Folha* remover(Folha *raiz, int input);