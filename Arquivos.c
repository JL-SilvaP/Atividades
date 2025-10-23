#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 256

void lerStr(char str[], int tam);
void inserirFinalArquivo(char nomeArq[]);
void listarArquivo(char nomeArq[]);
void lerPosicaoEspecifica(char nomeArq[]);
void buscarNumero(char nomeArq[]);
void substituirNumero(char nomeArq[]);
void excluirNumero(char nomeArq[]);

int main() {
    char nomeArq[TAM];
    int opcao;
    printf("Digite o nome do arquivo: ");
    lerStr(nomeArq, TAM);
    while (strlen(nomeArq) == 0) {
        printf("Nome vazio é inválido!\n");
        printf("Digite o nome do arquivo: ");
        lerStr(nomeArq, TAM);
    }
    do {
        printf("\n\nMENU\n");
        printf("1 - Gravar um número no final do arquivo\n");
        printf("2 - Listar o conteúdo do arquivo\n");
        printf("3 - Imprimir valor específico\n");
        printf("4 - Buscar número no arquivo\n");
        printf("5 - Substituir número no arquivo\n");
        printf("6 - Excluir número do arquivo\n");
        printf("Digite a sua opção (0 p/ finalizar): ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirFinalArquivo(nomeArq);
                break;
            case 2:
                printf("---------------- Listagem ----------------\n");
                listarArquivo(nomeArq);
                printf("------------------------------------------\n");
                break;
            case 3:
                lerPosicaoEspecifica(nomeArq);
                break;
            case 4:
                buscarNumero(nomeArq);
                break;
            case 5:
                substituirNumero(nomeArq);
                break;
            case 6:
                excluirNumero(nomeArq);
                break;
            default:
                if (opcao != 0)
                    printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

void lerStr(char str[], int tam) {
    fgets(str, tam, stdin);
    int tamDigitado = strlen(str);
    if (tamDigitado > 0 && str[tamDigitado - 1] == '\n')
        str[tamDigitado - 1] = '\0';
}

void inserirFinalArquivo(char nomeArq[]) {
    int status;
    double num;
    FILE *arq = fopen(nomeArq, "ab");
    if (arq == NULL) {
        printf("Não pode abrir o arquivo!\n");
        return;
    }
    printf("Digite um número real: ");
    scanf("%lf", &num);
    status = fwrite(&num, sizeof(double), 1, arq);
    if (status == 1)
        printf("Valor armazenado com sucesso!\n");
    else
        printf("Erro ao gravar o valor no arquivo!\n");
    fclose(arq);
}

void listarArquivo(char nomeArq[]) {
    int status;
    double num;
    FILE *arq = fopen(nomeArq, "rb");
    if (arq == NULL) {
        printf("Não pode abrir o arquivo!\n");
        return;
    }
    status = fread(&num, sizeof(double), 1, arq);
    while (!feof(arq)) {
        if (status == 1)
            printf("%.3f\n", num);
        status = fread(&num, sizeof(double), 1, arq);
    }
    fclose(arq);
}

void lerPosicaoEspecifica(char nomeArq[]) {
    int status, pos;
    double num;
    FILE *arq = fopen(nomeArq, "rb");
    if (arq == NULL) {
        printf("Não pode abrir o arquivo!\n");
        return;
    }

    printf("Você quer mover para que posição: ");
    scanf("%d", &pos);

    status = fseek(arq, (pos - 1) * sizeof(double), SEEK_SET);
    if (status != 0 || feof(arq)) {
        printf("Essa é uma posição inválida!");
        fclose(arq);
        return;
    }

    status = fread(&num, sizeof(double), 1, arq);
    if (status == 1)
        printf("%.3f\n", num);
    else
        printf("Erro na leitura do registro\n");

    fclose(arq);
}

void buscarNumero(char nomeArq[]) {
    double num, alvo;
    int pos = 1, encontrado = 0;
    FILE *arq = fopen(nomeArq, "rb");
    if (!arq) {
        printf("Não pode abrir o arquivo!\n");
        return;
    }

    printf("Digite o número que deseja buscar: ");
    scanf("%lf", &alvo);

    while (fread(&num, sizeof(double), 1, arq) == 1) {
        if (num == alvo) {
            printf("Número %.3f encontrado na posição %d\n", alvo, pos);
            encontrado = 1;
        }
        pos++;
    }

    if (!encontrado)
        printf("Número %.3f não encontrado no arquivo.\n", alvo);

    fclose(arq);
}

void substituirNumero(char nomeArq[]) {
    double num, antigo, novo;
    int alterado = 0;
    FILE *arq = fopen(nomeArq, "r+b");
    if (!arq) {
        printf("Não pode abrir o arquivo!\n");
        return;
    }

    printf("Digite o número que deseja substituir: ");
    scanf("%lf", &antigo);
    printf("Digite o novo número: ");
    scanf("%lf", &novo);

    while (fread(&num, sizeof(double), 1, arq) == 1) {
        if (num == antigo) {
            fseek(arq, -sizeof(double), SEEK_CUR);
            fwrite(&novo, sizeof(double), 1, arq);
            alterado = 1;
        }
    }

    if (alterado)
        printf("Número %.3f substituído por %.3f com sucesso!\n", antigo, novo);
    else
        printf("Número %.3f não encontrado no arquivo.\n", antigo);

    fclose(arq);
}

void excluirNumero(char nomeArq[]) {
    double num, alvo;
    int encontrado = 0;
    char tempArq[TAM];

    FILE *arq = fopen(nomeArq, "rb");
    if (!arq) {
        printf("Não pode abrir o arquivo!\n");
        return;
    }

    printf("Digite o número que deseja excluir: ");
    scanf("%lf", &alvo);

    strcpy(tempArq, "temp.bin");
    FILE *temp = fopen(tempArq, "wb");
    if (!temp) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(arq);
        return;
    }

    while (fread(&num, sizeof(double), 1, arq) == 1) {
        if (num != alvo)
            fwrite(&num, sizeof(double), 1, temp);
        else
            encontrado = 1;
    }

    fclose(arq);
    fclose(temp);

    if (encontrado) {
        remove(nomeArq);
        rename(tempArq, nomeArq);
        printf("Número %.3f excluído com sucesso!\n", alvo);
    } else {
        remove(tempArq);
        printf("Número %.3f não encontrado no arquivo.\n", alvo);
    }
}
