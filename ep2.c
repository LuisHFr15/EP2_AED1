//--------------------------------------------------------------
// NOME: Luís Henrique Fernandes Ramires
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


// no da arvore
typedef struct estr {

    int chave;
    struct estr *esq;
	struct estr *dir;
} NO;


// no de lista ligada (caso queira usar alguma estrutura auxiliar)
typedef struct estrL {

    int chave;
    struct estrL *prox;
} NOL;


NOL* ultimoElemento (NOL* lista) {

    if (!lista) return (NULL);

    NOL* ultimo;
    while (lista) {

        ultimo = lista;
        lista  = lista -> prox;
    }

    
    return (ultimo);
}


NOL* ordenaLista (NOL* lista) {

    for (NOL* i = lista; i -> prox != NULL; i = i -> prox) {


        NOL* menorNumero = i;


        for (NOL* j = i -> prox; j != NULL; j = j -> prox) {

            if (j -> chave < menorNumero -> chave) {
            
                menorNumero = j;
            }
        }

        int auxiliar         = i -> chave;
        i -> chave           = menorNumero -> chave;
        menorNumero -> chave = auxiliar;
    }

    return (lista);
}


NO* criarNo (NOL* lista, int posicao) {

    if (!lista) return (NULL);

    for (int i = 0; i < posicao; i++) {

        lista = lista -> prox;
    }

    NO* novo = (NO*) malloc(sizeof(NO));
    novo -> chave = lista -> chave;

    return(novo);
}


int tamanhoDaLista (NOL* lista) {

    int contador = -1; // -1 = vazio, 0 = primeira posição

    while (lista) {
        
        contador++;
        lista = lista -> prox;
    }

    return (contador);
}



NOL* passarParaLista (NO* raiz, NOL** lista) {

    if (!raiz) return (NULL);
    NOL* novo     = (NOL*) malloc(sizeof(NOL));
    novo -> chave = raiz -> chave;
    novo -> prox  = *lista;

    *lista = novo;

    NOL* esquerda = passarParaLista(raiz -> esq, lista); // percorre o lado esquerdo da arvore
    NOL* direita  = passarParaLista(raiz -> dir, lista); // percorre o lado direito da arvore

    return (*lista);
}


// inicio = primeiro elemento (sempre 0), fim = tamanho da lista
NO* transformarEmArvore (NOL* lista, NO* raiz, int inicio, int fim) {

    if (!lista) return (NULL);
    int meio = (inicio + fim)/2;
    bool existe;

    if (inicio == fim) {

        NO* folha    = NULL;
        folha        = criarNo(lista, meio);
        folha -> esq = NULL;
        folha -> dir = NULL;

        return (folha);
    }

    raiz   = NULL;
    raiz   = criarNo(lista, meio);

    NO* filhoEsquerdo = NULL;
    filhoEsquerdo     = transformarEmArvore(lista, raiz, inicio, meio-1);
    raiz -> esq       = filhoEsquerdo;

    
    NO* filhoDireito  = NULL;
    filhoDireito      = transformarEmArvore(lista, raiz, meio+1, fim);
    raiz -> dir       = filhoDireito;

    return (raiz);
}


// caso o compilador exija declarar a funcao aqui
NO* copiaCompleta(NO* raiz);

NO* copiaCompleta(NO* raiz) {

    NOL* listaDaArvore = NULL;
    listaDaArvore = passarParaLista(raiz, &listaDaArvore);

    int tamanhoLista = tamanhoDaLista(listaDaArvore);

    listaDaArvore = ordenaLista(listaDaArvore);

    NO* copiaDaArvore = transformarEmArvore(listaDaArvore, copiaDaArvore, 0, tamanhoLista);

    return (copiaDaArvore);
}


int main() {

    return (0);
}
