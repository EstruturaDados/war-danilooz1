// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

#define NUM_TERRITORIOS 5
#define CONTADOR_TERRITORIOS 0
#define MAX_STRING 100

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

struct Territorio {
    char nome[MAX_STRING];
    char corExercito[MAX_STRING];
    int numTropas;
};


// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void inicializarTerritorios(struct Territorio *lista, int *total) {

    limparBufferEntrada();
    

    // Verificação de Limite
    printf("Total atual de territorios: %d\n", *total);
    if (*total >= NUM_TERRITORIOS) {
        printf("ERRO: Limite maximo de territorios (%d) atingido.\n", NUM_TERRITORIOS);
        return;
    }

    int novo_indice = *total;

    printf("\n##### CADASTRO DE TERRITORIO %d #####\n", novo_indice + 1);

    
    printf("Informe o nome do territorio: ");
    fgets(lista[novo_indice].nome, MAX_STRING, stdin);

    printf("Informe o cor do exercito: ");
    fgets(lista[novo_indice].corExercito, MAX_STRING, stdin);

    printf("Informe a quantidade de tropas: ");
    scanf("%d", &lista[novo_indice].numTropas);

    lista[novo_indice].nome[strcspn(lista[novo_indice].nome, "\n")] = '\0';
    lista[novo_indice].corExercito[strcspn(lista[novo_indice].corExercito, "\n")] = '\0';
    
    // 4. ATUALIZAÇÃO DO CONTADOR (CHAVE!)
    (*total)++; // Incrementa o contador na função main (via ponteiro)

}

void exibirMenuPrincipal(int *itemMenu) {
    int itemMenuSelected;
    int totalItem = 2;

    printf("\n############################## MENU PRINCIPAL ##############################");
    printf("\n##### [1] CADASTRAR TERRITORIO         #####################################");
    printf("\n##### [2] VER TERRITORIOS CADASTRADOS  #####################################");
    printf("\n##### [0] SAIR                         #####################################");
    printf("\n");

    scanf("%d", &itemMenuSelected);

    if (itemMenuSelected < 0 || itemMenuSelected > totalItem) {
        printf("ERRO: Opcao invalida. Escolha entre 0 e %d.\n", totalItem);
        *itemMenu = -1; // Indica escolha inválida
        return;
    }

    *itemMenu = itemMenuSelected;

}

void imprimirTerritorios(struct Territorio *territorio) {
    printf("\n##### Detalhes do Territorio #####\n");
    printf("Nome: %s\n", territorio->nome);
    printf("Cor do Exercito: %s\n", territorio->corExercito);
    printf("Numero de Tropas: %d\n", territorio->numTropas);
}

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    struct Territorio listaTerritorios[NUM_TERRITORIOS];
    int itemMenu = -1;

    do {
        exibirMenuPrincipal(&itemMenu);
        
        // Verifica se a entrada foi válida antes do switch
        if (itemMenu == -1) {
            continue;
        }

        switch (itemMenu)
        {
            case 1:
                // Tenta cadastrar um único território (uma inserção)
                inicializarTerritorios(listaTerritorios, CONTADOR_TERRITORIOS);
                break;
            
            case 2:
                printf("\n\n##### LISTA DE TERRITORIOS CADASTRADOS (%d/%d) ##### \n", 
                       CONTADOR_TERRITORIOS, NUM_TERRITORIOS);
                
                if (CONTADOR_TERRITORIOS == 0) {
                    printf("Nenhum territorio cadastrado ainda.\n");
                } else {
                    // LOOP PARA IMPRIMIR TODOS OS TERRITÓRIOS
                    for (int i = 0; i < CONTADOR_TERRITORIOS; i++) {
                        imprimirTerritorios(&listaTerritorios[i]);
                    }
                }
                break;
            
            case 0:
                printf("\nEncerrando o jogo. Ate mais!\n");
                break;

            default:
                // Este default não deve ser alcançado se a validação do menu for boa
                printf("Opcao nao reconhecida. Tente novamente.\n");
                break;
        }

    } while (itemMenu != 0); // Continua até o usuário escolher SAIR


    // teste
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
