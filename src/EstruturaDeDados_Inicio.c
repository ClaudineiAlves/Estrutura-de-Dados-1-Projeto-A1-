#include <stdio.h>
#define LABS 30
#define DAYS 20

int main()
{
    int num_labs, cap_labs[LABS], qtd_dias, lab_day[LABS][DAYS];
    float m_desemp;

    printf("Insira o numero de laboratorios: ");
    scanf("%d", &num_labs);

    printf("Insira a capacidade de cada laboratório:\n");
    for(int i=1; i<=num_labs; i++){
        printf("Laboratorio %d: ", i);
        scanf("%d", &cap_labs[i]);
    }

    printf("Insira a quantidade de dias que deseja acompanhar: ");
    scanf("%d", &qtd_dias);

    printf("Informe a media de desempenho de cada laboratorio:\n");


}
