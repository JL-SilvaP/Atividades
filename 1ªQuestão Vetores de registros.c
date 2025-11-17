#include <stdio.h>
#include <string.h>

#define TOTAL_ESTADOS 26

typedef struct {
    char nome[50];
    int veiculos;
    int acidentes;
} Estado;

void coletarDados(Estado estados[]) {
    for (int i = 0; i < TOTAL_ESTADOS; i++) {
        printf("\n--- Estado %d ---\n", i + 1);
        printf("Nome do estado: ");
        scanf(" %[^\n]", estados[i].nome);

        printf("Numero de veiculos (2007): ");
        scanf("%d", &estados[i].veiculos);

        printf("Numero de acidentes (2007): ");
        scanf("%d", &estados[i].acidentes);
    }
}

void encontrarMaiorMenor(Estado estados[], int *indiceMaior, int *indiceMenor) {
    *indiceMaior = 0;
    *indiceMenor = 0;

    for (int i = 1; i < TOTAL_ESTADOS; i++) {
        if (estados[i].acidentes > estados[*indiceMaior].acidentes) {
            *indiceMaior = i;
        }
        if (estados[i].acidentes < estados[*indiceMenor].acidentes) {
            *indiceMenor = i;
        }
    }
}

float percentualAcidentes(Estado estados[], int i) {
    if (estados[i].veiculos == 0) return 0;
    return ((float)estados[i].acidentes / estados[i].veiculos) * 100.0;
}

float mediaAcidentes(Estado estados[]) {
    float soma = 0;
    for (int i = 0; i < TOTAL_ESTADOS; i++) {
        soma += estados[i].acidentes;
    }
    return soma / TOTAL_ESTADOS;
}

void estadosAcimaDaMedia(Estado estados[], float media) {
    printf("\nEstados acima da media de acidentes:\n");
    for (int i = 0; i < TOTAL_ESTADOS; i++) {
        if (estados[i].acidentes > media) {
            printf("%s (%d acidentes)\n", estados[i].nome, estados[i].acidentes);
        }
    }
}

int main() {
    Estado estados[TOTAL_ESTADOS];
    int indiceMaior, indiceMenor;
    float media;

    coletarDados(estados);
    encontrarMaiorMenor(estados, &indiceMaior, &indiceMenor);

    printf("\n--- Maior numero de acidentes ---\n");
    printf("Estado: %s\n", estados[indiceMaior].nome);
    printf("Acidentes: %d\n", estados[indiceMaior].acidentes);

    printf("\n--- Menor numero de acidentes ---\n");
    printf("Estado: %s\n", estados[indiceMenor].nome);
    printf("Acidentes: %d\n", estados[indiceMenor].acidentes);

    media = mediaAcidentes(estados);
    printf("\nMedia de acidentes no pais: %.2f\n", media);

    printf("\nPercentual de veiculos envolvidos em acidentes:\n");
    for (int i = 0; i < TOTAL_ESTADOS; i++) {
        printf("%s: %.2f%%\n", estados[i].nome, percentualAcidentes(estados, i));
    }

    estadosAcimaDaMedia(estados, media);

    return 0;
}
