#include <stdio.h>
#include <string.h>


struct Data {
    int dia;
    int mes;
    int ano;
};


struct Paciente {
    int codigo;
    char nome[50];
    int idade;
};


struct Consulta {
    struct Paciente paciente; 
    struct Data data;         
    char descricao[50];  
};

int main() {
    struct Paciente pacientes[15];
    struct Consulta consultas[30];
    int qtdPacientes = 0;
    int qtdConsultas = 0;
    int opcao, i, c;

    do {
        printf("\n===== CONTROLE DE CONSULTAS =====\n");
        printf("1 - Cadastrar paciente\n");
        printf("2 - Listar pacientes\n");
        printf("3 - Registrar consulta\n");
        printf("4 - Pesquisar consultas de um paciente (codigo)\n");
        printf("5 - Listar consultas de uma data\n");
        printf("6 - Numero de consultas por paciente\n");
        printf("7 - Paciente com mais atendimentos\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1: // cadastrar paciente
            if (qtdPacientes >= 15) {
                printf("Limite de pacientes atingido!\n");
            } else {
                int codigo, repetido = 0;

                printf("Codigo: ");
                scanf("%d", &codigo);

                // confere se o codigo ja existe
                for (i = 0; i < qtdPacientes; i++) {
                    if (pacientes[i].codigo == codigo) {
                        repetido = 1;
                    }
                }

                if (repetido == 1) {
                    printf("Ja existe paciente com esse codigo!\n");
                } else {
                    pacientes[qtdPacientes].codigo = codigo;
                    printf("Nome (sem espacos): ");
                    scanf("%s", pacientes[qtdPacientes].nome);
                    printf("Idade: ");
                    scanf("%d", &pacientes[qtdPacientes].idade);
                    qtdPacientes++;
                    printf("Paciente cadastrado!\n");
                }
            }
            break;

        case 2: 
        
    if (qtdPacientes == 0) {
        printf("Nenhum paciente cadastrado.\n");
    } else {
        for (i = 0; i < qtdPacientes; i++) {
            printf("Codigo: %d | Nome: %s | Idade: %d\n",
                   pacientes[i].codigo, pacientes[i].nome, pacientes[i].idade);
        }
    }
    break;

        case 3: // registrar consulta
            if (qtdPacientes == 0) {
                printf("Cadastre um paciente primeiro!\n");
            } else if (qtdConsultas >= 30) {
                printf("Limite de consultas atingido!\n");
            } else {
                int codigo, achou = -1;

                printf("Codigo do paciente: ");
                scanf("%d", &codigo);

                // procura o paciente pelo codigo
                for (i = 0; i < qtdPacientes; i++) {
                    if (pacientes[i].codigo == codigo) {
                        achou = i;
                    }
                }

                if (achou == -1) {
                    printf("Paciente nao encontrado!\n");
                } else {
                    consultas[qtdConsultas].paciente = pacientes[achou];

                    printf("Data da consulta (dia mes ano): ");
                    scanf("%d %d %d", &consultas[qtdConsultas].data.dia,
                          &consultas[qtdConsultas].data.mes,
                          &consultas[qtdConsultas].data.ano);

                    printf("Descricao do atendimento: ");
                    getchar(); // limpa o enter que sobrou no buffer
                    fgets(consultas[qtdConsultas].descricao, 100, stdin);
                    // tira o \n que o fgets deixa no final
                    consultas[qtdConsultas].descricao[strcspn(consultas[qtdConsultas].descricao, "\n")] = '\0';

                    qtdConsultas++;
                    printf("Consulta registrada!\n");
                }
            }
            break;

        case 4: // pesquisar consultas de um paciente
            {
                int codigo, encontrou = 0;

                printf("Codigo do paciente: ");
                scanf("%d", &codigo);

                for (i = 0; i < qtdConsultas; i++) {
                    if (consultas[i].paciente.codigo == codigo) {
                        printf("%02d/%02d/%d | %s | %s\n",
                               consultas[i].data.dia,
                               consultas[i].data.mes,
                               consultas[i].data.ano,
                               consultas[i].paciente.nome,
                               consultas[i].descricao);
                        encontrou = 1;
                    }
                }

                if (encontrou == 0) {
                    printf("Nenhuma consulta encontrada para esse codigo.\n");
                }
            }
            break;

        case 5: // listar consultas de uma data
            {
                struct Data d;
                int encontrou = 0;

                printf("Data (dia mes ano): ");
                scanf("%d %d %d", &d.dia, &d.mes, &d.ano);

                for (i = 0; i < qtdConsultas; i++) {
                    if (consultas[i].data.dia == d.dia &&
                        consultas[i].data.mes == d.mes &&
                        consultas[i].data.ano == d.ano) {
                        printf("Paciente: %s (cod %d) | %s\n",
                               consultas[i].paciente.nome,
                               consultas[i].paciente.codigo,
                               consultas[i].descricao);
                        encontrou = 1;
                    }
                }

                if (encontrou == 0) {
                    printf("Nenhuma consulta nessa data.\n");
                }
            }
            break;

        case 6: // numero de consultas por paciente
            if (qtdPacientes == 0) {
                printf("Nenhum paciente cadastrado.\n");
            } else {
                for (i = 0; i < qtdPacientes; i++) {
                    int cont = 0;
                    for (c = 0; c < qtdConsultas; c++) {
                        if (consultas[c].paciente.codigo == pacientes[i].codigo) {
                            cont++;
                        }
                    }
                    printf("%s (cod %d): %d consulta(s)\n",
                           pacientes[i].nome, pacientes[i].codigo, cont);
                }
            }
            break;

        case 7: // paciente com mais atendimentos
            if (qtdConsultas == 0) {
                printf("Nenhuma consulta registrada ainda.\n");
            } else {
                int maior = 0, maiorCont = 0;

                for (i = 0; i < qtdPacientes; i++) {
                    int cont = 0;
                    for (c = 0; c < qtdConsultas; c++) {
                        if (consultas[c].paciente.codigo == pacientes[i].codigo) {
                            cont++;
                        }
                    }
                    if (cont > maiorCont) {
                        maiorCont = cont;
                        maior = i;
                    }
                }

                printf("Paciente com mais atendimentos: %s (cod %d) com %d consulta(s)\n",
                       pacientes[maior].nome, pacientes[maior].codigo, maiorCont);
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
