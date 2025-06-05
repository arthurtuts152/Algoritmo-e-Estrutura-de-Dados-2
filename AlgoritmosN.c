#include <stdio.h>
#include <string.h>
#include <ctype.h>
int encontra_index(char chave[], char c) {
     if(c == ' ') return 0;
     for(int i = 0; i < 26; i++) {
        if(chave[i] == c) return i+1;
     }
     return 0;
}
void counting_sort(char palavras[][21], int num_palavras, int pos, char chave[], int C[]) {
    for(int i = 0; i < 27; i++) {
        C[i] = 0;
    }
    for(int i = 0; i < num_palavras; i++) {
        char c = palavras[i][pos];
        int ind = encontra_index(chave, c);
        C[ind]++;
    }
    for(int i = 1; i < 27; i++) {
        C[i] += C[i-1];
    }
}
void radix_sort(char palavras[][21], int num_palavras, int max_tamanho, char chave[]) {
    char temp[num_palavras][21];
    int C[27];
    for(int pos = max_tamanho - 1; pos >= 0; pos--) {
        counting_sort(palavras, num_palavras, pos, chave, C);
        for (int i = 0; i < 27; i++) {
            printf("%d ", C[i]);
        }
        printf("\n");
        for(int i = num_palavras - 1; i >= 0; i--) {
            char c = palavras[i][pos];
            int ind = encontra_index(chave, c);
            strcpy(temp[--C[ind]], palavras[i]);
        }
        for(int i = 0; i < num_palavras; i++) {
            strcpy(palavras[i], temp[i]);
        }
    }
}
void preencher(char palavras[][21], int num_palavras, int max_tamanho) {
    for(int i = 0; i < num_palavras; i++) {
        int tam = strlen(palavras[i]);
        for(int j = tam; j < max_tamanho;j++) {
            palavras[i][j] = ' ';
        }
        palavras[i][max_tamanho] = '\0';
    }
}
void lower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
int main() {
    int n = 0;
    char chave[27];
    char palavras[20][21];
    scanf("%d", &n);
    scanf("%s", chave);
    for(int i = 0; i < n; i++) {
        scanf("%s", palavras[i]);
        lower(palavras[i]);
    }
    int maior_tam = 0;
    for(int i = 0; i < n; i++) {
        int temp = strlen(palavras[i]);
        if(temp > maior_tam) maior_tam = temp;
    }
    preencher(palavras, n, 20);
    for (int i = 0; i < n; i++) {
        printf("%s.\n", palavras[i]);
    }
    printf("%d\n", maior_tam);
    radix_sort(palavras, n, maior_tam, chave);
    for(int i = 0; i < n; i++) {
        printf("%s\n", palavras[i]);
    }
    return 0;
}



