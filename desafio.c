#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para exibir o menu
void exibirMenu() {
    printf("\nEscolha uma opção:\n");
    printf("1. Ocupar armário\n");
    printf("2. Liberar armário\n");
    printf("3. Sair\n");
    printf("Opção: ");
}

// Função para exibir o estado atual dos armários
void exibirEstado(unsigned char armarios) {
    printf("\nEstado dos armários (1 = ocupado, 0 = disponível):\n");
    for (int i = 7; i >= 0; i--) {
        printf("%d ", (armarios >> i) & 1);
    }
    printf("\n");
}

// Função para ocupar um armário
void ocuparArmario(unsigned char *armarios) {
    // Encontrar um armário disponível (bit 0)
    for (int i = 0; i < 8; i++) {
        if (((*armarios >> i) & 1) == 0) { // Se o armário i está disponível
            *armarios |= (1 << i); // Marcar como ocupado
            printf("Armário %d ocupado.\n", i + 1);
            return;
        }
    }
    printf("Nenhum armário disponível.\n");
}

// Função para liberar um armário
void liberarArmario(unsigned char *armarios) {
    int armario;
    printf("Digite o número do armário para liberar (1 a 8): ");
    scanf("%d", &armario);

    if (armario < 1 || armario > 8) {
        printf("Número de armário inválido.\n");
        return;
    }

    armario--; // Ajuste para índice de 0 a 7
    if (((*armarios >> armario) & 1) == 1) { // Se o armário já está ocupado
        *armarios &= ~(1 << armario); // Liberar o armário (setar bit para 0)
        printf("Armário %d liberado.\n", armario + 1);
    } else {
        printf("Armário %d já está livre.\n", armario + 1);
    }
}

int main() {
    unsigned char armarios = 0x00; // Todos os armários começam desocupados (0x00 = 00000000)
    int opcao;

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    do {
        exibirEstado(armarios); // Exibe o estado atual dos armários
        exibirMenu(); // Exibe o menu
        scanf("%d", &opcao); // Recebe a opção do usuário

        switch (opcao) {
            case 1:
                ocuparArmario(&armarios); // Ocupar armário aleatoriamente
                break;
            case 2:
                liberarArmario(&armarios); // Liberar armário específico
                break;
            case 3:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}

