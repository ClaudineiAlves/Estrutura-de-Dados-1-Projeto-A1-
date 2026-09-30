#include <stdio.h>
#define LABS 20
#define DAYS 30

int main()
{
    int num_labs, qtd_dias, i, j;
    int cap_labs[LABS]; // Capacidade dos laboratorios
    int lab_day[LABS][DAYS]; // Matriz de cada laboratorio por dia
    float m_desemp[LABS]; // Media de desempenho

    // Numero de laboratorios:
    printf("Insira o numero de laboratorios (1 a %d): ", LABS);
    scanf("%d", &num_labs);
    while(num_labs < 1 || num_labs > LABS){
        printf("Valor invalido! Tente novamente: ");
        scanf("%d", &num_labs);
    }

    // Capacidade de cada laboratorio:
    printf("\nInsira a capacidade de cada laboratorio:\n");
    for(i = 0; i < num_labs; i++){
        printf("Laboratorio %d: ", i + 1);
        scanf("%d", &cap_labs[i]);
        while(cap_labs[i] <= 0){
            printf("Capacidade invalida! Deve ser maior que 0: ");
            scanf("%d", &cap_labs[i]);
        }
    }

    // Quantidade de dias:
    printf("\nInsira a quantidade de dias que deseja acompanhar (1 a %d): ", DAYS);
    scanf("%d", &qtd_dias);
    while(qtd_dias < 1 || qtd_dias > DAYS){
        printf("Valor invalido! Tente novamente: ");
        scanf("%d", &qtd_dias);
    }

    // Ocupacao de cada lab em cada dia (Leitura da Matriz):
    printf("\nInsira o numero de ocupacao de cada laboratorio em cada dia:\n");
    for(i = 0; i < num_labs; i++){
        for(j = 0; j < qtd_dias; j++){
            printf("Lab %d, dia %d: ", i + 1, j + 1);
            scanf("%d", &lab_day[i][j]);
            while(lab_day[i][j] < 0 || lab_day[i][j] > cap_labs[i]){
                printf("Invalido! O numero inserido deve estar entre 0 e %d: ", cap_labs[i]);
                scanf("%d", &lab_day[i][j]);
            }
        }
    }

    // Media de desempenho de cada laboratorio:
    printf("\nInforme a media de desempenho de cada laboratorio (0 a 10):\n");
    for(i = 0; i < num_labs; i++){
        printf("Laboratorio %d: ", i + 1);
        scanf("%f", &m_desemp[i]);
        while(m_desemp[i] < 0 || m_desemp[i] > 10){
            printf("Nota invalida! Deve estar entre 0 e 10: ");
            scanf("%f", &m_desemp[i]);
        }
    }

    return 0;
}
