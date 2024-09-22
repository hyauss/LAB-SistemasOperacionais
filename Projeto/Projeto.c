//Vinicius Alves Marques,
//Rafael de Menezes Ros,
//Gabriel Barros Albertini

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define INITIAL_BALANCE 1000
#define NUM_THREADS 10
#define TRANSFER_AMOUNT 50

// Estrutura para armazenar informações da conta
typedef struct {
    int balance;
    pthread_mutex_t mutex;
} BankAccount;

// Função para depositar uma quantia na conta
void deposit(BankAccount *account, int amount) {
    pthread_mutex_lock(&account->mutex); // Bloqueia o mutex antes de modificar o saldo
    account->balance += amount;
    printf("Depositado: %d, Saldo Atual: %d\n", amount, account->balance);
    pthread_mutex_unlock(&account->mutex); // Desbloqueia o mutex após a modificação
}

// Função para sacar uma quantia da conta
void withdraw(BankAccount *account, int amount) {
    pthread_mutex_lock(&account->mutex); // Bloqueia o mutex antes de modificar o saldo
    if (account->balance >= amount) {
        account->balance -= amount;
        printf("Sacado: %d, Saldo Atual: %d\n", amount, account->balance);
    } else {
        printf("Saldo Insuficiente para saque: %d\n", amount);
    }
    pthread_mutex_unlock(&account->mutex); // Desbloqueia o mutex após a modificação
}

// Função executada pelas threads de depósito
void* transaction_dep(void* arg) {
    BankAccount *account = (BankAccount*)arg;
    for (int i = 0; i < 5; i++) {
        deposit(account, TRANSFER_AMOUNT);
        sleep(3); // Simula algum tempo de processamento
    }
    return NULL;
}

// Função executada pelas threads de saque
void* transaction_sac(void* arg) {
    BankAccount *account = (BankAccount*)arg;
    for (int i = 0; i < 5; i++) {
        withdraw(account, TRANSFER_AMOUNT);
        sleep(1); // Simula algum tempo de processamento
    }
    return NULL;
}

int main() {
    pthread_t threads_dep[NUM_THREADS];
    pthread_t threads_sac[NUM_THREADS];
    BankAccount account;
    account.balance = INITIAL_BALANCE;
    pthread_mutex_init(&account.mutex, NULL); // Inicializa o mutex

    // Cria as threads de depósito
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads_dep[i], NULL, transaction_dep, &account) != 0) {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }
    }

    // Cria as threads de saque
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads_sac[i], NULL, transaction_sac, &account) != 0) {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }
    }

    // Espera todas as threads de depósito terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads_dep[i], NULL) != 0) {
            perror("pthread_join failed");
            exit(EXIT_FAILURE);
        }
    }

    // Espera todas as threads de saque terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads_sac[i], NULL) != 0) {
            perror("pthread_join failed");
            exit(EXIT_FAILURE);
        }
    }

    // Destrói o mutex
    pthread_mutex_destroy(&account.mutex);

    // Imprime o saldo final
    printf("Saldo Final: %d\n", account.balance);

    return 0;
}




