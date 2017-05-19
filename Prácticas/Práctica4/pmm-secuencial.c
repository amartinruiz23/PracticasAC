#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int **matriz_1, **matriz_2, **matriz_resultado;

int main(int argc, char const *argv[]) {


  if (argc < 2){
      printf("ERROR. Introducir tamaño para matriz.\n");
      return -1;
  }

  int tamanio = atoi(argv[1]);
  int i, j, k;

  double inicio, final, total;



  matriz_1 = (int**) malloc(tamanio*sizeof(int*));
  matriz_2 = (int**) malloc(tamanio*sizeof(int*));
  matriz_resultado = (int**) malloc(tamanio*sizeof(int*));



  if ( (matriz_1 == NULL) || (matriz_2 == NULL) || (matriz_resultado == NULL)){
    printf("Error en la reserva de memoria");
    return -1;
  }

  for ( i = 0; i < tamanio; i++){
    matriz_1[i] = (int*) malloc(tamanio*sizeof(int));
    if (matriz_1[i] == NULL){
      printf("Error en la reserva de memoria para matriz");
      return -1;
    }
  }

  for ( i = 0; i < tamanio; i++){
    matriz_2[i] = (int*) malloc(tamanio*sizeof(int));
    if (matriz_2[i] == NULL){
      printf("Error en la reserva de memoria para matriz");
      return -1;
    }
  }

  for ( i = 0; i < tamanio; i++){
    matriz_resultado[i] = (int*) malloc(tamanio*sizeof(int));
    if (matriz_resultado[i] == NULL){
      printf("Error en la reserva de memoria para matriz");
      return -1;
    }
  }

  #pragma omp parallel for private(j)
  for ( i = 0; i < tamanio; i++){
    for ( j = 0; j < tamanio; j++){
      matriz_1[i][j] = 1;
      matriz_2[i][j] = 2;
      matriz_resultado[i][j] = 0;
    }
  }

  inicio = omp_get_wtime();

  #pragma omp parallel for private(j,k)
  for ( i = 0; i < tamanio; i++){
    for ( j = 0; j < tamanio; j++){
      for ( k = 0; k < tamanio; k++){
        matriz_resultado[i][j] += matriz_1[i][k] * matriz_2[k][j];
      }
    }
  }

  final = omp_get_wtime();

  total = final - inicio;


    printf("resultado:\n" );
    printf("%d, %d\n", matriz_resultado[0][0], matriz_resultado[tamanio-1][tamanio-1]);
    printf("TIEMPO: %f\n", total);

  return 0;
}
