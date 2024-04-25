#include <stdio.h>
#include <pthread.h>

int k, pnum, mod;
pthread_mutex_t mutex;
unsigned long long result = 1;

void* factorial(void* arg) {
    int start = *((int*)arg);
    unsigned long long partial_result = 1;
    
    for (int i = start; i <= k; i += pnum) {
        partial_result = (partial_result * i) % mod;
    }
    
    pthread_mutex_lock(&mutex);
    result = (result * partial_result) % mod;
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

int main(int argc, char *argv[]) {
    // -k --pnum --mod

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--k") == 0) {
            k = atoi(argv[i+1]);
        } else if (strncmp(argv[i], "--pnum", 7) == 0) {
            pnum = atoi(argv[i] + 7);
        } else if (strncmp(argv[i], "--mod", 6) == 0) {
            mod = atoi(argv[i] + 6);
        }
    }

    pthread_t threads[pnum];
    int thread_args[pnum];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < pnum; i++) {
        thread_args[i] = i + 1;
        pthread_create(&threads[i], NULL, factorial, &thread_args[i]);
    }

    for (int i = 0; i < pnum; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Factorial of %d mod %d: %llu\n", k, mod, result);

    pthread_mutex_destroy(&mutex);

    return 0;
}