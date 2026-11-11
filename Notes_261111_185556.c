#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    int opcao;
    double n1, n2, resultado;
    char resposta;

    do {
        printf("\n===== CALCULADORA =====\n");
        printf("1 - Adicao\n");
        printf("2 - Subtracao\n");
        printf("3 - Multiplicacao\n");
        printf("4 - Divisao\n");
        printf("5 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Erro: Opcao invalida!\n");

            while (getchar() != '\n');
            continue;
        }

        if (opcao < 1 || opcao > 5) {
            printf("Erro: Escolha uma opcao entre 1 e 5.\n");
            continue;
        }

        if (opcao == 5) {
            printf("Obrigado por utilizar a calculadora! Ate mais!\n");
            break;
        }

        printf("Digite o primeiro numero: ");
        if (scanf("%lf", &n1) != 1) {
            printf("Erro: Numero invalido!\n");
            while (getchar() != '\n');
            continue;
        }

        printf("Digite o segundo numero: ");
        if (scanf("%lf", &n2) != 1) {
            printf("Erro: Numero invalido!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (opcao) {
            case 1:
                resultado = n1 + n2;
                printf("Resultado: %g + %g = %g\n", n1, n2, resultado);
                break;

            case 2:
                resultado = n1 - n2;
                printf("Resultado: %g - %g = %g\n", n1, n2, resultado);
                break;

            case 3:
                resultado = n1 * n2;
                printf("Resultado: %g * %g = %g\n", n1, n2, resultado);
                break;

            case 4:
                if (n2 == 0) {
                    printf("Erro: Divisao por zero nao e permitida.\n");
                } else {
                    resultado = n1 / n2;
                    printf("Resultado: %g / %g = %g\n", n1, n2, resultado);
                }
                break;
        }

        do {
            printf("\nDeseja realizar outra operacao? (s/n): ");
            scanf(" %c", &resposta);

            resposta = tolower(resposta);

            if (resposta != 's' && resposta != 'n') {
                printf("Resposta invalida! Digite s ou n.\n");
            }

        } while (resposta != 's' && resposta != 'n');

        if (resposta == 'n') {
            printf("Obrigado por utilizar a calculadora! Ate mais!\n");
            break;
        }

    } while (1);

    return 0;
}