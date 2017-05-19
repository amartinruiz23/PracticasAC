#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
#endif

int main(int argc, char **argv)
{
  int i, n=200, chunk, a[n], suma=0;
  omp_sched_t tipo;
  int chunk2;

  if(argc < 3) {
    fprintf(stderr,"\nFalta iteraciones o chunk \n");
    exit(-1);
  }

  n = atoi(argv[1]);
  if (n>200)
    n=200;
  chunk = atoi(argv[2]);

  for (i=0; i<n; i++)
    a[i]=i;

    omp_get_schedule(&tipo, &chunk2);
    printf("ANTES DEL CAMBIO: dyn-var: %d, nthreads-var: %d, thread-limit-var: %d, run-sched-var: %d, chunk: %d\n", omp_get_dynamic(), omp_get_max_threads(), omp_get_thread_limit(), tipo, chunk2);
    printf("num_threads: %d, num_procs: %d, in_parallel: %d\n", omp_get_num_threads(), omp_get_num_procs(), omp_in_parallel());


    omp_set_dynamic(2);
    omp_set_num_threads(2);
    omp_set_schedule(2,1);

  #pragma omp parallel for firstprivate(suma)  \
  lastprivate(suma) schedule(dynamic,chunk)
  for (i=0; i<n; i++) {
    suma = suma + a[i];
    printf(" thread %d suma a[%d]=%d suma=%d \n",
	   omp_get_thread_num(),i,a[i],suma);

     #pragma omp critical
     {
     omp_get_schedule(&tipo, &chunk2);
     printf("DENTRO DE PARALLEL: dyn-var: %d, nthreads-var: %d, thread-limit-var: %d, run-sched-var: %d, chunk: %d\n", omp_get_dynamic(), omp_get_max_threads(), omp_get_thread_limit(), tipo, chunk2);
     printf("num_threads: %d, num_procs: %d, in_parallel: %d\n", omp_get_num_threads(), omp_get_num_procs(), omp_in_parallel());
    }
  }

  printf("Fuera de 'parallel for' suma=%d\n",suma);
  omp_get_schedule(&tipo, &chunk2);
  printf("DESPUÉS DEL CAMBIO: dyn-var: %d, nthreads-var: %d, thread-limit-var: %d, run-sched-var: %d, chunk: %d\n", omp_get_dynamic(), omp_get_max_threads(), omp_get_thread_limit(), tipo, chunk2);
  printf("num_threads: %d, num_procs: %d, in_parallel: %d\n", omp_get_num_threads(), omp_get_num_procs(), omp_in_parallel());

}
