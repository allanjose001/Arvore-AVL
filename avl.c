#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

//⚠️observação para o professor:⚠️
//- eu implementei a arvore com logica de altura, por esse motivo a impressão do pre-order
//é representada "invertida", onde os elementos mais distantes da arvore tem valor 0
//e a raiz tem o valor mais alto. isso até soa contra contra-intuitivo
//agora que escrevi desta forma, apesar disso o codigo está funcionando
//sem nenhum problema (que eu tenha encontrado).
//- em alguns momentos eu chamo um Nó de folha, mesmo quando ela não é necessariamente
//uma folha, isso é apenas uma forma pessoal de nomear os Nós
//- o codigo está cheio de printf que dizem qual movimento foi realizado

//recebe um numero como argumento e cria uma nova folha vazia
Folha* novaFolha(int input){
    Folha *novo = malloc(sizeof(Folha));

    if (novo) {
        novo->valor = input;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;
    } else {
        printf("erro no malloc\n");
    }
    return novo;
}

int maior(int altura1, int altura2) {
    if(altura1 > altura2) {
        return altura1;
    } else {
        return altura2;
    }
}

//nomiei de get por que se assemelha mt a logica de Java
int getAltura(Folha *folha) {
    if (folha == NULL) {
        return -1;
    } else {
        return folha->altura;
    }
}

int fatorBalanceamento(Folha *folha) {
    if (folha) {
        //fb = h(t2) - h(t1)
        return (getAltura(folha->dir) - getAltura(folha->esq));
    } else {
        return 0;
    }
}

//imprime a altura da folha junto com seu numero
void preOrder(Folha *raiz) {
    if (raiz != NULL) {
        printf("[%d, %d]", raiz->valor, raiz->altura);
        preOrder(raiz->esq);
        preOrder(raiz->dir);
    }
}

void inOrder(Folha *raiz) {
    if (raiz) {
        inOrder(raiz->esq);
        printf("%d ", raiz->valor);
        inOrder(raiz->dir);
    }
}

Folha* inserir(Folha *raiz, int input) {
    if (raiz == NULL) {
        //caso base
        return novaFolha(input);
    } else {
        //percorre a arvore recursivamente até chegar no NULL, onde será inserido
        if (input < raiz->valor) {
            raiz->esq = inserir(raiz-> esq, input);
        } else {
            raiz->dir = inserir(raiz->dir, input);
        }
    }
    //altura = 1 + max(h1, h2)
    raiz->altura = maior(getAltura(raiz->esq), getAltura(raiz->dir)) + 1;

    //a função balancear faz todas a parte de verificação para saber
    //se é rotação simples ou dupla
    raiz = balancear(raiz);

    return raiz;
}

//neste caso raiz se refere a raiz da subarvore e não a raiz da arvore inteira
Folha* girarEsquerda(Folha *raiz) {
    Folha *novaRaiz, *t2;
    //em uma rotação esquerda o filho direito da raiz será a nova raiz
    //t2 é o filho esquerdo dessa nova raiz, ele é o unico elemento generico que se move durante a rotação
                        
    novaRaiz = raiz->dir;
    t2 = novaRaiz->esq;

    //a antiga raiz será filho esquerdo da nova, e t2 será o novo filho
    //direito da antiga raiz
    novaRaiz->esq = raiz;
    raiz->dir = t2;

    //altura = 1 + max(h1, h2)
    raiz->altura = maior(getAltura(raiz->esq), getAltura(raiz->dir)) +1;
    novaRaiz->altura = maior(getAltura(novaRaiz->esq), getAltura(novaRaiz->dir)) + 1;

    return novaRaiz;
}

Folha* girarDireita(Folha *raiz) {
    Folha *novaRaiz, *t2;

    novaRaiz = raiz->esq;
    t2 = novaRaiz->dir;

    novaRaiz->dir = raiz;
    raiz->esq = t2;

    raiz->altura = maior(getAltura(raiz->esq), getAltura(raiz->dir)) + 1;
    novaRaiz->altura = maior(getAltura(novaRaiz->esq), getAltura(novaRaiz->dir)) + 1;

    return novaRaiz;
}

//rotaciona 2 vezes 
Folha* giroDuploEsquerdo(Folha *raiz) {
    //primeiro rotaciona o filho do pivo de rotação 
    raiz->dir = girarDireita(raiz->dir);
    //depois rotaciona para a esquerda usando o pivo de rotação
    return girarEsquerda(raiz);
}

Folha* giroDuploDireito(Folha *raiz) {
    raiz->esq = girarEsquerda(raiz->esq);
    return girarDireita(raiz);
}

//verifica se existe 2 elementos com alturas diferentes, formando o caracteristico
//"joelho" da rotação dupla
Folha* balancear(Folha *raiz) {
    int fb = fatorBalanceamento(raiz);
    //maior que 1 e maior que 0, quer dizer que só existem folhas para um lado
    if (fb > 1 && fatorBalanceamento(raiz->dir) >= 0) {
        printf("rotacao simples esquerda\n");
        raiz = girarEsquerda(raiz);

    } else if (fb < -1 && fatorBalanceamento(raiz->esq) <= 0) {
        printf("rotacao simples direita\n");
        raiz = girarDireita(raiz);

    //maior que 1, mas menor que 0, significa que existe uma "dobra" na arvore
    //se desenhar uma linha entre o elemento de valor maior que 1, o menor que 0
    //e seu filho, formará uma caracteristica imagem que se assemelha com um joelho
    } else if (fb > 1 && fatorBalanceamento(raiz->dir) < 0) {
        printf("rotacao dupla esquerda\n");
        raiz = giroDuploEsquerdo(raiz);
        
    } else if (fb < -1 && fatorBalanceamento(raiz->esq) > 0) {
        printf("rotacao dupla direita\n");
        raiz = giroDuploDireito(raiz);
    }

    return raiz;
}

Folha* remover(Folha *raiz, int input) {
    if (raiz == NULL) {
        printf("valor nao encontrado\n");
        return NULL;
    } else {
        //if responsavel por percorrer a arvore
        if (raiz->valor == input) {
            if (raiz->esq == NULL && raiz->dir == NULL) {
                //caso base, se não tiver filhos apenas remove sem se preocupar
                free(raiz);
                printf("folha removida\n");
                return NULL;
            } else {
                //se a folha possui 2 galhos, move o numero da folha atual até o fim do galho
                //que não coincidentemente tem o valor ideal para ficar onde o numero removido está.
                //este elemento tambem pode ser chamado de antecessor
                if (raiz->esq != NULL && raiz->dir != NULL) {
                    Folha *aux = raiz->esq;
                    //procura numero antecessor ao que quer ser removido
                    while (aux->dir != NULL) {
                        aux = aux->dir;
                    }
                    //troca o numero que quer ser removido com o numero antecessor
                    raiz->valor = aux->valor;
                    aux->valor = input;
                    //chamada recursiva para remover o numero que agora está em um caso de 
                    //1 ou nenhum filho
                    raiz->esq = remover(raiz->esq, input);
                    return raiz;

                } else {
                    //se a folha que quer ser removida tem 1 filho, faz o filho desta folha
                    //substituir o seu lugar
                    Folha *aux;
                    if (raiz->esq != NULL) {
                        raiz = raiz->esq;
                    } else {
                        raiz = raiz->dir;
                    }
                    free(raiz);
                    return aux;
                }
            }
        } else {
            //recursividade responsavel por percorrer a arvore
            if (input < raiz->valor) {
                raiz->esq = remover(raiz->esq, input);
            } else {
                raiz->dir = remover(raiz->dir, input);
            }
        }
        //h = 1 + max(h1, h2);
        raiz->altura = maior(getAltura(raiz->esq), getAltura(raiz->dir)) + 1;

        raiz = balancear(raiz);

        return raiz;
    }
}
