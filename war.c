
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constantes para tamanho de strings e número de territórios
#define MAX_NOME 50
#define MAX_COR 20
#define NUM_TERRITORIOS 5

// Estrutura que representa um território no jogo
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// Enumeração para representar os tipos de missão
typedef enum {
    DESTRUIR_VERDE,
    CONQUISTAR_TRES
} Missao;

// Inicializa os territórios com nomes, cores e tropas aleatórias
void inicializarTerritorios(Territorio *territorios) {
    const char *nomes[] = {"Alfa", "Bravo", "Charlie", "Delta", "Echo"};
    const char *cores[] = {"Vermelho", "Verde", "Azul", "Amarelo", "Preto"};

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        strcpy(territorios[i].nome, nomes[i]);
        strcpy(territorios[i].cor, cores[i]);
        territorios[i].tropas = rand() % 5 + 3; // entre 3 e 7 tropas
    }
}

// Exibe o estado atual do mapa com todos os territórios
void exibirMapa(const Territorio *territorios) {
    printf("\n📍 Estado Atual do Mapa:\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do Exército: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
    }
}

// Simula uma batalha entre dois territórios escolhidos pelo jogador
void simularBatalha(Territorio *territorios) {
    int atacante, defensor;

    // Escolha dos territórios
    printf("\nEscolha o território atacante (1 a 5): ");
    scanf("%d", &atacante);
    printf("Escolha o território defensor (1 a 5): ");
    scanf("%d", &defensor);
    getchar(); // limpa o buffer

    atacante--; defensor--; // ajusta para índice de vetor

    // Validação das escolhas
    if (atacante == defensor || atacante < 0 || defensor < 0 || atacante >= NUM_TERRITORIOS || defensor >= NUM_TERRITORIOS) {
        printf("❌ Escolha inválida.\n");
        return;
    }

    if (territorios[atacante].tropas <= 0) {
        printf("⚠️ O território atacante não tem tropas suficientes.\n");
        return;
    }

    // Sorteio dos dados de ataque e defesa
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    // Exibição dos dados sorteados
    printf("\n🎲 Dados sorteados:\n");
    printf("  %s (Atacante): %d\n", territorios[atacante].nome, dadoAtacante);
    printf("  %s (Defensor): %d\n", territorios[defensor].nome, dadoDefensor);

    // Lógica da batalha
    if (dadoAtacante >= dadoDefensor) {
        territorios[defensor].tropas--;
        printf("✅ O atacante venceu! Tropas do defensor: %d\n", territorios[defensor].tropas);

        // Se o defensor perdeu todas as tropas, território é conquistado
        if (territorios[defensor].tropas <= 0) {
            printf("🏳️ O território %s foi conquistado por %s!\n", territorios[defensor].nome, territorios[atacante].cor);
            strcpy(territorios[defensor].cor, territorios[atacante].cor);
            territorios[defensor].tropas = 1;
            territorios[atacante].tropas--;
        }
    } else {
        printf("🛡️ O defensor resistiu ao ataque!\n");
    }
}

// Verifica se a missão foi cumprida
int verificarMissao(const Territorio *territorios, Missao missao, const char *corJogador) {
    if (missao == DESTRUIR_VERDE) {
        // Missão: eliminar todos os territórios verdes
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (strcmp(territorios[i].cor, "Verde") == 0) {
                return 0; // ainda existe território verde
            }
        }
        return 1; // missão cumprida
    } else if (missao == CONQUISTAR_TRES) {
        // Missão: conquistar 3 territórios
        int conquistados = 0;
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (strcmp(territorios[i].cor, corJogador) == 0) {
                conquistados++;
            }
        }
        return conquistados >= 3;
    }
    return 0;
}

// Exibe a missão atual do jogador
void mostrarMissao(Missao missao) {
    printf("\n🎯 Missão Atual:\n");
    if (missao == DESTRUIR_VERDE) {
        printf("→ Eliminar todos os territórios com exército Verde.\n");
    } else {
        printf("→ Conquistar pelo menos 3 territórios.\n");
    }
}

// Função principal do jogo
int main() {
    srand(time(NULL)); // inicializa gerador de números aleatórios

    // Alocação dinâmica dos territórios
    Territorio *territorios = calloc(NUM_TERRITORIOS, sizeof(Territorio));
    inicializarTerritorios(territorios);

    // Sorteia uma missão para o jogador
    Missao missao = rand() % 2;
    char corJogador[MAX_COR] = "Vermelho"; // cor do jogador

    int opcao;
    do {
        // Menu principal
        printf("\n🧠 Menu Principal:\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                exibirMapa(territorios);
                simularBatalha(territorios);
                break;
            case 2:
                mostrarMissao(missao);
                if (verificarMissao(territorios, missao, corJogador)) {
                    printf("🏆 Missão cumprida! Você venceu!\n");
                    opcao = 0; // encerra o jogo
                } else {
                    printf("⏳ Missão ainda não cumprida. Continue lutando!\n");
                }
                break;
            case 0:
                printf("👋 Saindo do jogo. Até a próxima!\n");
                break;
            default:
                printf("❌ Opção inválida.\n");
        }
    } while (opcao != 0);

    free(territorios); // libera memória alocada
    return 0;

