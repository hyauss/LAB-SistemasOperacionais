#include <stdio.h>
#include <unistd.h>  // Para fork() e sleep()
#include <sys/types.h> // Para pid_t
#include <sys/wait.h>  // Para wait()

int main() {
    // Cria um processo filho
    pid_t pid = fork();

    if (pid < 0) {
        // Erro ao criar o processo filho
        perror("Erro ao criar o processo filho");
        return 1;
    } else if (pid == 0) {
        // Este bloco é executado no processo filho
        printf("Este é o processo filho. PID do filho: %d\n", getpid());

        // Loop para imprimir a mensagem 5 vezes com intervalo de 1 segundo
        for (int i = 0; i < 5; i++) {
            printf("Mensagem do processo filho (%d): %d\n", getpid(), i+1);
            sleep(1); // Pausa de 1 segundo
        }
    } else {
        // Este bloco é executado no processo pai
        printf("Este é o processo pai. PID do pai: %d, PID do filho: %d\n", getpid(), pid);

        // Espera o processo filho terminar
        wait(NULL);
    }

    return 0;
}
