#include <stdio.h>
#include <pthread.h>

// Variável global compartilhada pelas threads
int contador = 0;

// Função executada pela primeira thread
void* thread1(void* arg) {
    for (int i = 0; i < 5; ++i) {
        contador++;
        printf("Thread 1: Contador = %d\n", contador);
    }
    return NULL;
}

// Função executada pela segunda thread
void* thread2(void* arg) {
    for (int i = 0; i < 5; ++i) {
        contador++;
        printf("Thread 2: Contador = %d\n", contador);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Criação das threads
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    // Espera que as threads terminem
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Valor final do contador: %d\n", contador);

    return 0;
}