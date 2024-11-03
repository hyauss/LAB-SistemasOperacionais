#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_PAGINA 4
#define NUM_FRAMES 4
#define NUM_PAGES 8

// Estrutura para Frame (Memória Física)
typedef struct {
    int frame_id; // Identificador do frame
    int occupied; // 0 se livre, 1 se ocupado
} Frame;

// Estrutura para Página (Memória Virtual)
typedef struct {
    int page_id; // Identificador da página
} Page;

// Estrutura para Tabela de Páginas
typedef struct {
    int page_id; // ID da página virtual
    int frame_id; // ID do frame físico mapeado
    int valid;    // 1 se a página está mapeada, 0 caso contrário
} PageTableEntry;

typedef struct {
    PageTableEntry *entries; // Array de entradas da tabela de páginas
    int size;                // Número de páginas
} PageTable;

// Estrutura para Gerenciar a Memória Física
typedef struct {
    Frame *frames; // Array de frames
    int total_frames; // Total de frames disponíveis
} PhysicalMemory;

// Estrutura para Processo
typedef struct {
    int process_id; // Identificador do processo
    PageTable page_table; // Tabela de páginas do processo
    int *virtual_addresses; // Endereços virtuais que o processo irá acessar
    int num_addresses;      // Número de endereços virtuais
} Process;

// Funções

// Inicializar Memória Física
void init_physical_memory(PhysicalMemory *pm) {
    pm->total_frames = NUM_FRAMES;
    pm->frames = malloc(NUM_FRAMES * sizeof(Frame));
    for (int i = 0; i < NUM_FRAMES; i++) {
        pm->frames[i].frame_id = i;
        pm->frames[i].occupied = 0; // Inicialmente todos livres
    }
}

// Inicializar Memória Virtual
void init_virtual_memory(Page *pages) {
    for (int i = 0; i < NUM_PAGES; i++) {
        pages[i].page_id = i;
    }
}

// Inicializar Tabela de Páginas
void init_page_table(PageTable *pt) {
    pt->size = NUM_PAGES;
    pt->entries = malloc(NUM_PAGES * sizeof(PageTableEntry));
    for (int i = 0; i < NUM_PAGES; i++) {
        pt->entries[i].page_id = i;
        pt->entries[i].frame_id = -1; // Indica que não está mapeado
        pt->entries[i].valid = 0; // Não mapeado
    }
}

// Funções de Alocação de Frames
int allocate_frame(PhysicalMemory *pm) {
    for (int i = 0; i < pm->total_frames; i++) {
        if (!pm->frames[i].occupied) {
            pm->frames[i].occupied = 1; // Marca como ocupado
            return i; // Retorna o ID do frame alocado
        }
    }
    return -1; // Nenhum frame livre encontrado
}

// Função de Tradução de Endereço Virtual para Físico
int translate_address(Process *proc, int virtual_address) {
    int page_number = virtual_address / TAMANHO_PAGINA;
    int offset = virtual_address % TAMANHO_PAGINA;

    if (page_number >= proc->page_table.size || !proc->page_table.entries[page_number].valid) {
        // Falta de página (page fault)
        printf("Falta de página ao acessar endereço virtual %d\n", virtual_address);
        return -1; // Retorna -1 se houver falta de página
    }

    int frame_id = proc->page_table.entries[page_number].frame_id;
    return frame_id * TAMANHO_PAGINA + offset; // Retorna o endereço físico
}

// Programa de Teste
int main() {
    PhysicalMemory pm;
    init_physical_memory(&pm);

    Page *virtual_memory = malloc(NUM_PAGES * sizeof(Page));
    init_virtual_memory(virtual_memory);

    PageTable page_table;
    init_page_table(&page_table);

    // Simular alocação de frames para páginas
    for (int i = 0; i < NUM_PAGES; i++) {
        int frame_id = allocate_frame(&pm);
        if (frame_id != -1) {
            page_table.entries[i].frame_id = frame_id;
            page_table.entries[i].valid = 1; // Marca como mapeado
        } else {
            printf("Sem frames disponíveis para a página %d\n", i);
        }
    }

    // Criar um processo e definir endereços virtuais para acesso
    Process proc = { .process_id = 1, .page_table = page_table };
    int addresses_to_access[] = {0, 4, 8, 12, 16, 20, 24}; // Exemplos de endereços
    proc.virtual_addresses = addresses_to_access;
    proc.num_addresses = sizeof(addresses_to_access) / sizeof(addresses_to_access[0]);

    // Testar tradução de endereços virtuais
    for (int i = 0; i < proc.num_addresses; i++) {
        int physical_address = translate_address(&proc, proc.virtual_addresses[i]);
        if (physical_address != -1) {
            printf("Endereço virtual %d traduzido para endereço físico %d\n", proc.virtual_addresses[i], physical_address);
        }
    }

    // Liberar memória alocada
    free(pm.frames);
    free(page_table.entries);
    free(virtual_memory);

 return 0;
}