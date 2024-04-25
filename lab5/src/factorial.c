#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 100

int factorial = 1;
int mod;

pthread_mutex_t mutex;

void* calculate_factorial(void* arg) {
    int thread_id = (int)arg;
    int start = thread_id * 1000;
    int end = start + 1000;

    for (int i = start; i < end; i++) {
        factorial *= i;
        factorial %= mod;
    }

    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage: ./program k pnum mod\n");
        return 1;
    }

    int k = atoi(argv[1]);
    int pnum = atoi(argv[2]);
    mod = atoi(argv[3]);

    pthread_t threads[pnum];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < pnum; i++) {
        pthread_mutex_lock(&mutex);
        pthread_create(&threads[i], NULL, calculate_factorial, (void*)i);
    }

    for (int i = 0; i < pnum; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Factorial of %d mod %d: %d\n", k, mod, factorial);

    pthread_mutex_destroy(&mutex);

    return 0;
}