#include <stdio.h>
#include <string.h>

#define TAM 100

struct Categoria {
    int codigo;
    char nome[50];
};

struct Produto {
    int codigo;
    char titulo[100];
    char descricao[256];
    int categoria;
    int preco;
};

void cadastrarCategoria(struct Categoria v[], int *qtd) {
    if (*qtd >= TAM) {
        printf("Nao eh possivel cadastrar mais categorias.\n");
        return;
    }

    struct Categoria nova;
    int codigoRepetido;

    do {
        codigoRepetido = 0;
        printf("Digite o codigo da categoria: ");
        scanf("%d", &nova.codigo);

        for (int i = 0; i < *qtd; i++) {
            if (v[i].codigo == nova.codigo) {
                printf("Codigo ja existente! Digite outro.\n");
                codigoRepetido = 1;
                break;
            }
        }
    } while (codigoRepetido);

    printf("Digite o nome da categoria: ");
    getchar();
    fgets(nova.nome, 50, stdin);
    nova.nome[strcspn(nova.nome, "\n")] = '\0';

    v[*qtd] = nova;
    (*qtd)++;
}

void imprimirCategorias(struct Categoria v[], int qtd) {
    if (qtd == 0) {
        printf("Nenhuma categoria cadastrada.\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        printf("Codigo: %d | Nome: %s\n", v[i].codigo, v[i].nome);
    }
}

void imprimirProdutos(struct Produto vp[], int qtdProdutos,
                      struct Categoria vc[], int qtdCategorias) {

    if (qtdProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtdProdutos; i++) {
        char nomeCategoria[50] = "Categoria nao encontrada";

        for (int j = 0; j < qtdCategorias; j++) {
            if (vc[j].codigo == vp[i].categoria) {
                strcpy(nomeCategoria, vc[j].nome);
                break;
            }
        }

        double precoFormatado = vp[i].preco / 100.0;

        printf("Codigo: %d\n", vp[i].codigo);
        printf("Titulo: %s\n", vp[i].titulo);
        printf("Descricao: %s\n", vp[i].descricao);
        printf("Categoria: %s\n", nomeCategoria);
        printf("Preco: R$ %.2f\n\n", precoFormatado);
    }
}

void selectionSortPorDescricao(struct Produto v[], int qtd) {
    int i, j, minIndex;

    for (i = 0; i < qtd - 1; i++) {
        minIndex = i;

        for (j = i + 1; j < qtd; j++) {
            if (strcmp(v[j].descricao, v[minIndex].descricao) < 0) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            struct Produto temp = v[i];
            v[i] = v[minIndex];
            v[minIndex] = temp;
        }
    }
}

void buscaBinariaPorDescricao(struct Produto v[], int qtd, char *x) {
    int inicio = 0;
    int fim = qtd - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(x, v[meio].descricao);

        if (cmp == 0) {
            printf("Produto encontrado!\n");
            printf("Codigo: %d\n", v[meio].codigo);
            printf("Titulo: %s\n", v[meio].titulo);
            printf("Descricao: %s\n\n", v[meio].descricao);
            return;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    printf("Produto NAO encontrado!\n");
}

int main() {
    struct Categoria categorias[TAM];
    struct Produto produtos[TAM];

    int qtdCategorias = 0;
    int qtdProdutos = 0;

    int opcao;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar Categoria\n");
        printf("2 - Imprimir Categorias\n");
        printf("3 - Imprimir Produtos\n");
        printf("4 - Ordenar Produtos por Descricao\n");
        printf("5 - Buscar Produto por Descricao\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            cadastrarCategoria(categorias, &qtdCategorias);
        }

        else if (opcao == 2) {
            imprimirCategorias(categorias, qtdCategorias);
        }

        else if (opcao == 3) {
            imprimirProdutos(produtos, qtdProdutos, categorias, qtdCategorias);
        }

        else if (opcao == 4) {
            selectionSortPorDescricao(produtos, qtdProdutos);
            printf("Produtos ordenados.\n");
        }

        else if (opcao == 5) {
            char busca[256];
            getchar();
            printf("Digite a descricao do produto: ");
            fgets(busca, 256, stdin);
            busca[strcspn(busca, "\n")] = '\0';

            buscaBinariaPorDescricao(produtos, qtdProdutos, busca);
        }

    } while (opcao != 0);

    return 0;
}
