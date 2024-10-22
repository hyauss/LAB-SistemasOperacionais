//Vinicius Alves Marques

/*
	Programação em C - Lista encadeada (linked list)
	Funcionalidades:
		1) - Criar lista
		2) - Adicionar na lista
		3) - Listar os elementos da lista
		4) - Verificar se a lista está vazia
		5) - Buscar elemento na lista
		6) - Remover elemento da lista
		7) - Verificar o tamanho da lista
        Adicionando..
        8) Calcule a quantidade de memória gasta por cada instância da célula
        6') Incremente sua função liberando a memória quando um elemento é liberado
        9) Calcule o máximo de elementos possíveis na fila, considerando a memória disponível no computador
*/

#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/sysinfo.h>
#endif

// struct "exemplo" possui dois campos
typedef struct exemplo
{
	int v; // inteiro "v"
	struct exemplo *prox; // ponteiro para o próximo elemento
} t_exemplo;


// variáveis ponteiros globais que guardam referência
// para a cabeça da lista e para o nó corrente
// cabeca da lista encadeada (começa com NULL)
t_exemplo *cabeca = NULL;
t_exemplo *corrente = NULL;


// função para criar uma lista
// recebe um valor inteiro e retorna um ponteiro do tipo t_exemplo
t_exemplo * criar_lista(int valor)
{
	// aloca espaço em memória
	t_exemplo * p = (t_exemplo*)malloc(sizeof(t_exemplo));

	// verifica se houve falha na alocação de memória
	if(p == NULL)
	{
		printf("\nFalha ao alocar memoria\n");
		return NULL;
	}

	// se chegou aqui é porque foi feita a alocação com sucesso
	p->v = valor; // atribui o valor passado
	p->prox = NULL; // o próximo é NULL

	// faz a cabeca e o corrente apontar para p
	cabeca = corrente = p;
	// retorna o ponteiro alocado
	return p;
}


// função que adiciona um elemento à lista
// recebe a cabeca e o elemento a ser adicionado
// o elemento é inserido no FINAL da lista
t_exemplo* adicionar_lista(int v)
{
	// verifica se a cabeca é NULL (lista vazia), se for NULL,
	// então retorna o retorno da função criar_lista
	if(cabeca == NULL)
	{
		return criar_lista(v);
	}

	// se chegou aqui é porque a lista NÃO é vazia
	// aloca espaço em memória
	t_exemplo * p = (t_exemplo*)malloc(sizeof(t_exemplo));

	// verifica se houve falha na alocação de memória
	if(p == NULL)
	{
		printf("\nFalha ao alocar memoria\n");
		return NULL;
	}

	// atribui valores
	p->v = v;
	p->prox = NULL;

	// insere no FINAL da lista (obs.: também poderia ser no início)
	// aqui será feita a inserção no final,
	// a inserção no início fica como um desafio ;-)
	// para inserção no final, fazemos com que o próximo do nó
	// corrente aponte para o "p"
	corrente->prox = p;
	// o corrente passar a ser o "p"
	corrente = p;

	// retorna o ponteiro alocado
	return p;
}

// função para verificar se a lista está vazia
// retorna 1 se estiver vazia e 0 caso contrário
int lista_vazia()
{
	// se cabeca for NULL, então a lista está vazia
	if(cabeca == NULL)
		return 1;
	return 0;
}

// função que imprime a lista
void imprimir_lista()
{
    if(lista_vazia()){
		printf("[]");
        return;
    }

	t_exemplo *aux = cabeca;
    printf("[ ");
	while(aux != NULL)
	{
        printf("%d ",aux->v);
		aux = aux->prox;
	}
	printf("]\n\n");
}

t_exemplo * buscar_elemento(int x)
{
t_exemplo *pAnda;
pAnda = cabeca;
while(pAnda!=NULL && pAnda->v !=x)
    pAnda = pAnda->prox;
if(pAnda==NULL){
    printf("Elemento não consta na lista!");
}
return pAnda;
}

// função que remove um elemento da lista
// retorna 1 se conseguiu remover e 0 caso contrário

int remover_elemento(int v)
{
    t_exemplo *pAnda = cabeca;
    t_exemplo *pAnt = NULL;

    if (pAnda == NULL)
    {
        printf("A lista está vazia.\n");
        return 0;
    }

    // Procurando o elemento
    while (pAnda != NULL && pAnda->v != v)
    {
        pAnt = pAnda;
        pAnda = pAnda->prox;
    }

    // Verifica se o elemento foi encontrado
    if (pAnda == NULL)
    {
        printf("Elemento %d não encontrado.\n", v);
        return 0;
    }

    // Caso especial: o elemento a ser removido é o primeiro
    if (pAnt == NULL)
    {
        cabeca = pAnda->prox;
    }
    else
    {
        pAnt->prox = pAnda->prox;
    }

    free(pAnda);
    printf("O elemento %d foi removido e sua memória liberada!\n\n", v);
    return 1;
}

// função que retorna o tamanho da lista

int tamanho_lista()
{
	if(lista_vazia())
		return 0;

	t_exemplo *aux = cabeca;
	int tam = 0;

	while(aux != NULL)
	{
		tam++;
		aux = aux->prox;
	}
	return tam;
}

#ifdef _WIN32
// Função para obter memória disponível no Windows
size_t memoria_disponivel()
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return status.ullAvailPhys;
}
#else
// Função para obter memória disponível no Linux
size_t memoria_disponivel()
{
    struct sysinfo info;
    sysinfo(&info);
    return info.freeram * info.mem_unit;
}
#endif

// função principal

int main(int argc, char * argv[])
{

	// cria uma lista passando o valor
	printf("Criando uma lista...\n\n");
	criar_lista(10);

	// adiciona outros elementos à lista
	printf("Adicionando elementos na lista...\n\n");
	adicionar_lista(20);
	adicionar_lista(30);
	adicionar_lista(40);

	// chama a função para imprimir a lista
	printf("Imprimindo os elementos da lista:\n");
	imprimir_lista();

    // chama a função para calcular o gasto baseado no tamanho da lista
    int tam = tamanho_lista();
    int tamanho = sizeof(t_exemplo);
    printf("Tamanho do inteiro: %lu bytes\n", sizeof(int));
    printf("Tamanho do ponteiro: %lu bytes\n", sizeof(void*));
    printf("A quantidade de memória sendo gasta atualmente por cada célula é %d bytes.\n\n",tamanho);
    
    // chama a função para remover elementos da lista liberando a memória quando um elemento é liberado
	remover_elemento(30);
    imprimir_lista();

    // chama a função que calcula o maximo de elementos possiveis na lista, considerando a mem disponivel no computador
    // Obter memória disponível no sistema
    size_t memoria_disponivel_sistema = memoria_disponivel();
    // Converter bytes para GB
    double memoria_em_gb = memoria_disponivel_sistema / 1073741824.0;
    printf("Memória disponível no sistema: %lu bytes (%.2f GB)\n", memoria_disponivel_sistema,memoria_em_gb);

    // Calcular o número máximo de elementos possíveis
    size_t max_elementos = memoria_disponivel_sistema -16 / tamanho;
    printf("Número máximo de elementos que podem ser alocados na lista: %lu\n", max_elementos);
	
	return 0;
}