#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 128  // Tamanho do buffer para leitura

int main() {
    // Nome do arquivo de entrada
    const char *arquivo_entrada = "lab2_ex2.txt";

    // Ponteiro para o arquivo
    FILE *file;
    char buffer[BUFFER_SIZE];  // Buffer de 128 bytes
    int num_linhas = 0;  // Contador de linhas
    size_t bytes_lidos;

    // Abre o arquivo no modo de leitura
    file = fopen(arquivo_entrada, "r");
    if (file == NULL) {
        perror("Não foi possível abrir o arquivo");
        return EXIT_FAILURE;
    }

    // Lê o arquivo em partes de 128 bytes e conta as quebras de linha
    while ((bytes_lidos = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        // Itera sobre o buffer para contar '\n'
        for (size_t i = 0; i < bytes_lidos; i++) {
            if (buffer[i] == '\n') {
                num_linhas++;
            }
        }
    }

    // Verifica se ocorreu erro na leitura
    if (ferror(file)) {
        perror("Erro ao ler o arquivo");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Fecha o arquivo
    fclose(file);

    // Exibe o número total de linhas
    printf("Número total de linhas no arquivo: %d\n", num_linhas);

    return EXIT_SUCCESS;
}
