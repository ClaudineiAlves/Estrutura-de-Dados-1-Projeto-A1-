#include <stdio.h>
#define LABS 30
#define DAYS 20

int main()
{
    int num_labs, cap_labs[LABS], qtd_dias, lab_day[DAYS][LABS];
    float m_desemp;
    int i, j;

    printf("Insira o numero de laboratorios: ");
    scanf("%d", &num_labs);

    printf("Insira a capacidade de cada laboratório:\n");
    for(i=1; i<=num_labs; i++){
        printf("Laboratorio %d: ", i);
        scanf("%d", &cap_labs[i]);
    }

    printf("Insira a quantidade de dias que deseja acompanhar: ");
    scanf("%d", &qtd_dias);

    printf("Informe a media de desempenho de cada laboratorio:\n");


    //leitura de matriz [quantidade de dias/ocupação]
    for (i=0,i<qtd_dias,i++)
    {

        for (j=0,j<num_labs,j++)


        {
            printf("Escreva o valor da ocupação de do lab 0%d do dia 0%d",i+1,j+1,)
            printf("\N\N\N\N\N\N\NDIA %d |",qtd_dias)
            printf("  LABORATORIO %d|  ")
        }
    }


}
