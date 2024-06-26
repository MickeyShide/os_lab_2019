#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* thread1_function(void* arg) {
    printf("Thread 1 is trying to lock mutex1\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 1 has locked mutex1\n");

    printf("Thread 1 is trying to lock mutex2\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 1 has locked mutex2\n");

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    pthread_exit(NULL);
}

void* thread2_function(void* arg) {
    printf("Thread 2 is trying to lock mutex2\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 2 has locked mutex2\n");

    printf("Thread 2 is trying to lock mutex1\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 2 has locked mutex1\n");

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread1_function, NULL);
    pthread_create(&thread2, NULL, thread2_function, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}