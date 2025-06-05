#include <stdio.h>
void imprime(int vet[], int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}
int merge(int vet[], int prim, int meio, int ult) {
    int comp = 0;
    int n1 = meio - prim + 1;
    int n2 = ult - meio;
    int l[n1];
    int r[n2];
    for(int i = 0; i < n1; i++) {
       l[i] = vet[prim + i];
    }
    for(int j = 0; j < n2; j++) {
        r[j] = vet[meio + j + 1];
    }
    int i = 0;
    int j = 0;
    int k = prim;
    while(i < n1 && j < n2) {
        comp++;
        if(l[i] <= r[j]) {
            vet[k] = l[i];
            i++;
        } else {
            vet[k] = r[j];
            j++;
        }
        k++;
    }  
    while(i < n1) {
        comp++;
        vet[k] =  l[i];
        i++;
        k++;
    }
    while(j < n2) {
        comp++;
        vet[k] = r[j];
        j++;
        k++;
    }
    return comp;
}

int merge_sort(int vet[], int prim, int ult) {
    int total = 0;
    if(prim < ult) {
        int meio = prim +(ult - prim)/2;
        total += merge_sort(vet, prim, meio);
        total += merge_sort(vet, meio+1, ult);
        total += merge(vet, prim, meio, ult);
    }
    return total;
}
int mediana_de_tres(int vet[], int prim, int ult, int *comp) {
    int meio = prim + (ult - prim)/2;
    int a = vet[prim], b = vet[meio], c = vet[ult];
    (*comp) += 3; 
    if(a > b) {
        if(b > c) return meio;
        else if(a > c) return ult;
        else return prim;
    } else {
        if(a > c) return prim;
        else if(b > c) return ult;
        else return meio;
    }
}
int partition(int vet[], int prim, int ult, int *comp) {
  int ind = mediana_de_tres(vet, prim, ult, comp);
  int i = prim - 1;
    int temp = vet[ult];
    vet[ult] = vet[ind];
    vet[ind] = temp;

    int pivo = vet[ult];
    for (int j = prim; j < ult; j++) {
        (*comp)++;
        if (vet[j] <= pivo) {
          i++;
          int t = vet[i];
          vet[i] = vet[j];
          vet[j] = t;
        }
      }
      int t = vet[i+1];
      vet[i+1] = vet[ult];
      vet[ult] = t;
    
      return i + 1;
}
void quick_sort(int vet[], int prim, int ult, int *count) {
    if(prim < ult) {
        int q = partition(vet, prim, ult, count);
        quick_sort(vet, prim, q - 1, count);
        quick_sort(vet, q+1, ult, count);
    }

}
void insertion_sort(int vet[], int n, int *count) {
    int chave = 0;
    int j = 0;
    for(int i = 1; i < n; i++) {
        chave = vet[i];
        j = i - 1;
        while(j >= 0) {
            (*count)++;
           if(vet[j] > chave) {
            vet[j + 1] = vet[j];
            j--;
            } else {
                break;
            }
        }
        if(j+1 != i) {
            vet[j + 1] = chave;
        }
    } 
    return;
}
void quick_sort_hibrido(int vet[], int prim, int ult, int *count) {
    while(prim < ult) {
        if(ult - prim + 1 < 5) {
            insertion_sort(vet, ult - prim + 1, count);
            break;
        } else {
            int q = partition(vet, prim, ult, count);
            if(q - prim < ult - q) {
                quick_sort_hibrido(vet, prim, q - 1, count);
                prim = q + 1;
            } else {
                quick_sort_hibrido(vet, q + 1, ult, count);
                ult = q - 1;
            }
            
        }
    }
}
int main() {
    int n = 0;
    int c1 = 0;
    int c2 = 0;
    int c3 = 0;
    scanf("%d", &n);
    int vet1[n];
    int vet2[n];
    int vet3[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &vet1[i]);
        vet2[i] = vet1[i];
        vet3[i] = vet1[i];
    }
    c1 = merge_sort(vet1, 0, n-1);
    imprime(vet1, n);
    printf("%d\n", c1);
    quick_sort(vet2, 0, n-1, &c2);
    imprime(vet2, n);
    printf("%d\n", c2);
    quick_sort_hibrido(vet3, 0, n-1, &c3);
    imprime(vet3, n);
    printf("%d\n", c3);
    return 0;
}