#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 50
#define MAX_COR 20
#define NUM_TERRITORIOS 5

// Estrutura que representa um território
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// Enum para representar os tipos de missão
typedef enum {
    DESTRUIR_VERDE,
    CONQUISTAR_TRES
} Missao;

// Inicializa os territórios com dados automáticos
void inicializarTerritorios(Territorio *territorios) {
    const char *nomes[] = {"Alfa", "Bravo", "Charlie", "Delta", "Echo"};
    const char *cores[] = {"Vermelho", "Verde", "Azul", "Amarelo", "Preto"};

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        strcpy(territorios[i].nome, nomes[i]);
        strcpy(territorios[i].cor, cores[i]);
        territorios[i].tropas = rand() % 5 + 3; // entre 3 e 7 tropas
    }
}

// Exibe o estado atual do mapa
void exibirMapa(const Territorio *territorios) {
    printf("\n📍 Estado Atual do Mapa:\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do Exército: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
    }
}

// Simula uma batalha entre dois territórios
void simularBatalha(Territorio *territorios) {
    int atacante, defensor;

    printf("\nEscolha o território atacante (1 a 5): ");
    scanf("%d", &atacante);
    printf("Escolha o território defensor (1 a 5): ");
    scanf("%d", &defensor);
    getchar();

    atacante--; defensor--;

    if (atacante == defensor || atacante < 0 || defensor < 0 || atacante >= NUM_TERRITORIOS || defensor >= NUM_TERRITORIOS) {
        printf("❌ Escolha inválida.\n");
        return;
    }

    if (territorios[atacante].tropas <= 0) {
        printf("⚠️ O território atacante não tem tropas suficientes.\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n🎲 Dados sorteados:\n");
    printf("  %s (Atacante): %d\n", territorios[atacante].nome, dadoAtacante);
    printf("  %s (Defensor): %d\n", territorios[defensor].nome, dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {
        territorios[defensor].tropas--;
        printf("✅ O atacante venceu! Tropas do defensor: %d\n", territorios[defensor].tropas);

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
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (strcmp(territorios[i].cor, "Verde") == 0) {
                return 0;
            }
        }
        return 1;
    } else if (missao == CONQUISTAR_TRES) {
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

// Exibe a missão atual
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
    srand(time(NULL));
    Territorio *territorios = (Territorio *)calloc(NUM_TERRITORIOS, sizeof(Territorio));
    inicializarTerritorios(territorios);

    Missao missao = (Missao)(rand() % 2);
    char corJogador[MAX_COR] = "Vermelho";

    int opcao;
    do {
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
                    opcao = 0;
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

    free(territorios);
    return 0;
}
