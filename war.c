// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_TERRITORIOS 5
#define MAX_NOME 50
#define MAX_COR 20

// Struct para representar um território
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// Função para cadastrar territórios
void cadastrar_territorios(Territorio* territorios) {
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Digite o nome do território %d: ", i + 1);
        fgets(territorios[i].nome, MAX_NOME, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = 0;

        printf("Digite a cor do exército do território %d: ", i + 1);
        fgets(territorios[i].cor, MAX_COR, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = 0;

        printf("Digite o número de tropas do território %d: ", i + 1);
        scanf("%d", &territorios[i].tropas);
        getchar(); // Consumir o caractere newline
    }
}

// Função para exibir o estado atual do mapa
void exibir_mapa(Territorio* territorios) {
    printf("Estado atual do mapa:\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Território %d: %s - Cor: %s - Tropas: %d\n", i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
}

// Função para simular uma batalha
void batalha(Territorio* territorios, int atacante, int defensor) {
    int dados_atacante = rand() % 6 + 1;
    int dados_defensor = rand() % 6 + 1;

    printf("Dados do atacante: %d\n", dados_atacante);
    printf("Dados do defensor: %d\n", dados_defensor);

    if (dados_atacante > dados_defensor) {
        territorios[defensor].tropas--;
        printf("Atacante venceu! Defensor perdeu 1 tropa.\n");
    } else {
        printf("Defensor defendeu! Nenhuma tropa perdida.\n");
    }
}

// Função para verificar se o defensor foi conquistado
int verificar_conquista(Territorio* territorios, int defensor) {
    if (territorios[defensor].tropas <= 0) {
        printf("Território %d foi conquistado!\n", defensor + 1);
        return 1;
    }
    return 0;
}

// Função para o nível Aventureiro
void nivel_aventureiro() {
    Territorio* territorios = (Territorio*) calloc(MAX_TERRITORIOS, sizeof(Territorio));

    cadastrar_territorios(territorios);
    exibir_mapa(territorios);

    srand(time(NULL)); // Inicializar o gerador de números aleatórios

    int atacante, defensor;
    printf("Digite o número do território atacante: ");
    scanf("%d", &atacante);
    getchar(); // Consumir o caractere newline
    atacante--; // Ajustar para índice 0

    printf("Digite o número do território defensor: ");
    scanf("%d", &defensor);
    getchar(); // Consumir o caractere newline
    defensor--; // Ajustar para índice 0

    batalha(territorios, atacante, defensor);
    exibir_mapa(territorios);

    verificar_conquista(territorios, defensor);

    free(territorios);
}

// Função para gerar uma missão aleatória
void gerar_missao(int* missao) {
    *missao = rand() % 2 + 1; // Gera uma missão aleatória (1 ou 2)
}

// Função para verificar se a missão foi cumprida
void verificar_missao(int missao, Territorio* territorios) {
    int conquistados = 0;
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        if (strcmp(territorios[i].cor, "Verde") != 0) {
            conquistados++;
        }
    }

    if (missao == 1 && conquistados >= 3) {
        printf("Missão cumprida! Você conquistou 3 territórios.\n");
    } else if (missao == 2 && strcmp(territorios[0].cor, "Azul") == 0) {
        printf("Missão cumprida! Você conquistou o território Azul.\n");
    } else {
        printf("Missão não cumprida.\n");
    }
}

// Função para o nível Mestre
void nivel_mestre() {
    Territorio* territorios = (Territorio*) calloc(MAX_TERRITORIOS, sizeof(Territorio));

    cadastrar_territorios(territorios);
    exibir_mapa(territorios);

    srand(time(NULL)); // Inicializar o gerador de números aleatórios

    int missao;
    gerar_missao(&missao);

    printf("Missão: ");
    if (missao == 1) {
        printf("Conquistar 3 territórios.\n");
    } else {
        printf("Conquistar o território Azul.\n");
    }

    int opcao;
    do {
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);
        getchar(); // Consumir o caractere newline

        switch (opcao) {
            case 1: {
                int atacante, defensor;
                printf("Digite o número do território atacante: ");
                scanf("%d", &atacante);
                getchar(); // Consumir o caractere newline
                atacante--; // Ajustar para índice 0

                printf("Digite o número do território defensor: ");
                scanf("%d", &defensor);
                getchar(); // Consumir o caractere newline
                defensor--; // Ajustar para índice 0

                batalha(territorios, atacante, defensor);
                exibir_mapa(territorios);

                verificar_conquista(territorios, defensor);
                break;
            }
            case 2:
                verificar_missao(missao, territorios);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    free(territorios);
}

int main() {
    int nivel;
    printf("Escolha o nível: 1 - Novato, 2 - Aventureiro, 3 - Mestre\n");
    scanf("%d", &nivel);
    getchar(); // Consumir o caractere newline

    switch (nivel) {
        case 1:
            // Implementar o nível Novato
            break;
        case 2:
            nivel_aventureiro();
            break;
        case 3:
            nivel_mestre();
            break;
        default:
            printf("Nível inválido!\n");
    }

    return 0;
}
