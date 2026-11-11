#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

void lerLinha(char linha[], int tamanho) {
    if (fgets(linha, tamanho, stdin) != NULL) {
        if (strchr(linha, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

int lerOpcao() {
    char linha[100];
    char *fim;
    long valor;

    while (1) {
        printf("\n===== CALCULADORA =====\n");
        printf("1 - Adicao\n");
        printf("2 - Subtracao\n");
        printf("3 - Multiplicacao\n");
        printf("4 - Divisao\n");
        printf("5 - Sair\n");
        printf("Escolha uma opcao: ");

        lerLinha(linha, sizeof(linha));

        errno = 0;
        valor = strtol(linha, &fim, 10);

        while (isspace((unsigned char)*fim)) {
            fim++;
        }

        if (fim != linha && *fim == '\0' &&
            errno != ERANGE && valor >= 1 && valor <= 5) {
            return (int)valor;
        }

        printf("Opcao invalida! Tente novamente.\n");
    }
}

double lerNumero(char mensagem[]) {
    char linha[100];
    char *fim;
    double numero;

    while (1) {
        printf("%s", mensagem);
        lerLinha(linha, sizeof(linha));

        errno = 0;
        numero = strtod(linha, &fim);

        while (isspace((unsigned char)*fim)) {
            fim++;
        }

        if (fim != linha && *fim == '\0' && errno != ERANGE) {
            return numero;
        }

        printf("Entrada invalida! Digite um numero valido.\n");
    }
}

char lerResposta() {
    char linha[100];
    char resposta;

    while (1) {
        printf("\nDeseja realizar outra operacao? (s/n): ");
        lerLinha(linha, sizeof(linha));

        resposta = tolower((unsigned char)linha[0]);

        if ((resposta == 's' || resposta == 'n') &&
            linha[1] == '\0') {
            return resposta;
        }

        if ((resposta == 's' || resposta == 'n') &&
            isspace((unsigned char)linha[1])) {
            int i = 1;
            while (isspace((unsigned char)linha[i])) {
                i++;
            }
            if (linha[i] == '\0') {
                return resposta;
            }
        }

        printf("Resposta invalida! Digite s ou n.\n");
    }
}

int main() {
    int opcao;
    double numero1, numero2, resultado;
    char resposta;

    do {
        opcao = lerOpcao();

        if (opcao == 5) {
            printf("\nObrigado por utilizar a calculadora!\n");
            break;
        }

        numero1 = lerNumero("Digite o primeiro numero: ");
        numero2 = lerNumero("Digite o segundo numero: ");

        switch (opcao) {
            case 1:
                resultado = numero1 + numero2;
                printf("Resultado: %g + %g = %g\n",
                       numero1, numero2, resultado);
                break;

            case 2:
                resultado = numero1 - numero2;
                printf("Resultado: %g - %g = %g\n",
                       numero1, numero2, resultado);
                break;

            case 3:
                resultado = numero1 * numero2;
                printf("Resultado: %g * %g = %g\n",
                       numero1, numero2, resultado);
                break;

            case 4:
                if (numero2 == 0) {
                    printf("Erro: Divisao por zero nao e permitida.\n");
                } else {
                    resultado = numero1 / numero2;
                    printf("Resultado: %g / %g = %g\n",
                           numero1, numero2, resultado);
                }
                break;
        }

        resposta = lerResposta();

        if (resposta == 'n') {
            printf("\nObrigado por utilizar a calculadora!\n");
            break;
        }

    } while (1);

    return 0;
}