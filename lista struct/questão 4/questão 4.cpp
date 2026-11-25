#include <stdio.h>
#include <string.h>


struct Produto {
    int codigo;
    char nome[50];
    float preco;
    int estoque;
    float faturamento; 
};


struct Venda {
    struct Produto produto; 
    int indiceProduto;      
    int quantidade;
    float valorTotal;
};

int main() {
    struct Produto produtos[10];
    struct Venda vendas[20];
    int qtdProdutos = 0;
    int qtdVendas = 0;
    int opcao, i;

    do {
        printf("\n===== CONTROLE DE VENDAS =====\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Registrar venda\n");
        printf("4 - Listar vendas\n");
        printf("5 - Faturamento total e produto campeao\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1: 
            if (qtdProdutos >= 10) {
                printf("Limite de produtos atingido!\n");
            } else {
                printf("Codigo: ");
                scanf("%d", &produtos[qtdProdutos].codigo);
                printf("Nome (sem espacos): ");
                scanf("%s", produtos[qtdProdutos].nome);
                printf("Preco: ");
                scanf("%f", &produtos[qtdProdutos].preco);
                printf("Estoque: ");
                scanf("%d", &produtos[qtdProdutos].estoque);
                produtos[qtdProdutos].faturamento = 0;
                qtdProdutos++;
                printf("Produto cadastrado!\n");
            }
            break;

        case 2:
    if (qtdProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
    } else {
        for (i = 0; i < qtdProdutos; i++) {
            printf("Codigo: %d | Nome: %s | Preco: %.2f | Estoque: %d\n",
                   produtos[i].codigo, produtos[i].nome,
                   produtos[i].preco, produtos[i].estoque);
        }
    }
    break;

        case 3: 
            if (qtdProdutos == 0) {
                printf("Cadastre um produto primeiro!\n");
            } else if (qtdVendas >= 20) {
                printf("Limite de vendas atingido!\n");
            } else {
                int codigo, qtd, achou = -1;

                printf("Codigo do produto vendido: ");
                scanf("%d", &codigo);

                
                for (i = 0; i < qtdProdutos; i++) {
                    if (produtos[i].codigo == codigo) {
                        achou = i;
                    }
                }

                if (achou == -1) {
                    printf("Produto nao encontrado!\n");
                } else {
                    printf("Quantidade: ");
                    scanf("%d", &qtd);

                    if (qtd <= 0) {
                        printf("Quantidade invalida!\n");
                    } else if (qtd > produtos[achou].estoque) {
                        printf("Estoque insuficiente! Disponivel: %d\n",
                               produtos[achou].estoque);
                    } else {
                        
                        vendas[qtdVendas].produto = produtos[achou];
                        vendas[qtdVendas].indiceProduto = achou;
                        vendas[qtdVendas].quantidade = qtd;
                        vendas[qtdVendas].valorTotal = qtd * produtos[achou].preco;

                        
                        produtos[achou].estoque -= qtd;
                        produtos[achou].faturamento += vendas[qtdVendas].valorTotal;

                        printf("Venda registrada! Total: R$%.2f\n",
                               vendas[qtdVendas].valorTotal);
                        qtdVendas++;
                    }
                }
            }
            break;

        case 4: 
            if (qtdVendas == 0) {
                printf("Nenhuma venda registrada.\n");
            } else {
                for (i = 0; i < qtdVendas; i++) {
                    printf("Venda %d: %s | Qtd: %d | Total: R$%.2f\n",
                           i + 1, vendas[i].produto.nome,
                           vendas[i].quantidade, vendas[i].valorTotal);
                }
            }
            break;

            if (qtdVendas == 0) {
                printf("Nenhuma venda registrada ainda.\n");
            } else {
                float total = 0;
                int maior = 0;

                for (i = 0; i < qtdVendas; i++) {
                    total += vendas[i].valorTotal;
                }

                for (i = 1; i < qtdProdutos; i++) {
                    if (produtos[i].faturamento > produtos[maior].faturamento) {
                        maior = i;
                    }
                }
               printf("\n");
                printf("Faturamento total: %.2f\n", total);
                printf("Produto que mais faturou: %s\n", produtos[maior].nome);
                printf("Faturamento do produto: %.2f\n", produtos[maior].faturamento);
            
            }
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
