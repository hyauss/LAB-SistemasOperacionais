#include <stdio.h>
#include <unistd.h>  // Para fork(), exec()
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
        fflush(stdout); // Garante que a mensagem seja exibida imediatamente

        // Executa o comando "ls" no processo filho
        execl("/bin/ls", "ls", "-l", (char *)NULL);

        // Se execl() falhar, o código abaixo será executado
        perror("Erro ao executar o comando");
        return 1;
    } else {
        // Este bloco é executado no processo pai
        printf("Este é o processo pai. PID do pai: %d, PID do filho: %d\n", getpid(), pid);

        // Espera o processo filho terminar
        wait(NULL);

        // Mensagem informando que o filho terminou
        printf("O processo filho com PID %d terminou.\n", pid);
    }

    return 0;
}
