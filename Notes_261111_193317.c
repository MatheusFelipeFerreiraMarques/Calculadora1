#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define ARQUIVO "inventory.txt"

void lerLinha(char texto[], int tamanho) {
    if (fgets(texto, tamanho, stdin) != NULL) {
        texto[strcspn(texto, "\n")] = '\0';
    }
}

int lerInteiro(char mensagem[]) {
    char linha[100];
    char *fim;
    long numero;

    while (1) {
        printf("%s", mensagem);
        lerLinha(linha, sizeof(linha));

        errno = 0;
        numero = strtol(linha, &fim, 10);

        while (isspace((unsigned char)*fim)) {
            fim++;
        }

        if (fim != linha && *fim == '\0' && errno != ERANGE &&
            numero >= 0 && numero <= 2147483647) {
            return (int)numero;
        }

        printf("Entrada invalida! Digite um numero inteiro.\n");
    }
}

int lerOpcao() {
    char linha[100];
    char *fim;
    long opcao;

    while (1) {
        printf("\n==================================\n");
        printf("       Controle de Estoque\n");
        printf("==================================\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Estoque\n");
        printf("4. Sair\n");
        printf("Opcao: ");

        lerLinha(linha, sizeof(linha));

        errno = 0;
        opcao = strtol(linha, &fim, 10);

        while (isspace((unsigned char)*fim)) {
            fim++;
        }

        if (fim != linha && *fim == '\0' &&
            errno != ERANGE && opcao >= 1 && opcao <= 4) {
            return (int)opcao;
        }

        printf("Opcao invalida! Tente novamente.\n");
    }
}

void adicionarItem() {
    char nome[100];
    int quantidade;

    printf("\nDigite o nome do item: ");
    lerLinha(nome, sizeof(nome));

    quantidade = lerInteiro("Digite a quantidade: ");

    FILE *arquivo = fopen(ARQUIVO, "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(arquivo, "%s\n%d\n", nome, quantidade);

    fclose(arquivo);

    printf("Item adicionado com sucesso!\n");
}

void removerItem() {
    char nome[100];
    char nomeArquivo[100];
    char linha[100];
    int quantidade, disponivel;
    int encontrado = 0;

    printf("\nDigite o nome do item: ");
    lerLinha(nome, sizeof(nome));

    quantidade = lerInteiro("Digite a quantidade a ser removida: ");

    FILE *arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {
        printf("Item nao encontrado.\n");
        return;
    }

    FILE *temporario = fopen("temp.txt", "w");

    if (temporario == NULL) {
        fclose(arquivo);
        printf("Erro ao abrir arquivo temporario.\n");
        return;
    }

    while (fgets(nomeArquivo, sizeof(nomeArquivo), arquivo) != NULL) {
        nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';

        if (fgets(linha, sizeof(linha), arquivo) == NULL) {
            break;
        }

        disponivel = atoi(linha);

        if (strcmp(nomeArquivo, nome) == 0 && !encontrado) {
            encontrado = 1;

            if (quantidade > disponivel) {
                printf("Estoque insuficiente. Quantidade disponivel: %d\n",
                       disponivel);

                fprintf(temporario, "%s\n%d\n",
                        nomeArquivo, disponivel);
            } else if (disponivel - quantidade > 0) {
                fprintf(temporario, "%s\n%d\n",
                        nomeArquivo, disponivel - quantidade);

                printf("Quantidade atualizada com sucesso!\n");
            } else {
                printf("Item removido do estoque!\n");
            }
        } else {
            fprintf(temporario, "%s\n%d\n",
                    nomeArquivo, disponivel);
        }
    }

    fclose(arquivo);
    fclose(temporario);

    remove(ARQUIVO);
    rename("temp.txt", ARQUIVO);

    if (!encontrado) {
        printf("Item nao encontrado.\n");
    }
}

void listarEstoque() {
    char nome[100];
    char linha[100];
    int quantidade;
    int vazio = 1;

    FILE *arquivo = fopen(ARQUIVO, "r");

    printf("\n=============================\n");
    printf("        Estoque Atual\n");
    printf("=============================\n");

    if (arquivo == NULL) {
        printf("O estoque esta vazio.\n");
        return;
    }

    while (fgets(nome, sizeof(nome), arquivo) != NULL) {
        nome[strcspn(nome, "\n")] = '\0';

        if (fgets(linha, sizeof(linha), arquivo) == NULL) {
            break;
        }

        quantidade = atoi(linha);

        printf("Nome: %s\n", nome);
        printf("Quantidade: %d\n\n", quantidade);

        vazio = 0;
    }

    if (vazio) {
        printf("O estoque esta vazio.\n");
    }

    fclose(arquivo);
}

int main() {
    int opcao;
    char resposta[100];

    while (1) {
        opcao = lerOpcao();

        if (opcao == 4) {
            printf("\nObrigado por usar o Controle de Estoques! Ate a proxima.\n");
            break;
        }

        switch (opcao) {
            case 1:
                adicionarItem();
                break;

            case 2:
                removerItem();
                break;

            case 3:
                listarEstoque();
                break;
        }

        printf("\nDeseja realizar outra operacao? (s/n): ");
        lerLinha(resposta, sizeof(resposta));

        if (tolower((unsigned char)resposta[0]) != 's' ||
            resposta[1] != '\0') {
            printf("\nObrigado por usar o Controle de Estoques! Ate a proxima.\n");
            break;
        }
    }

    return 0;
}