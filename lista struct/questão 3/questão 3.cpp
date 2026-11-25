#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Funcionario {
    int codigo;
    char nome[50];
    char cargo[40];
    float salarioBase;
    float horasExtras;
};

struct Funcionario func[8];
int cont = 0; 


int buscar(int cod) {
    int i;
    for (i = 0; i < cont; i++) {
        if (func[i].codigo == cod) {
            return i;
        }
    }
    return -1;
}

float calcularLiquido(int pos) {
    float valorHora, valorHoraExtra, bruto, desconto, liquido;

    valorHora = func[pos].salarioBase / 160;
    valorHoraExtra = valorHora * 1.5; 
    bruto = func[pos].salarioBase + (func[pos].horasExtras * valorHoraExtra);
    desconto = bruto * 0.10;
    liquido = bruto - desconto;

    return liquido;
}

void cadastrar() {
    int cod;

    if (cont == 8) {
        printf("\nLimite de funcionarios atingido! (maximo 8)\n");
        return;
    }

    printf("\n--- CADASTRAR FUNCIONARIO ---\n");
    printf("Codigo: ");
    scanf("%d", &cod);

    if (buscar(cod) != -1) {
        printf("\nJa existe um funcionario com esse codigo!\n");
        return;
    }

    func[cont].codigo = cod;

    printf("Nome: ");
    scanf(" %[^\n]", func[cont].nome);

    printf("Cargo: ");
    scanf(" %[^\n]", func[cont].cargo);

    printf("Salario base: R$ ");
    scanf("%f", &func[cont].salarioBase);

    printf("Horas extras do mes: ");
    scanf("%f", &func[cont].horasExtras);

    cont++;
    printf("\nFuncionario cadastrado!\n");
}

void listar() {
    int i;
    float valorHora, valorHoraExtra, bruto, desconto, liquido;

    if (cont == 0) {
        printf("\nNenhum funcionario cadastrado ainda.\n");
        return;
    }

    printf("\n--- FOLHA DE PAGAMENTO ---\n");
    for (i = 0; i < cont; i++) {
        valorHora = func[i].salarioBase / 160;
        valorHoraExtra = valorHora * 1.5;
        bruto = func[i].salarioBase + (func[i].horasExtras * valorHoraExtra);
        desconto = bruto * 0.10;
        liquido = bruto - desconto;

        printf("\nCodigo: %d\n", func[i].codigo);
        printf("Nome: %s\n", func[i].nome);
        printf("Cargo: %s\n", func[i].cargo);
        printf("Salario base: R$ %.2f\n", func[i].salarioBase);
        printf("Horas extras: %.1f\n", func[i].horasExtras);
        printf("Valor da hora: R$ %.2f\n", valorHora);
        printf("Valor da hora extra: R$ %.2f\n", valorHoraExtra);
        printf("Salario bruto: R$ %.2f\n", bruto);
        printf("Desconto (10%%): R$ %.2f\n", desconto);
        printf("Salario liquido: R$ %.2f\n", liquido);
    }
}

void relatorio() {
    int i, posMaior = 0;
    float liquido, maior = 0, custoTotal = 0;

    if (cont == 0) {
        printf("\nNenhum funcionario cadastrado ainda.\n");
        return;
    }

    for (i = 0; i < cont; i++) {
        liquido = calcularLiquido(i);
        custoTotal = custoTotal + liquido;

        if (liquido > maior) {
            maior = liquido;
            posMaior = i;
        }
    }

    printf("\n--- RELATORIO DA FOLHA ---\n");
    printf("Maior salario liquido:\n");
    printf("Codigo: %d\n", func[posMaior].codigo);
    printf("Nome: %s\n", func[posMaior].nome);
    printf("Cargo: %s\n", func[posMaior].cargo);
    printf("Valor: R$ %.2f\n", maior);
    printf("\nCusto total da folha: R$ %.2f\n", custoTotal);
}

int main() {
    int op;

    do {
        system("cls");
        printf("===== FOLHA DE PAGAMENTO =====\n");
        printf("1 - Cadastrar funcionario\n");
        printf("2 - Listar folha de pagamento\n");
        printf("3 - Relatorio (maior liquido e custo total)\n");
        printf("0 - Sair\n");
        printf("\nEscolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                cadastrar();
                break;
            case 2:
                listar();
                break;
            case 3:
                relatorio();
                break;
            case 0:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }

        printf("\nPressione ENTER para continuar...");
        getchar(); 
        getchar(); 

    } while (op != 0);

    return 0;
}


