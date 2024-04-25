#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

struct SumArgs {
  int *array;
  int begin;
  int end;
};

void GenerateArray(int *array, unsigned int array_size, unsigned int seed) {
  srand(seed);
  for (int i = 0; i < array_size; i++) {
    array[i] = rand();
  }
}


int Sum(const struct SumArgs *args) {
  int sum = 0;
    for (int i = args->begin; i < args->end; i++) {
      sum += args->array[i];
    }
  return sum;
}

void *ThreadSum(void *args) {
  struct SumArgs *sum_args = (struct SumArgs *)args;
  return (void *)(size_t)Sum(sum_args);
}

int main(int argc, char **argv) {
  // --threads_num <num> --seed <num> --array_size <num>

  uint32_t threads_num = atoi(argv[2]);
  uint32_t array_size = atoi(argv[6]);
  uint32_t seed = atoi(argv[4]);
  pthread_t threads[threads_num];

  /*
   * TODO:
   * your code here
   * Generate array here
   */

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);

  struct SumArgs args[threads_num];
  for (uint32_t i = 0; i < threads_num; i++) {
    args[i].array = array;
    args[i].begin = i * (array_size / threads_num);
    args[i].end = (i == threads_num - 1) ? array_size : (i + 1) * (array_size / threads_num);
        
    if (pthread_create(&threads[i], NULL, ThreadSum, (void *)&args[i])) {
      printf("Error: pthread_create failed!\n");
      return 1;
    }
  }

  int total_sum = 0;
  for (uint32_t i = 0; i < threads_num; i++) {
    int sum = 0;
    pthread_join(threads[i], (void **)&sum);
    total_sum += sum;
  }

  free(array);
  printf("Total: %d\n", total_sum);
  return 0;
}
