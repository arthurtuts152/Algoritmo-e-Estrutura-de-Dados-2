#include <stdio.h>
#include <time.h>
int BuscaLinear(long vet[], int key, int tam) {
  clock_t start = clock();
  for (int i = 0; i < tam; i++) {
    if (vet[i] == key) {
      double tempo = ((double)clock() - start) / CLOCKS_PER_SEC;
      printf("O tempo gasto na busca linear foi: %f", tempo);
      return i;
    }
  }
  double tempo = ((double)clock() - start) / CLOCKS_PER_SEC;
  printf("O tempo gasto na busca linear foi: %f", tempo);
  return 0;
}
int Busca_Binaria(long vet[], int key, int tam) {
  clock_t start = clock();
  int ini = 0;
  int fim = tam - 1;
  int meio = 0;
  do {
    meio = (ini + fim) / 2;
    if (key > vet[meio]) {
      ini = meio + 1;
    } else if (key < vet[meio]) {
      fim = meio - 1;
    }
  } while (ini <= fim && key != vet[meio]);
  if (key == vet[meio]) {
    double tempo = ((double)clock() - start) / CLOCKS_PER_SEC;
    printf("O tempo gasto na Busca Binária foi: %f", tempo);
    return meio;
  } else {
    double tempo = ((double)clock() - start) / CLOCKS_PER_SEC;
    printf("O tempo gasto na Busca Binária foi: %f", tempo);
    return -1;
  }
}
int Busca_Binaria_Rec(long vet[], int tam, int key, int ini, int fim) {
  if (ini <= fim) {
    int meio = (ini + fim) / 2;
    if (key == vet[meio]) {
      return meio;
    } else {
      if (key < vet[meio]) {
        return Busca_Binaria_Rec(vet, tam, key, ini, meio - 1);
      } else if (key > vet[meio]) {
        return Busca_Binaria_Rec(vet, tam, key, meio + 1, fim);
      }
    }
  }
  return -1;
}
float Busca_Binaria_Tempo(long vet[], int tam, int key) {
  clock_t start = clock();
  int resultado = Busca_Binaria_Rec(vet, tam, key, 0, tam - 1);
  double tempo = ((double)clock() - start) / CLOCKS_PER_SEC;
  printf("O tempo gasto na Busca Binária Recursiva foi: %f", tempo);
  return tempo;
}

int main() {
  int i;
  int chave = 0;
  int tamanho = 1000000;
  long vet[tamanho];
  long vet_inverso[tamanho];
  printf("Digite a chave a ser encontrada:\n");
  scanf("%d", &chave);
  for (i = 0; i < tamanho; i++) {
    vet[i] = i;
  }
  int x = Busca_Binaria_Tempo(vet, chave, tamanho);
  printf("%d", x);
  return 0;
  // Para chegar nos resultados para as outras funções basta trocar Busca_Binaria_Tempo por Busca_Binaria ou BuscaLinear
}
