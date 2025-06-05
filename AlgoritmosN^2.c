#include <stdio.h>
#include <stdbool.h>
void selection_sort(int vet[], int n) {
    for(int i = 0; i < n - 1; i++) {
        int menor_j = i;
        for(int j = i + 1; j < n; j++) {
            if(vet[menor_j] > vet[j]) {
                menor_j = j;
            }
        }
        if(menor_j != i) {
            int temp = vet[i];
            vet[i] = vet[menor_j];
            vet[menor_j] = temp;
        }
    }
    return;
}

void bubble_sort(int vet[], int n) {
    for(int i = 0; i < n - 1; i++) {
        bool troca = false;
        for(int j = 0; j < n - i - 1; j++) {
            if(vet[j] > vet[j+1]) {
                troca = true;
                int temp = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = temp;
                
            }
        }
        if(troca == false) {
            break;
        }
    }
    return;
}

void insertion_sort(int vet[], int n) {
    int chave = 0;
    int j = 0;
    for(int i = 1; i < n; i++) {
        chave = vet[i];
        j = i - 1;
    }
    while(j >= 0 && vet[j] > chave) {
        vet[j + 1] = vet[j];
        j--;
    }
    vet[j + 1] = chave;
    return;
}

int main() {
    int vet[10] = {5, 2, 9, 1, 5, 6, 7, 8, 3, 4};
    int n = sizeof(vet) / sizeof(vet[0]);

    selection_sort(vet, n);
    for(int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");

    int vet2[10] = {5, 2, 9, 1, 5, 6, 7, 8, 3, 4};
    bubble_sort(vet2, n);
    for(int i = 0; i < n; i++) {
        printf("%d ", vet2[i]);
    }
    printf("\n");

    int vet3[10] = {5, 2, 9, 1, 5, 6, 7, 8, 3, 4};
    insertion_sort(vet3, n);
    for(int i = 0; i < n; i++) {
        printf("%d ", vet3[i]);
    }
    printf("\n");
    return 0;
}
