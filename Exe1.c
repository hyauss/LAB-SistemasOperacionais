//Vinicius Alves Marques, TIA: 10417880

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    // Nome do arquivo de entrada
    const char *arquivo_entrada = "lab2_ex1.txt";
    
    // Descritores de arquivos
    int fd_in;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    // Abrindo o arquivo de entrada no modo de leitura
    fd_in = open(arquivo_entrada, O_RDONLY);
    if (fd_in == -1) {
        perror("Não foi possível abrir o arquivo de entrada");
        return EXIT_FAILURE;
    }

    // Lendo do arquivo de entrada e escrevendo na tela
    while ((bytes_read = read(fd_in, buffer, sizeof(buffer))) > 0) {
        // Escrevendo no prompt (saída padrão)
        bytes_written = write(STDOUT_FILENO, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Erro ao escrever no prompt");
            close(fd_in);
            return EXIT_FAILURE;
        }
    }

    // Verifica se ocorreu erro na leitura
    if (bytes_read == -1) {
        perror("Erro ao ler o arquivo de entrada");
    }
    
    return EXIT_SUCCESS;
}
