#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define linhas 800
#define nos 800

struct no {
   int val;
   int alt;
   struct no* esq;
   struct no* dir;
};
typedef struct no Sno;
typedef struct no* Pno;

int max(int a, int b) {
    if(a >= b) {
        return a;
    } else {
        return b;
    }
}

int altura(Pno arv) {
    if (arv == NULL) {
        return -1;  
    }
    return arv->alt;
}

int altura_ex(Pno arv) {
    if (arv == NULL) { 
        return 0;
    }
    int alt_esq = altura_ex(arv->esq);
    int alt_dir = altura_ex(arv->dir);
    return 1 + max(alt_esq, alt_dir);
}

void busca_intervalo(Pno arv, int min_val, int max_val, int resultado[], int* count) {
    if(arv == NULL) {
        return;
    }
    int menor = (min_val < max_val) ? min_val : max_val;
    int maior = (min_val > max_val) ? min_val : max_val;
    
    if(menor < arv->val) {
        busca_intervalo(arv->esq, menor, maior, resultado, count);
    }
    if(arv->val >= menor && arv->val <= maior) {
        resultado[(*count)++] = arv->val;
    }
    if(maior > arv->val) {
        busca_intervalo(arv->dir, menor, maior, resultado, count);
    }
}

Pno cria(int val) {
    Pno novo = (Pno)malloc(sizeof(Sno));
    novo->val = val;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->alt = 0;
    return novo;
}

Pno busca(Pno arv, int chave) {
    if(arv == NULL || arv->val == chave) {
        return arv;
    }
    if(chave < arv->val) {
        return busca(arv->esq, chave);
    } else {
        return busca(arv->dir, chave);
    }
}

void atualiza_alt(Pno arv) {
    if (arv == NULL) return;
    arv->alt = max(altura(arv->esq), altura(arv->dir)) + 1;
}

int fb(Pno arv) {
    if(arv == NULL) {
        return 0;
    } else {
        return altura(arv->esq) - altura(arv->dir);
    }
}

Pno RR(Pno arv) {
    Pno x = arv->dir;
    arv->dir = x->esq;
    x->esq = arv;
    atualiza_alt(arv);
    atualiza_alt(x);
    return x;
}

Pno LL(Pno arv) {
    Pno x = arv->esq;
    arv->esq = x->dir;
    x->dir = arv;
    atualiza_alt(arv);
    atualiza_alt(x);
    return x;
}

Pno balancear(Pno arv) {
    if(arv == NULL) {
        return NULL;
    }
    if(fb(arv) == -2) {
        if(fb(arv->dir) == 1) {
            arv->dir = LL(arv->dir);
        }
        return RR(arv);
    } else if(fb(arv) == 2) {
        if(fb(arv->esq) == -1) {
            arv->esq = RR(arv->esq);
        }
        return LL(arv);
    }
    return arv;
}

Pno insere(Pno arv, int val) {
    if(arv == NULL) {
        Pno novo = cria(val);
        return novo;
    }

    if(val < arv->val) {
        arv->esq = insere(arv->esq, val);
    } else if(val > arv->val) {
        arv->dir = insere(arv->dir, val);
    } else {
        return arv; 
    }
    
    atualiza_alt(arv);  
    return balancear(arv);
}

Pno remover(Pno arv, int val) {
    if(arv == NULL) {
        return NULL;
    }
    if(val < arv->val) {
        arv->esq = remover(arv->esq, val);
    } else if(val > arv->val) {
        arv->dir = remover(arv->dir, val);
    } else {
        if(arv->esq == NULL && arv->dir == NULL) {
            free(arv);
            return NULL;
        } else if(arv->esq == NULL) {
            Pno aux = arv->dir;
            free(arv);
            return aux;
        } else if(arv->dir == NULL) {
            Pno aux = arv->esq;
            free(arv);
            return aux;
        } else {
            Pno aux;
            for (aux = arv->dir; aux->esq != NULL; aux = aux->esq);
            arv->val = aux->val;
            arv->dir = remover(arv->dir, aux->val);
        }
    }
    atualiza_alt(arv);
    return balancear(arv);
}

Pno libera_arvore(Pno arv) {
    if (arv != NULL) {
        libera_arvore(arv->esq);
        libera_arvore(arv->dir);
        free(arv);
    }
    return NULL;
}

int parseNumbers(char* line, int numbers[]) {
    int count = 0;
    char* token = strtok(line, " ");
    while (token != NULL && count < nos) {
        int num = atoi(token);
        if (num >= 0) {
            numbers[count++] = num;
        } else {
            break;
        }
        token = strtok(NULL, " ");
    }
    return count;
}

int main() {
    Pno arv = NULL;
    char input_lines[3][linhas];
    int numbers[nos];
    int count;

    // Lê as 3 linhas de entrada
    for (int i = 0; i < 3; i++) {
        if (fgets(input_lines[i], linhas, stdin) != NULL) {
            // Remove newline character
            input_lines[i][strcspn(input_lines[i], "\n")] = 0;
        }
    }

    // Primeira fase - inserção
    char line1_copy[linhas];
    strcpy(line1_copy, input_lines[0]);
    count = parseNumbers(line1_copy, numbers);
    
    for (int i = 0; i < count; i++) {
        arv = insere(arv, numbers[i]);
    }

    // Saída da primeira fase
    if(arv != NULL) {
        int alt_esq = altura_ex(arv->esq);
        int alt_dir = altura_ex(arv->dir);
        int alt_raiz = (arv->alt > 0) ? arv->alt : 0;
        printf("%d, %d, %d\n", alt_raiz, alt_esq, alt_dir);
    } else {
        printf("0, 0, 0\n");
    }

    // Segunda fase - inserção/remoção
    char line2_copy[linhas];
    strcpy(line2_copy, input_lines[1]);
    count = parseNumbers(line2_copy, numbers);
    
    for (int i = 0; i < count; i++) {
        Pno aux = busca(arv, numbers[i]);
        if(aux == NULL) {
            arv = insere(arv, numbers[i]);
        } else {
            arv = remover(arv, numbers[i]);
        }
    }
    if(arv == NULL) {
        printf("ARVORE VAZIA\n");
    } else {
        int alt_esq = altura_ex(arv->esq);
        int alt_dir = altura_ex(arv->dir);
        int alt_raiz = (arv->alt > 0) ? arv->alt : 0;
        printf("%d, %d, %d\n", alt_raiz, alt_esq, alt_dir);
    }
    int k1, k2;
    sscanf(input_lines[2], "%d %d", &k1, &k2);

    int resultado[nos];
    int resultado_count = 0;
    busca_intervalo(arv, k1, k2, resultado, &resultado_count);

    if (resultado_count == 0) {
        printf("NADA A EXIBIR\n");
    } else {
        for (int i = 0; i < resultado_count; i++) {
            printf("%d", resultado[i]);
            if (i < resultado_count - 1) printf(", ");
        }
        printf("\n");
        for (int i = 0; i < resultado_count; i++) {
            Pno encontrado = busca(arv, resultado[i]);
            if (encontrado) {
                int alt_esq = altura_ex(encontrado->esq);
                int alt_dir = altura_ex(encontrado->dir);
                int alt_no = (encontrado->alt > 0) ? encontrado->alt : 0;
                printf("%d, %d, %d\n", alt_no, alt_esq, alt_dir);
            }
        }
    }

    libera_arvore(arv);
    return 0;
}