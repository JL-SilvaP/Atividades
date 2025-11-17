#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int numero;
    char nome[50];
    char cpf[20];
    char telefone[20];
    float saldo;
} Conta;

int busca(Conta cadastro[], int tamanho, int numero) {
    if (tamanho == 0) return -1;
    for (int i = 0; i < tamanho; i++) {
        if (cadastro[i].numero == numero)
            return i;
    }
    return -2;
}

void cadastrarConta(Conta cadastro[], int *tamanho, int numero) {
    int pos = busca(cadastro, *tamanho, numero);

    if (pos >= 0) {
        printf("Numero de conta repetido. Cadastro nao realizado.\n");
        return;
    }

    cadastro[*tamanho].numero = numero;

    printf("Nome: ");
    scanf(" %[^\n]", cadastro[*tamanho].nome);

    printf("CPF: ");
    scanf(" %[^\n]", cadastro[*tamanho].cpf);

    printf("Telefone: ");
    scanf(" %[^\n]", cadastro[*tamanho].telefone);

    printf("Saldo inicial: ");
    scanf("%f", &cadastro[*tamanho].saldo);

    (*tamanho)++;
}

void consultarSaldo(Conta cadastro[], int tamanho, int numero) {
    int pos = busca(cadastro, tamanho, numero);

    if (pos >= 0) {
        printf("Saldo da conta %d: %.2f\n", numero, cadastro[pos].saldo);
    } else {
        printf("Conta nao cadastrada.\n");
    }
}

void depositar(Conta cadastro[], int tamanho, int numero) {
    int pos = busca(cadastro, tamanho, numero);

    if (pos >= 0) {
        float valor;
        printf("Valor do deposito: ");
        scanf("%f", &valor);
        cadastro[pos].saldo += valor;
    } else {
        printf("Conta nao cadastrada.\n");
    }
}

void sacar(Conta cadastro[], int tamanho, int numero) {
    int pos = busca(cadastro, tamanho, numero);

    if (pos < 0) {
        printf("Conta nao cadastrada.\n");
        return;
    }

    float valor;
    printf("Valor do saque: ");
    scanf("%f", &valor);

    if (valor <= cadastro[pos].saldo) {
        cadastro[pos].saldo -= valor;
    } else {
        printf("Saldo insuficiente.\n");
    }
}

void listarContas(Conta cadastro[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("\nConta: %d\n", cadastro[i].numero);
        printf("Titular: %s\n", cadastro[i].nome);
        printf("Telefone: %s\n", cadastro[i].telefone);
    }
}

int main() {
    Conta corrente[MAX], poupanca[MAX];
    int tamCorrente = 0, tamPoupanca = 0;
    int opcao, tipo, numero;

    do {
        printf("\n1 - Cadastrar conta");
        printf("\n2 - Consultar saldo");
        printf("\n3 - Deposito");
        printf("\n4 - Saque");
        printf("\n5 - Listar contas");
        printf("\n0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 0) break;

        printf("1 - Corrente\n2 - Poupanca\nTipo: ");
        scanf("%d", &tipo);

        Conta *cadastro;
        int *tamanho;

        if (tipo == 1) { cadastro = corrente; tamanho = &tamCorrente; }
        else { cadastro = poupanca; tamanho = &tamPoupanca; }

        switch (opcao) {
            case 1:
                printf("Numero da nova conta: ");
                scanf("%d", &numero);
                cadastrarConta(cadastro, tamanho, numero);
                break;
            case 2:
                printf("Numero da conta: ");
                scanf("%d", &numero);
                consultarSaldo(cadastro, *tamanho, numero);
                break;
            case 3:
                printf("Numero da conta: ");
                scanf("%d", &numero);
                depositar(cadastro, *tamanho, numero);
                break;
            case 4:
                printf("Numero da conta: ");
                scanf("%d", &numero);
                sacar(cadastro, *tamanho, numero);
                break;
            case 5:
                listarContas(cadastro, *tamanho);
                break;
        }

    } while (opcao != 0);

    return 0;
}

