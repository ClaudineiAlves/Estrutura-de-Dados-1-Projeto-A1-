#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LABS 20
#define DAYS 30
#define BLOCO 15

// Descarta o que sobrou na linha depois do scanf.
void limpar_buffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
	if (c == EOF) {
		printf("\nFim da entrada. Encerrando...\n");
		exit(0);
	}
}

// Segura a tela ate apertar ENTER.
void pausar() {
	printf("\nPressione ENTER para continuar...");
	limpar_buffer();
}

// MENU DE CADASTRO -> 1. Cadastrar Dados Manualmente
void cadastro_manual(int *num_labs, int cap_labs[], int *qtd_dias, int lab_day[][DAYS], double m_desemp[]) {
	int i, j;

	// Numero de laboratorios
	printf("\nInsira o numero de laboratorios (1 a %d): ", LABS);

	*num_labs = 0;
	scanf("%d", num_labs);
	limpar_buffer();

	while (*num_labs < 1 || *num_labs > LABS) {
		printf("Valor invalido! Tente novamente: ");
		*num_labs = 0;
		scanf("%d", num_labs);
		limpar_buffer();
	}

	// Capacidade de cada laboratorio
	printf("\nInsira a capacidade de cada laboratorio:\n");
	for (i = 0; i < *num_labs; i++) {
		printf("Laboratorio %d: ", i + 1);
		cap_labs[i] = 0;
		scanf("%d", &cap_labs[i]);
		limpar_buffer();

		while (cap_labs[i] <= 0) {
			printf("Capacidade invalida! Deve ser maior que 0: ");
			cap_labs[i] = 0;
			scanf("%d", &cap_labs[i]);
			limpar_buffer();
		}
	}

	// Quantidade de dias
	printf("\nInsira a quantidade de dias que deseja acompanhar (1 a %d): ", DAYS);
	*qtd_dias = 0;
	scanf("%d", qtd_dias);
	limpar_buffer();

	while (*qtd_dias < 1 || *qtd_dias > DAYS) {
		printf("Valor invalido! Tente novamente: ");
		*qtd_dias = 0;
		scanf("%d", qtd_dias);
		limpar_buffer();
	}

	// Ocupacao de cada laboratorio em cada dia
	printf("\nInsira o numero de ocupacao de cada laboratorio em cada dia:\n");
	for (i = 0; i < *num_labs; i++) {
		for (j = 0; j < *qtd_dias; j++) {
			printf("Lab %d, dia %d: ", i + 1, j + 1);
			lab_day[i][j] = -1;
			scanf("%d", &lab_day[i][j]);
			limpar_buffer();

			while (lab_day[i][j] < 0 || lab_day[i][j] > cap_labs[i]) {
				printf("Invalido! O numero inserido deve estar entre 0 e %d: ", cap_labs[i]);
				lab_day[i][j] = -1;
				scanf("%d", &lab_day[i][j]);
				limpar_buffer();
			}
		}
	}

	// Media de desempenho de cada laboratorio
	printf("\nInforme a media de desempenho de cada laboratorio (0 a 10):\n");
	for (i = 0; i < *num_labs; i++) {
		printf("Laboratorio %d: ", i + 1);
		m_desemp[i] = -1;
		scanf("%lf", &m_desemp[i]);
		limpar_buffer();

		while (m_desemp[i] < 0 || m_desemp[i] > 10) {
			printf("Nota invalida! Deve estar entre 0 e 10: ");
			m_desemp[i] = -1;
			scanf("%lf", &m_desemp[i]);
			limpar_buffer();
		}
	}
}

// MENU DE CADASTRO -> 2. Cadastrar Dados Aleatoriamente
void cadastro_aleatorio(int *num_labs, int cap_labs[], int *qtd_dias, int lab_day[][DAYS], double m_desemp[]) {
	int i, j;

	// Numero de laboratorios
	*num_labs = (rand() % LABS) + 1;

	// Capacidade de cada laboratorio
	for (i = 0; i < *num_labs; i++) {
		cap_labs[i] = (rand() % 50) + 1;
	}

	// Quantidade de dias
	*qtd_dias = (rand() % DAYS) + 1;

	// Ocupacao de cada laboratorio em cada dia
	for (i = 0; i < *num_labs; i++) {
		for (j = 0; j < *qtd_dias; j++) {
			lab_day[i][j] = rand() % (cap_labs[i] + 1);
		}
	}

	// Media de desempenho de cada laboratorio
	for (i = 0; i < *num_labs; i++) {
		m_desemp[i] = ((double)rand() / RAND_MAX) * 10.0;
	}
}

// MENU PRINCIPAL -> 1. Cadastrar Dados
void menu_cadastro(int *num_labs, int cap_labs[], int *qtd_dias, int lab_day[][DAYS], double m_desemp[], int *ehtrue) {
	int opcao2;

	do {
		printf("\n--- MENU DE CADASTRO ---\n");
		printf("1. Cadastrar Dados Manualmente\n");
		printf("2. Cadastrar Dados Aleatoriamente (para testes)\n");
		printf("3. Sair\n");
		printf("Escolha uma opcao: ");

		opcao2 = 0;

		scanf("%d", &opcao2);
		limpar_buffer();

		switch (opcao2) {
			case 1:
				cadastro_manual(num_labs, cap_labs, qtd_dias, lab_day, m_desemp);
				*ehtrue = 1;
				opcao2 = 3;
				break;
			case 2:
				cadastro_aleatorio(num_labs, cap_labs, qtd_dias, lab_day, m_desemp);
				*ehtrue = 1;
				opcao2 = 3;
				break;
			case 3:
				printf("\nVoltando para o menu.\n");
				break;
			default:
				printf("\nOpcao invalida! Tente novamente.\n");
		}
	} while (opcao2 != 3);
}

// MENU PRINCIPAL -> 2. Visualizar Dados Inseridos
void visualizar_dados(int num_labs, int cap_labs[], int qtd_dias, double m_desemp[]) {
	int i;

	printf("\n--- DADOS INSERIDOS ---\n");
	printf("Numero de laboratorios: %d\n", num_labs);
	printf("Quantidade de dias: %d\n", qtd_dias);
	printf("\nLab | Capacidade | Media desempenho\n");

	for (i = 0; i < num_labs; i++) {
		printf("%3d | %10d | %16.2f\n", i + 1, cap_labs[i], m_desemp[i]);
	}
}

// MENU PRINCIPAL -> 3. Exibir Tabela de Ocupacao
void exibir_tabela_ocupacao(int num_labs, int qtd_dias, int lab_day[][DAYS]) {
	int i, j, inicio, fim;

	printf("\n===== TABELA DE OCUPACAO =====\n");
	for (inicio = 0; inicio < qtd_dias; inicio += BLOCO) {
		fim = inicio + BLOCO;
		if (fim > qtd_dias) {
			fim = qtd_dias;
		}

		printf("\nLaboratorio");
		for (j = inicio; j < fim; j++) {
			printf(" Dia %02d", j + 1);
		}
		printf("\n");

		for (i = 0; i < num_labs; i++) {
			printf("     Lab %02d", i + 1);
			for (j = inicio; j < fim; j++) {
				printf("%7d", lab_day[i][j]);
			}
			printf("\n");
		}
	}
}

// MENU PRINCIPAL -> 4.1 Calcular Indicadores
void calcular_indicadores(int num_labs, int cap_labs[], int qtd_dias, int lab_day[][DAYS], int total_dia[], float media_diaria[], float taxa_media[], int *aux2) {
	int i, j;
	int maior_total;

	// Total diario
	for (j = 0; j < qtd_dias; j++) {
		total_dia[j] = 0;

		for (i = 0; i < num_labs; i++) {
			total_dia[j] += lab_day[i][j];
		}

		printf("%d eh o numero de alunos no dia %d\n", total_dia[j], j + 1);
	}

	// Media diaria de cada laboratorio
	for (i = 0; i < num_labs; i++) {
		media_diaria[i] = 0;

		for (j = 0; j < qtd_dias; j++) {
			media_diaria[i] += lab_day[i][j];
		}

		media_diaria[i] /= qtd_dias;
	}

	for (i = 0; i < num_labs; i++) {
		printf("\n%.2f eh a media do lab %d\n", media_diaria[i], i + 1);
	}

	// Dia de maior movimentacao
	maior_total = total_dia[0];
	*aux2 = 0;

	for (j = 1; j < qtd_dias; j++) {
		if (total_dia[j] > maior_total) {
			maior_total = total_dia[j];
			*aux2 = j;
		}
	}

	printf("\nO maior dia eh %d\n", *aux2 + 1);

	// Taxa media de ocupacao
	for (i = 0; i < num_labs; i++) {
		taxa_media[i] = (media_diaria[i] / cap_labs[i]) * 100.0f;

		printf("\nTaxa media do laboratorio %d eh %.2f\n", i + 1, taxa_media[i]);
	}
}
// MENU PRINCIPAL -> 4.2 Calcular indicaores maior e menor
void mais_e_menos_ocupados(int num_labs, int lab_ocupado[DAYS][LABS], int qtd_dias, int lab_day[LABS][DAYS]) {
	int i, j, maior, menor, aux;
	int minimo[LABS];
	int grupo_maior_lab[LABS];
	int grupo_menor_lab[LABS];
	int contador_maior = 0;
	int contador_menor = 0;
	printf("\n=====Tabela de maior ocupacao=====\n\n");
	for (j = 0; j < qtd_dias; j++) { //define um dia fixo primeiro
		maior = lab_day[0][j]; //atribui para a variável "maior" o valor do índice de cada dia, pois só irá guardar um valor
		aux = 0;
		for (i = 0; i < num_labs; i++) { //ERA UM ANTES E ESTAVA DANDO CERTO
			if (maior < lab_day[i][j]) {
				maior = lab_day[i][j]; //a variavel maior vai passar a valer o valor de alunos e vai alterando até acabar o valor
				aux = i;
			}
		}
		for (i=0; i<LABS; i++) {
            grupo_maior_lab[i]=0;
		}
		contador_maior = 0; //CRIEI O CONTADOR MAIOR
		for (i = 1; i < num_labs; i++) { //for para verificar se há mais algum laboratório com a mesma ocupação e adiciona-lo ao vetor
            if (maior == lab_day[i][j]) {
                grupo_maior_lab[contador_maior] = i;
                contador_maior++; //INVERTI OS DOISSSSSSS

            }
		}
		printf("\n VALOR DO CONTADOR MAIOR %d\n",contador_maior);
		lab_ocupado[j][aux] = maior;
		printf("Dia %d\t Lab %d\t Ocupacao: %d alunos\n", j + 1, aux + 1, maior);
		if (contador_maior > 1) {
            printf("Dia %d contem os seguintes labs a mais\n", j+1);
            for (i = 0; i<contador_maior; i++) {
                printf("Lab %d\t\n", grupo_maior_lab[i+1]);
            }
		}
	}
	printf("\n=====Tabela de menor ocupacao=====\n\n");
	for (j = 0; j < qtd_dias; j++) {
		menor = lab_day[0][j];
		aux = 0;
		for (i = 1; i < num_labs; i++) {
			if (menor > lab_day[i][j]) {
				menor = lab_day[i][j];
				aux = i;
				if (menor == 0) {
					// PRECISA VER COMO VAI FAZER PARA APARECERE DOIS IGUAIS
				}
			}
		}
		lab_ocupado[j][aux] = menor;
		printf("Dia %d\t Lab %d\t Ocupacao: %d alunos\n", j + 1, aux + 1, menor);
	}
}
// MENU PRINCIPAL -> 5. Exibir Indicadores
void exibir_indicadores(int num_labs, int qtd_dias, int total_dia[], float media_diaria[], float taxa_media[], int aux2) {
	int i, j;

	printf("\n--- INDICADORES ---\n");
	printf("\nDia | Total de alunos\n");

	for (j = 0; j < qtd_dias; j++) {
		printf("%3d | %15d\n", j + 1, total_dia[j]);
	}

	printf("\nDia de maior movimentacao: %d\n", aux2 + 1);
	printf("\nLab | Media diaria | Taxa media (%%)\n");
	for (i = 0; i < num_labs; i++) {
		printf("%3d | %12.2f | %14.2f\n", i + 1, media_diaria[i], taxa_media[i]);
	}
}

// MENU PRINCIPAL -> 6. Laboratorio mais ocupado
void laboratorio_mais_ocupado(int num_labs, int qtd_dias, int lab_day[][DAYS]) {
	int dia = 0;
	int i;
	int maior;
	int lab_maior;

	printf("\nDigite o dia que deseja consultar (1 a %d): ", qtd_dias);

	scanf("%d", &dia);
	limpar_buffer();

	while (dia < 1 || dia > qtd_dias) {
		printf("Dia invalido! Digite um valor entre 1 e %d: ", qtd_dias);

		dia = 0;
		scanf("%d", &dia);
		limpar_buffer();
	}

	maior = lab_day[0][dia - 1];
	lab_maior = 0;

	for (i = 1; i < num_labs; i++) {
		if (lab_day[i][dia - 1] > maior) {
			maior = lab_day[i][dia - 1];
			lab_maior = i;
		}
	}

	printf("\n--- LABORATORIO MAIS OCUPADO ---\n");
	printf("Dia: %d\n", dia);
	printf("Laboratorio: %d\n", lab_maior + 1);
	printf("Ocupacao: %d alunos\n", maior);
}

// Retorna a classificacao com base em dois criterios:
// 1. Taxa media de ocupacao
// 2. Media de desempenho dos estudantes
//
// Taxa de ocupacao:
// Baixa = menor que 50%
// Media = de 50% ate menor que 80%
// Alta  = de 80% ate 100%
//
// Desempenho:
// Baixo = menor que 5
// Medio = de 5 ate menor que 8
// Alto  = de 8 ate 10
const char *obter_classificacao(float taxa, double desempenho) {
	if (taxa >= 80.0f && desempenho >= 8.0) {
		return "Excelente";
	} else if (taxa >= 80.0f && desempenho >= 5.0) {
		return "Muito bom";
	} else if (taxa >= 80.0f && desempenho < 5.0) {
		return "Atencao";
	} else if (taxa >= 50.0f && desempenho >= 8.0) {
		return "Bom";
	} else if (taxa >= 50.0f && desempenho >= 5.0) {
		return "Regular";
	} else if (taxa >= 50.0f && desempenho < 5.0) {
		return "Atencao";
	} else if (taxa < 50.0f && desempenho >= 8.0) {
		return "Bom desempenho / baixa utilizacao";
	} else if (taxa < 50.0f && desempenho >= 5.0) {
		return "Subutilizado";
	} else {
		return "Critico";
	}
}

// MENU PRINCIPAL -> 7. Classificacao dos laboratorios
void classificacao_laboratorios(int num_labs, float taxa_media[], double m_desemp[]) {
	int i;

	printf("\n===== CLASSIFICACAO DOS LABORATORIOS =====\n");
	printf("\nLab | Taxa media | Desempenho | Classificacao\n");

	for (i = 0; i < num_labs; i++) {
		printf("%3d | %10.2f%% | %10.2f | %s\n", i + 1, taxa_media[i], m_desemp[i],
		       obter_classificacao(taxa_media[i], m_desemp[i]));
	}
}

// MENU PRINCIPAL -> 8.1. Relatorio de um laboratorio
void relatorio_laboratorio(int num_labs, int qtd_dias, int cap_labs[], int lab_day[][DAYS], float media_diaria[], float taxa_media[], double m_desemp[]) {
	int lab = 0;
	int i;
	int maior;
	int menor;
	int dia_maior;
	int dia_menor;

	printf("\nDigite o laboratorio que deseja consultar (1 a %d): ", num_labs);
	scanf("%d", &lab);
	limpar_buffer();

	while (lab < 1 || lab > num_labs) {
		printf("Laboratorio invalido! Digite um valor entre 1 e %d: ", num_labs);
		lab = 0;
		scanf("%d", &lab);
		limpar_buffer();
	}
	// Maior ocupacao
	maior = lab_day[lab - 1][0];
	dia_maior = 1;

	for (i = 1; i < qtd_dias; i++) {
		if (lab_day[lab - 1][i] > maior) {
			maior = lab_day[lab - 1][i];
			dia_maior = i + 1;
		}
	}

	// Menor ocupacao
	menor = lab_day[lab - 1][0];
	dia_menor = 1;

	for (i = 1; i < qtd_dias; i++) {
		if (lab_day[lab - 1][i] < menor) {
			menor = lab_day[lab - 1][i];
			dia_menor = i + 1;
		}
	}

	printf("\n===== RELATORIO DO LABORATORIO =====\n");
	printf("Laboratorio: %d\n", lab);
	printf("Capacidade: %d alunos\n", cap_labs[lab - 1]);
	printf("Media de ocupacao: %.2f alunos\n", media_diaria[lab - 1]);
	printf("Maior ocupacao: %d alunos (Dia %d)\n", maior, dia_maior);
	printf("Menor ocupacao: %d alunos (Dia %d)\n", menor, dia_menor);
	printf("Taxa media de ocupacao: %.2f%%\n", taxa_media[lab - 1]);
	printf("Desempenho medio: %.2f\n", m_desemp[lab - 1]);
	printf("Classificacao: %s\n", obter_classificacao(taxa_media[lab - 1], m_desemp[lab - 1]));
}

// MENU PRINCIPAL -> 8.2. Relatorio final
void relatorio_final(int num_labs, int qtd_dias, int cap_labs[], int lab_day[][DAYS], float media_diaria[], float taxa_media[], double m_desemp[]) {
	int lab;
	int i;
	int maior;
	int menor;
	int dia_maior;
	int dia_menor;

	printf("\n========== RELATORIO FINAL ==========\n");
	for (lab = 0; lab < num_labs; lab++) {
		maior = lab_day[lab][0];
		dia_maior = 1;

		menor = lab_day[lab][0];
		dia_menor = 1;

		for (i = 1; i < qtd_dias; i++) {
			if (lab_day[lab][i] > maior) {
				maior = lab_day[lab][i];
				dia_maior = i + 1;
			}

			if (lab_day[lab][i] < menor) {
				menor = lab_day[lab][i];
				dia_menor = i + 1;
			}
		}

		printf("\n-------------------------------------\n");
		printf("Laboratorio: %d\n", lab + 1);
		printf("Capacidade: %d alunos\n", cap_labs[lab]);
		printf("Media de ocupacao: %.2f alunos\n", media_diaria[lab]);
		printf("Maior ocupacao: %d alunos (Dia %d)\n", maior, dia_maior);
		printf("Menor ocupacao: %d alunos (Dia %d)\n", menor, dia_menor);
		printf("Taxa media de ocupacao: %.2f%%\n", taxa_media[lab]);
		printf("Desempenho medio: %.2f\n", m_desemp[lab]);
		printf("Classificacao: %s\n", obter_classificacao(taxa_media[lab], m_desemp[lab]));
	}
	printf("\n=====================================\n");
}

// MENU PRINCIPAL -> 8. Exibir Relatorio
void menu_relatorio(int num_labs, int qtd_dias, int cap_labs[], int lab_day[][DAYS], float media_diaria[], float taxa_media[], double m_desemp[]) {
	int opcao3;

	do {
		printf("\n--- MENU DE RELATORIO ---\n");
		printf("1. Relatorio de um laboratorio\n");
		printf("2. Relatorio final\n");
		printf("3. Sair\n");
		printf("Escolha uma opcao: ");

		opcao3 = 0;

		scanf("%d", &opcao3);
		limpar_buffer();

		switch (opcao3) {
			case 1:
				relatorio_laboratorio(num_labs, qtd_dias, cap_labs, lab_day, media_diaria,taxa_media, m_desemp);
				break;
			case 2:
				relatorio_final(num_labs, qtd_dias, cap_labs, lab_day, media_diaria, taxa_media, m_desemp);
				break;
			case 3:
				printf("\nVoltando para o menu.\n");
				break;
			default:
				printf("\nOpcao invalida! Tente novamente.\n");
		}
	} while (opcao3 != 3);
}

int main() {
	int num_labs;
	int qtd_dias;

	int cap_labs[LABS];
	int lab_day[LABS][DAYS];
	int lab_ocupado[DAYS][LABS];

	double m_desemp[LABS];

	int opcao;

	int ehtrue = 0;
	int ehtrue2 = 0;

	int total_dia[DAYS];

	float media_diaria[LABS];
	float taxa_media[LABS];

	int aux2;

	srand(time(NULL));

	do {
		printf("\n--- MENU PRINCIPAL ---\n");
		printf("1. Cadastrar Dados\n");
		printf("2. Visualizar Dados Inseridos\n");
		printf("3. Exibir Tabela de Ocupacao\n");
		printf("4. Calcular Indicadores\n");
		printf("5. Exibir Indicadores\n");
		printf("6. Laboratorio mais ocupado\n");
		printf("7. Classificacao dos laboratorios\n");
		printf("8. Exibir Relatorio\n");
		printf("9. Sair\n");
		printf("Escolha uma opcao: ");

		opcao = 0;

		scanf("%d", &opcao);
		limpar_buffer();

		switch (opcao) {
			case 1:
				menu_cadastro(&num_labs, cap_labs, &qtd_dias, lab_day, m_desemp, &ehtrue);
				// Novo cadastro invalida os indicadores anteriores.
				ehtrue2 = 0;
				break;
			case 2:
				if (ehtrue == 0) {
					printf("\nFazer o cadastro dos dados primeiro.\n");
					break;
				}

				visualizar_dados(num_labs, cap_labs, qtd_dias, m_desemp);
				exibir_tabela_ocupacao(num_labs, qtd_dias, lab_day);
				break;
			case 3:
				if (ehtrue == 0) {
					printf("\nFazer o cadastro dos dados primeiro.\n");

					break;
				}
				exibir_tabela_ocupacao(num_labs, qtd_dias, lab_day);
				mais_e_menos_ocupados(num_labs, lab_ocupado, qtd_dias, lab_day);
				break;
			case 4:
				if (ehtrue == 0) {
					printf("\nFazer o cadastro dos dados primeiro.\n");
					break;
				}
				calcular_indicadores(num_labs, cap_labs, qtd_dias, lab_day, total_dia, media_diaria, taxa_media, &aux2);
				ehtrue2 = 1;
				break;
			case 5:
				if (ehtrue == 0 || ehtrue2 == 0) {
					printf("\nFazer o cadastro dos dados e calcular indicadores primeiro.\n");
					break;
				}
				exibir_indicadores(num_labs, qtd_dias, total_dia, media_diaria, taxa_media, aux2);
				break;
			case 6:
				if (ehtrue == 0) {
					printf("\nFazer o cadastro dos dados primeiro.\n");
					break;
				}
				laboratorio_mais_ocupado(num_labs, qtd_dias, lab_day);
				break;
			case 7:
				if (ehtrue == 0 || ehtrue2 == 0) {
					printf("\nFazer o cadastro dos dados e calcular indicadores primeiro.\n");
					break;
				}
				classificacao_laboratorios(num_labs, taxa_media, m_desemp);
				break;
			case 8:
				if (ehtrue == 0 || ehtrue2 == 0) {
					printf("\nFazer o cadastro dos dados e calcular indicadores primeiro.\n");
					break;
				}
				menu_relatorio(num_labs, qtd_dias, cap_labs, lab_day, media_diaria, taxa_media, m_desemp);
				break;
			case 9:
				printf("\nSaindo do programa...\n");
				break;
			default:
				printf("\nOpcao invalida! Tente novamente.\n");
		}
		if (opcao != 9) {
			pausar();
		}
	} while (opcao != 9);
	return 0;
}
