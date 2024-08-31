# Lista de Exercícios Práticos
## Manipulando Arquivos com Chamadas de Sistema

### Laboratório de Sistemas Operacionais

Nesta lista de exercícios, você utilizará algumas syscalls básicas em C para manipular arquivos. 


EXERCÍCIOS

## Exercício 1: Abrir e Ler um Arquivo

Escreva um programa em C que realize as seguintes operações:

1.	Abra um arquivo de texto chamado ‘lab2_ex1.txt’ em modo leitura.

2.	Verifique se o arquivo foi aberto com sucesso. Se não, exiba uma mensagem de erro e encerre o programa.

3.	Leia o conteúdo do arquivo para um buffer.

4.	Exiba o conteúdo lido na tela.

5.	Feche o arquivo após a leitura.

Requisitos:

•	O buffer deve ter um tamanho de 128 bytes.

•	Certifique-se de adicionar um caractere nulo (\0) ao final do buffer após a leitura.


Código fonte no arquivo Exe1.c,

![image](https://github.com/user-attachments/assets/bfb1ad40-b3bd-4b68-b142-810678202522)

## Exercício 2: Contar Linhas em um Arquivo

Escreva um programa em C que:

1.	Abra um arquivo de texto (lab2_ex2.txt) e leia seu conteúdo.

2.	Conte quantas linhas existem no arquivo.

3.	Exiba o número total de linhas na tela.

Requisitos:

•	Utilize um buffer de 128 bytes para ler o arquivo em partes.

•	A contagem de linhas deve ser feita identificando os caracteres de quebra de linha (\n).

•	O loop deve continuar até que todo o arquivo tenha sido processado.

Código fonte no arquivo Exe2.c,

![image](https://github.com/user-attachments/assets/05b97abc-f463-46d5-b6ac-0bee05086509)

## Exercício 3: Copiar o Conteúdo de um Arquivo para Outro

Escreva um programa em C que:

1.	Abra um arquivo de origem (lab2_ex3_origem.txt) em modo leitura (O_RDONLY).
2.	Abra ou crie um arquivo de destino (lab2_ex3_destino.txt) em modo escrita (o parametro do modo de abertura deve ser ‘O_WRONLY | O_CREAT | O_TRUNC’).

3.	Leia o conteúdo do arquivo de origem usando read() e escreva no arquivo de destino usando write().
4.	Feche ambos os arquivos após a operação.

Requisitos:

•	Use um buffer de 128 bytes para copiar o conteúdo.

•	Verifique se ambos os arquivos foram abertos com sucesso e trate possíveis erros.

•	Utilize um loop para ler o conteúdo do arquivo de origem e escrevê-lo no arquivo de destino até que todo o conteúdo tenha sido copiado.

![image](https://github.com/user-attachments/assets/99f9fef7-2f2e-4f5c-a0e5-292cf7bcabff)
