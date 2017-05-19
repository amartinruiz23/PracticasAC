#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
#endif


int main(int argc, char const *argv[]) {


  if (argc < 2){
      printf("ERROR. ./pmtv-paralelo <tamaño> \n");
      return -1;
  }


  int tamanio = atoi(argv[1]);
  int i, j;

  long int *vector, *vector_resultado, **matriz;
  double inicio, final, total;


  vector = (long int*) malloc(tamanio*sizeof(long int));
  vector_resultado = (long int*) malloc(tamanio*sizeof(long int));
  matriz = (long int**) malloc(tamanio*sizeof(long int*));

  if ( (vector == NULL) || (vector_resultado == NULL) || (matriz == NULL)){
    printf("Error en la reserva de memoria");
    return -1;
  }

  for ( i = 0; i < tamanio; i++){
    matriz[i] = (long int*) malloc(tamanio*sizeof(long int));
    if (matriz[i] == NULL){
      printf("Error en la reserva de memoria para matriz");
      return -1;
    }
  }


  for ( i = 0; i < tamanio; i++){
    vector[i] = 2;
    vector_resultado[i] = 0;
    for ( j = 0; j < tamanio; j++){
      if(i >= j)
      matriz[i][j] = 5;
      else
      matriz[i][j] = 0;
    }
  }


  if (tamanio < 5){ //imprime la matriz si no es muy grande (tamaño 10)
    for ( i = 0; i < tamanio; i++){
      for ( j = 0; j < tamanio; j++){
        printf("%ld ", matriz[i][j]);
      }
      printf("\n");
    }
  }

  inicio = omp_get_wtime();

  for ( i = 0; i < tamanio; i++){
    int acumulador = 0;
    #pragma omp parallel for reduction(+:acumulador) schedule(runtime)
    for ( j = 0; j <= i; j++){
      acumulador += matriz[i][j]*vector[j];
    }
    vector_resultado[i] += acumulador;
  }

  final = omp_get_wtime();

  total = final - inicio;

  int a;
  if (tamanio>15)
    a = tamanio-1;
  else
    a = 1;

  printf("resultado:\n" );
    for ( i = 0; i < tamanio; i+=a)
      printf("%ld ",vector_resultado[i]);
  printf("\n");
  printf("TIEMPO: %f\n", total);


  return 0;

}
