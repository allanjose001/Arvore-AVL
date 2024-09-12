#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main() {
    int opcao, input;
    Folha *raiz = NULL;

    do {
        printf("0 - sair\n1 - inserir\n2 - remover\n3 - imprimir PreOrder\n4 - imprimir inOrder\n");
        scanf("%d" ,&opcao);

        switch(opcao) {
            case 0:
                break;
            case 1:
                printf("\ndigite o numero a ser inserido: ");
                scanf("%d", &input);
                raiz = inserir(raiz, input);
                break;
            case 2:
                printf("\ndigite o numero a ser removido: ");
                scanf("%d", &input);
                raiz = remover(raiz, input);
                break;
            case 3:
                printf("\nPre Order: \n");
                preOrder(raiz);
                printf("\n");
                break;
            case 4:
                printf("\nIn Order: \n");
                inOrder(raiz);
                printf("\n");
                break;
            default:
                printf("\nopcao invalida\n");
        }
    } while (opcao != 0);

    return 0;
}
