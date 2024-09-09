# Lista de Exercícios Práticos 
## Criação de Processos

### Laboratório de Sistemas Operacionais

### EXERCÍCIO 1. Escreva um programa em C que crie um processo filho utilizando fork().
•	No processo pai, imprima o PID do processo pai e do filho.

•	No processo filho, imprima uma mensagem informando que ele é o filho e o PID dele.

•	Adicione um código no processo filho para fazer com que ele execute um loop que imprime uma mensagem 5 vezes, com um intervalo de 1 segundo entre as mensagens.

![image](https://github.com/user-attachments/assets/58074426-c210-4f36-b54b-34101a91e666)

### EXERCÍCIO 2. Modifique o programa anterior para que o processo pai use wait() para aguardar que o processo filho termine antes de continuar sua execução.
•	Após o término do filho, o pai deve imprimir uma mensagem informando que o filho terminou.

![image](https://github.com/user-attachments/assets/6466bf6a-ef1a-4998-9d54-67437823fb4d)

### EXERCÍCIO 3. Modifique o processo filho para que, em vez de executar um loop, ele execute um novo programa (como ls, ou pwd) usando exec() ou suas outras variações.
•	O processo pai deve continuar aguardando o término do filho.

![image](https://github.com/user-attachments/assets/a261bd5c-7ecd-4df8-a22f-c9932cfc27e9)
