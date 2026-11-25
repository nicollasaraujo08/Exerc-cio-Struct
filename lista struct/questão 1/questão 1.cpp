#include <stdio.h>
#include <string.h>
struct Aluno {
    int matricula;
    char nome[50];
    float nota1;
    float nota2;
    float media;
};

float calcula_media(float n1, float n2) {
    return (n1 + n2) / 2;
}

int main() {
    struct Aluno alunos[10];
     int i, maior = 0, menor = 0, acima = 0;
    float soma = 0, media_geral;
    // cadastro
    for (i = 0; i < 10; i++) {
        printf("\nAluno %d\n", i + 1);
        printf("Matricula: ");
        scanf("%d", &alunos[i].matricula);
        printf("Nome: ");
        scanf(" %49[^\n]", alunos[i].nome);
        printf("Nota 1: ");
        scanf("%f", &alunos[i].nota1);
        printf("Nota 2: ");
        scanf("%f", &alunos[i].nota2);

        alunos[i].media = calcula_media(alunos[i].nota1, alunos[i].nota2);
    }


    for (i = 0; i < 10; i++) {
    printf("Nome: %s\n", alunos[i].nome);
   printf("Media: %.1f\n", alunos[i].media);
    if (alunos[i].media >= 6) {
            printf("Aprovado\n");
        } else {
            printf("Reprovado\n");
        }

        soma = soma + alunos[i].media;

        if (alunos[i].media > alunos[maior].media) {
            maior = i;
        }
        if (alunos[i].media < alunos[menor].media) {
            menor = i;
        }
    }

    media_geral = soma/ 10;

    for (i = 0; i < 10; i++) {
        if (alunos[i].media > media_geral) {
            acima++;
        }
    }

    printf("\nMaior media: %s (%.1f)\n", alunos[maior].nome, alunos[maior].media);
    printf("Menor media: %s (%.1f)\n", alunos[menor].nome, alunos[menor].media);
    printf("Media geral da turma: %.2f\n", media_geral);
    printf("Alunos acima da media geral: %d\n", acima);

    return 0;
}
