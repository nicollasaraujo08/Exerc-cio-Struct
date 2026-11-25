#include <stdio.h>
#include <stdlib.h>

#define MAX 15

struct Produto {
    int codigo;
    char nome[50];
    float preco;
    int qtd;
};

int buscarCodigo(struct Produto p[], int total, int cod) {
    for (int i = 0; i < total; i++) {
        if (p[i].codigo == cod) {
            return i;
        }
    }
    return -1;
}

void reporEstoque(struct Produto *p, int q) {
    p->qtd += q;
}

int venderProduto(struct Produto *p, int q) {
    if (q <= 0 || q > p->qtd) {
        return 0;
    }
    p->qtd -= q;
    return 1;
}

void calcularRelatorio(struct Produto p[], int total, float *totalGeral, int *idxMaior) {
    float maiorValor = -1.0;
    *totalGeral = 0.0;
    *idxMaior = -1;

    for (int i = 0; i < total; i++) {
        float valorItem = p[i].preco * p[i].qtd;
        *totalGeral += valorItem;

        if (valorItem > maiorValor) {
            maiorValor = valorItem;
            *idxMaior = i;
        }
    }
}

int main() {
    struct Produto prod[MAX];
    int cont = 0;
    int op;

    do {
        system("cls");
        printf("===== PAPELARIA =====\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Repor estoque\n");
        printf("4 - Registrar venda\n");
        printf("5 - Consultar produto\n");
        printf("6 - Relatorio do estoque\n");
        printf("0 - Sair\n");
        printf("\nEscolha: ");
        scanf("%d", &op);

        if (op == 1) {
            if (cont >= MAX) {
                printf("\nEstoque cheio! (maximo %d produtos)\n", MAX);
            } else {
                int cod;
                printf("\nCodigo: ");
                scanf("%d", &cod);

                if (buscarCodigo(prod, cont, cod) != -1) {
                    printf("\nJa existe um produto com esse codigo!\n");
                } else {
                    prod[cont].codigo = cod;

                    printf("Nome: ");
                    fflush(stdin);
                    scanf(" %49[^\n]", prod[cont].nome);

                    printf("Preco: ");
                    scanf("%f", &prod[cont].preco);

                    printf("Quantidade em estoque: ");
                    scanf("%d", &prod[cont].qtd);

                    cont++;
                    printf("\nProduto cadastrado!\n");
                }
            }
        } else if (op == 2) {
            if (cont == 0) {
                printf("\nNenhum produto cadastrado.\n");
            } else {
                for (int i = 0; i < cont; i++) {
                    printf("\nCodigo: %d | Nome: %s | Preco: R$ %.2f | Estoque: %d\n",
                           prod[i].codigo, prod[i].nome, prod[i].preco, prod[i].qtd);
                }
            }
        } else if (op == 3) {
            int cod, pos, q;
            printf("\nCodigo do produto: ");
            scanf("%d", &cod);
            pos = buscarCodigo(prod, cont, cod);

            if (pos == -1) {
                printf("\nProduto nao encontrado!\n");
            } else {
                printf("Quanto vai repor? ");
                scanf("%d", &q);
                if (q > 0) {
                    reporEstoque(&prod[pos], q);
                    printf("\nEstoque atualizado! Agora tem %d unidades.\n", prod[pos].qtd);
                } else {
                    printf("\nQuantidade invalida!\n");
                }
            }
        } else if (op == 4) {
            int cod, pos, q;
            printf("\nCodigo do produto: ");
            scanf("%d", &cod);
            pos = buscarCodigo(prod, cont, cod);

            if (pos == -1) {
                printf("\nProduto nao encontrado!\n");
            } else {
                printf("Quantidade vendida: ");
                scanf("%d", &q);
                if (venderProduto(&prod[pos], q)) {
                    printf("\nVenda registrada! Total: R$ %.2f\n", q * prod[pos].preco);
                    printf("Sobraram %d unidades.\n", prod[pos].qtd);
                } else {
                    printf("\nEstoque insuficiente ou quantidade invalida!\n");
                }
            }
        } else if (op == 5) {
            int cod, pos;
            printf("\nCodigo do produto: ");
            scanf("%d", &cod);
            pos = buscarCodigo(prod, cont, cod);

            if (pos == -1) {
                printf("\nProduto nao encontrado!\n");
            } else {
                printf("\nCodigo: %d | Nome: %s | Preco: R$ %.2f | Estoque: %d\n",
                       prod[pos].codigo, prod[pos].nome, prod[pos].preco, prod[pos].qtd);
            }
        } else if (op == 6) {
            if (cont == 0) {
                printf("\nNenhum produto cadastrado.\n");
            } else {
                float totalGeral;
                int idxMaior;
                calcularRelatorio(prod, cont, &totalGeral, &idxMaior);

                printf("\nValor total em estoque: R$ %.2f\n", totalGeral);
                if (idxMaior != -1) {
                    printf("Maior valor em estoque: %s (Cod: %d) - R$ %.2f\n",
                           prod[idxMaior].nome,
                           prod[idxMaior].codigo,
                           prod[idxMaior].preco * prod[idxMaior].qtd);
                }
            }
        } else if (op != 0) {
            printf("\nOpcao invalida!\n");
        }

        printf("\nPressione ENTER para continuar...");
        fflush(stdin);
        getchar();

    } while (op != 0);

    return 0;
}
