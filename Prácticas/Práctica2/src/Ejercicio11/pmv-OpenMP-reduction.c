#include <stdlib.h>
#include <stdio.h>

#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
  #define omp_get_num_threads() 1
#endif

int main(int argc, char const *argv[]) {

  if (argc < 2){
    printf("ERROR: argumentos incorrectos. Modo de uso: ./pmv-secuencial <tamaño de matriz y vector>");
    return -1;
  }

    double tiempo_inicio, tiempo_final, tiempo_ejecucion;
    int tamanio = atoi(argv[1]);
    int i, j;

    double *vector, *vector_resultado, **matriz;

    vector = (double*) malloc(tamanio*sizeof(double));
    vector_resultado = (double*) malloc(tamanio*sizeof(double));
    matriz = (double**) malloc(tamanio*sizeof(double*));

    if ( (vector == NULL) || (vector_resultado == NULL) || (matriz == NULL)){
      printf("Error en la reserva de memoria");
      return -1;
    }

    for ( i = 0; i < tamanio; i++){
      matriz[i] = (double*) malloc(tamanio*sizeof(double));
      if (matriz[i] == NULL){
        printf("Error en la reserva de memoria para matriz");
        return -1;
      }
    }


    for ( i = 0; i < tamanio; i++){
      vector[i] = i;
      vector_resultado[i] = 0;
      #pragma omp parallel for
      for ( j = 0; j < tamanio; j++)
        matriz[i][j] = i+j;
    }

    tiempo_inicio = omp_get_wtime();



    for ( i = 0; i < tamanio; i++){

      double acumulador = 0;
      #pragma omp parallel for reduction(+:acumulador)
      for ( j = 0; j < tamanio; j++){
        acumulador += matriz[i][j]*vector[j];
      }

      vector_resultado[i] += acumulador;
    }


    tiempo_final = omp_get_wtime();



    tiempo_ejecucion = tiempo_final - tiempo_inicio;


    printf("Tamaño: %d . Tiempo: %f s.\n",tamanio, tiempo_ejecucion);

//    if (tamanio<15){
  //    for ( i = 0; i < tamanio; i++)
  //      printf("vector_resultado[%d]=%f", i, vector_resultado[i]);
  //  }

  free(vector_resultado);
  free(vector);
  for(i=0; i<tamanio;i++){
    free(matriz[i]);
  }
  free(matriz);

  return 0;
}
