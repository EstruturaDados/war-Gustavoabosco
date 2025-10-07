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

// Função para o nível Mestre
void nivel_mestre() {
    // Implementar o sistema de missões e modularização total
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
