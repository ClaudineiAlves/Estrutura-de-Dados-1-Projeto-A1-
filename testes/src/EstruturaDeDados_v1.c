#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LABS 20
#define DAYS 30
#define BLOCO 15
#define TOLERANCIA 0.001f

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
void cadastro_manual(int *num_labs, int cap_labs[], int *qtd_dias, int lab_day[][DAYS],
                     double m_desemp[]) {
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

		// Condicao negada para recusar tambem "nan", que falha em qualquer comparacao.
		while (!(m_desemp[i] >= 0 && m_desemp[i] <= 10)) {
			printf("Nota invalida! Deve estar entre 0 e 10: ");
			m_desemp[i] = -1;
			scanf("%lf", &m_desemp[i]);
			limpar_buffer();
		}
	}
}

// Confere os dados com as mesmas regras do cadastro manual.
// Retorna 1 se tudo for valido; senao avisa o primeiro erro e retorna 0.
int validar_dados(int num_labs, int cap_labs[], int qtd_dias, int lab_day[][DAYS],
                  double m_desemp[]) {
	int i, j;

	if (num_labs < 1 || num_labs > LABS) {
		printf("Numero de laboratorios invalido: %d\n", num_labs);
		return 0;
	}

	if (qtd_dias < 1 || qtd_dias > DAYS) {
		printf("Quantidade de dias invalida: %d\n", qtd_dias);
		return 0;
	}

	for (i = 0; i < num_labs; i++) {
		if (cap_labs[i] <= 0) {
			printf("Capacidade invalida no Lab %d: %d\n", i + 1, cap_labs[i]);
			return 0;
		}

		for (j = 0; j < qtd_dias; j++) {
			if (lab_day[i][j] < 0 || lab_day[i][j] > cap_labs[i]) {
				printf("Ocupacao invalida no Lab %d, dia %d: %d\n", i + 1, j + 1, lab_day[i][j]);
				return 0;
			}
		}

		if (!(m_desemp[i] >= 0 && m_desemp[i] <= 10)) {
			printf("Nota invalida no Lab %d: %.2f\n", i + 1, m_desemp[i]);
			return 0;
		}
	}

	return 1;
}

// MENU DE CADASTRO -> 2. Cadastrar Dados Aleatoriamente
void cadastro_aleatorio(int *num_labs, int cap_labs[], int *qtd_dias, int lab_day[][DAYS],
                        double m_desemp[]) {
	int i, j;

	// Gera de novo enquanto algum valor nao passar na validacao
	do {
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
	} while (!validar_dados(*num_labs, cap_labs, *qtd_dias, lab_day, m_desemp));
}

// MENU PRINCIPAL -> 1. Cadastrar dados
void menu_cadastro(int *num_labs, int cap_labs[], int *qtd_dias, int lab_day[][DAYS],
                   double m_desemp[], int *ehtrue) {
	int opcao2;

	do {
		printf("\n--- MENU DE CADASTRO ---\n");
		printf("1 - Cadastrar Dados Manualmente\n");
		printf("2 - Cadastrar Dados Aleatoriamente (para testes)\n");
		printf("0 - Voltar\n");
		printf("Escolha uma opcao: ");

		// -1 e nao 0: se o usuario digitar letras, nao pode cair no "Voltar".
		opcao2 = -1;

		scanf("%d", &opcao2);
		limpar_buffer();

		switch (opcao2) {
			case 1:
				cadastro_manual(num_labs, cap_labs, qtd_dias, lab_day, m_desemp);
				*ehtrue = 1;
				opcao2 = 0;
				break;
			case 2:
				cadastro_aleatorio(num_labs, cap_labs, qtd_dias, lab_day, m_desemp);
				printf("\nDados aleatorios cadastrados: %d laboratorios, %d dias.\n", *num_labs,
				       *qtd_dias);
				*ehtrue = 1;
				opcao2 = 0;
				break;
			case 0:
				printf("\nVoltando para o menu.\n");
				break;
			default:
				printf("\nOpcao invalida! Tente novamente.\n");
		}
	} while (opcao2 != 0);
}

// MENU PRINCIPAL -> 2. Exibir Tabela de Ocupacao
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

// Calcula os indicadores que ficam guardados nos vetores.
// Chamada logo apos cada cadastro, para a classificacao e os relatorios ja terem os valores.
void calcular_indicadores(int num_labs, int cap_labs[], int qtd_dias, int lab_day[][DAYS],
                          int total_dia[], float media_diaria[], float taxa_media[]) {
	int i, j;

	// Total diario
	for (j = 0; j < qtd_dias; j++) {
		total_dia[j] = 0;

		for (i = 0; i < num_labs; i++) {
			total_dia[j] += lab_day[i][j];
		}
	}

	// Media diaria de cada laboratorio
	for (i = 0; i < num_labs; i++) {
		media_diaria[i] = 0;

		for (j = 0; j < qtd_dias; j++) {
			media_diaria[i] += lab_day[i][j];
		}

		media_diaria[i] /= qtd_dias;
	}

	// Taxa media de ocupacao
	for (i = 0; i < num_labs; i++) {
		taxa_media[i] = (media_diaria[i] / cap_labs[i]) * 100.0f;
	}
}

// Maior e menor ocupacao de toda a matriz, listando todos os empates.
void exibir_maior_menor_ocupacao(int num_labs, int qtd_dias, int lab_day[][DAYS]) {
	int i, j, maior, menor;

	// 1a passagem: encontra o maior e o menor valor
	maior = lab_day[0][0];
	menor = lab_day[0][0];

	for (i = 0; i < num_labs; i++) {
		for (j = 0; j < qtd_dias; j++) {
			if (lab_day[i][j] > maior) {
				maior = lab_day[i][j];
			}
			if (lab_day[i][j] < menor) {
				menor = lab_day[i][j];
			}
		}
	}

	// 2a passagem: imprime todos os pares (lab, dia) com esses valores
	printf("\nMaior ocupacao: %d alunos\n", maior);
	for (i = 0; i < num_labs; i++) {
		for (j = 0; j < qtd_dias; j++) {
			if (lab_day[i][j] == maior) {
				printf("  Lab %02d - Dia %02d\n", i + 1, j + 1);
			}
		}
	}

	printf("\nMenor ocupacao: %d alunos\n", menor);
	for (i = 0; i < num_labs; i++) {
		for (j = 0; j < qtd_dias; j++) {
			if (lab_day[i][j] == menor) {
				printf("  Lab %02d - Dia %02d\n", i + 1, j + 1);
			}
		}
	}
}

// MENU PRINCIPAL -> 3. Calcular indicadores
void exibir_indicadores(int num_labs, int qtd_dias, int lab_day[][DAYS], int total_dia[],
                        float media_diaria[], float taxa_media[], int cap_labs[],
                        double m_desemp[]) {
	int i, j;
	int maior_total;
	int capacidade_total;
	printf("\n===== DADOS INSERIDOS =====\n");
	printf("Numero de laboratorios: %d\n", num_labs);
	printf("Quantidade de dias: %d\n", qtd_dias);
	printf("\nLab | Capacidade | Media desempenho\n");

	for (i = 0; i < num_labs; i++) {
		printf("%3d | %10d | %16.2f\n", i + 1, cap_labs[i], m_desemp[i]);
	}
	printf("\n===== INDICADORES =====\n");

	// Total diario de ocupacao
	printf("\n--- Total diario de ocupacao ---\n");
	printf("Dia | Total de alunos\n");
	for (j = 0; j < qtd_dias; j++) {
		printf("%3d | %15d\n", j + 1, total_dia[j]);
	}

	// Media diaria de ocupacao
	printf("\n--- Media diaria de ocupacao ---\n");
	printf("Lab | Media diaria\n");
	for (i = 0; i < num_labs; i++) {
		printf("%3d | %12.2f\n", i + 1, media_diaria[i]);
	}

	// Maior e menor ocupacao
	printf("\n--- Maior e menor ocupacao ---");
	exibir_maior_menor_ocupacao(num_labs, qtd_dias, lab_day);

	// Dia de maior movimentacao (todos os dias empatados)
	maior_total = total_dia[0];
	for (j = 1; j < qtd_dias; j++) {
		if (total_dia[j] > maior_total) {
			maior_total = total_dia[j];
		}
	}

	printf("\n--- Dia de maior movimentacao ---\n");
	printf("Total: %d alunos\n", maior_total);
	for (j = 0; j < qtd_dias; j++) {
		if (total_dia[j] == maior_total) {
			printf("  Dia %02d\n", j + 1);
		}
	}

	// Compara com a soma das capacidades de todos os laboratorios
	capacidade_total = 0;
	for (i = 0; i < num_labs; i++) {
		capacidade_total += cap_labs[i];
	}

	printf("Capacidade total dos laboratorios: %d alunos (%.2f%% ocupada)\n", capacidade_total,
	       (float)maior_total / capacidade_total * 100.0f);
	if (maior_total >= capacidade_total) {
		printf("Atingiu a capacidade total!\n");
	} else {
		printf("Nao atingiu a capacidade total (sobraram %d vagas).\n",
		       capacidade_total - maior_total);
	}

	// Taxa media de ocupacao
	printf("\n--- Taxa media de ocupacao ---\n");
	printf("Lab | Taxa media (%%)\n");
	for (i = 0; i < num_labs; i++) {
		printf("%3d | %14.2f\n", i + 1, taxa_media[i]);
	}
}

// MENU PRINCIPAL -> 4. Laboratorio mais ocupado
void laboratorio_mais_ocupado(int num_labs, int qtd_dias, int lab_day[][DAYS]) {
	int dia = 0;
	int i;
	int maior;

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

	for (i = 1; i < num_labs; i++) {
		if (lab_day[i][dia - 1] > maior) {
			maior = lab_day[i][dia - 1];
		}
	}

	printf("\n--- LABORATORIO MAIS OCUPADO ---\n");
	printf("Dia: %d\n", dia);
	printf("Ocupacao: %d alunos\n", maior);
	printf("Laboratorio(s):\n");
	for (i = 0; i < num_labs; i++) {
		if (lab_day[i][dia - 1] == maior) {
			printf("  Lab %02d\n", i + 1);
		}
	}
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
	// O float pode guardar 80% exato como 79.999992 (ex.: media 7.2 / capacidade 9).
	// A margem corrige isso sem mudar nenhum outro caso: taxas possiveis diferentes
	// distam pelo menos 100 / (50 * 30) = 0.067 ponto percentual entre si.
	taxa += TOLERANCIA;

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

// MENU PRINCIPAL -> 5. Classificacao dos laboratorios
void classificacao_laboratorios(int num_labs, float taxa_media[], double m_desemp[]) {
	int i;

	printf("\n===== CLASSIFICACAO DOS LABORATORIOS =====\n");
	printf("\nLab | Taxa media | Desempenho | Classificacao\n");

	for (i = 0; i < num_labs; i++) {
		printf("%3d | %10.2f%% | %10.2f | %s\n", i + 1, taxa_media[i], m_desemp[i],
		       obter_classificacao(taxa_media[i], m_desemp[i]));
	}
}

// Imprime os dias em que o laboratorio teve exatamente "valor" alunos.
void imprimir_dias_com_valor(int lab, int qtd_dias, int lab_day[][DAYS], int valor) {
	int j;
	int primeiro = 1;

	printf("(Dia ");
	for (j = 0; j < qtd_dias; j++) {
		if (lab_day[lab][j] == valor) {
			if (!primeiro) {
				printf(", ");
			}
			printf("%d", j + 1);
			primeiro = 0;
		}
	}
	printf(")\n");
}

// Bloco de informacoes de um laboratorio, usado pelos dois relatorios.
void imprimir_relatorio_lab(int lab, int qtd_dias, int cap_labs[], int lab_day[][DAYS],
                            float media_diaria[], float taxa_media[], double m_desemp[]) {
	int i;
	int maior = lab_day[lab][0];
	int menor = lab_day[lab][0];

	for (i = 1; i < qtd_dias; i++) {
		if (lab_day[lab][i] > maior) {
			maior = lab_day[lab][i];
		}
		if (lab_day[lab][i] < menor) {
			menor = lab_day[lab][i];
		}
	}

	printf("Laboratorio: %d\n", lab + 1);
	printf("Capacidade: %d alunos\n", cap_labs[lab]);
	printf("Media de ocupacao: %.2f alunos\n", media_diaria[lab]);
	printf("Maior ocupacao: %d alunos ", maior);
	imprimir_dias_com_valor(lab, qtd_dias, lab_day, maior);
	printf("Menor ocupacao: %d alunos ", menor);
	imprimir_dias_com_valor(lab, qtd_dias, lab_day, menor);
	printf("Taxa media de ocupacao: %.2f%%\n", taxa_media[lab]);
	printf("Desempenho medio: %.2f\n", m_desemp[lab]);
	printf("Classificacao: %s\n", obter_classificacao(taxa_media[lab], m_desemp[lab]));
}

// MENU DE RELATORIO -> 1. Relatorio de um laboratorio
void relatorio_laboratorio(int num_labs, int qtd_dias, int cap_labs[], int lab_day[][DAYS],
                           float media_diaria[], float taxa_media[], double m_desemp[]) {
	int lab = 0;

	printf("\nDigite o laboratorio que deseja consultar (1 a %d): ", num_labs);
	scanf("%d", &lab);
	limpar_buffer();

	while (lab < 1 || lab > num_labs) {
		printf("Laboratorio invalido! Digite um valor entre 1 e %d: ", num_labs);
		lab = 0;
		scanf("%d", &lab);
		limpar_buffer();
	}

	printf("\n===== RELATORIO DO LABORATORIO =====\n");
	imprimir_relatorio_lab(lab - 1, qtd_dias, cap_labs, lab_day, media_diaria, taxa_media,
	                       m_desemp);
}

// MENU DE RELATORIO -> 2. Relatorio final
void relatorio_final(int num_labs, int qtd_dias, int cap_labs[], int lab_day[][DAYS],
                     float media_diaria[], float taxa_media[], double m_desemp[]) {
	int lab;

	printf("\n========== RELATORIO FINAL ==========\n");
	printf("Laboratorios: %d | Dias: %d\n", num_labs, qtd_dias);
	exibir_tabela_ocupacao(num_labs, qtd_dias, lab_day);

	for (lab = 0; lab < num_labs; lab++) {
		printf("\n-------------------------------------\n");
		imprimir_relatorio_lab(lab, qtd_dias, cap_labs, lab_day, media_diaria, taxa_media,
		                       m_desemp);
	}
	printf("\n=====================================\n");
}

// MENU PRINCIPAL -> 6. Exibir relatorio
void menu_relatorio(int num_labs, int qtd_dias, int cap_labs[], int lab_day[][DAYS],
                    float media_diaria[], float taxa_media[], double m_desemp[]) {
	int opcao3;

	do {
		printf("\n--- MENU DE RELATORIO ---\n");
		printf("1 - Relatorio de um laboratorio\n");
		printf("2 - Relatorio final\n");
		printf("0 - Voltar\n");
		printf("Escolha uma opcao: ");

		opcao3 = -1;

		scanf("%d", &opcao3);
		limpar_buffer();

		switch (opcao3) {
			case 1:
				relatorio_laboratorio(num_labs, qtd_dias, cap_labs, lab_day, media_diaria,
				                      taxa_media, m_desemp);
				break;
			case 2:
				relatorio_final(num_labs, qtd_dias, cap_labs, lab_day, media_diaria, taxa_media,
				                m_desemp);
				break;
			case 0:
				printf("\nVoltando para o menu.\n");
				break;
			default:
				printf("\nOpcao invalida! Tente novamente.\n");
		}
	} while (opcao3 != 0);
}

int main() {
	int num_labs = 0;
	int qtd_dias = 0;

	int cap_labs[LABS];
	int lab_day[LABS][DAYS];

	double m_desemp[LABS];

	int opcao;

	int ehtrue = 0;

	int total_dia[DAYS];

	float media_diaria[LABS];
	float taxa_media[LABS];

	srand(time(NULL));

	do {
		printf("\n--- MENU PRINCIPAL ---\n");
		printf("1 - Cadastrar dados\n");
		printf("2 - Exibir tabela de ocupacao\n");
		printf("3 - Calcular indicadores\n");
		printf("4 - Laboratorio mais ocupado\n");
		printf("5 - Classificacao dos laboratorios\n");
		printf("6 - Exibir relatorio\n");
		printf("0 - Encerrar\n");
		printf("Escolha uma opcao: ");

		// -1 e nao 0: se o usuario digitar letras, o programa nao pode encerrar.
		opcao = -1;

		scanf("%d", &opcao);
		limpar_buffer();

		if (opcao >= 2 && opcao <= 6 && ehtrue == 0) {
			printf("\nFazer o cadastro dos dados primeiro.\n");
		} else {
			switch (opcao) {
				case 1:
					menu_cadastro(&num_labs, cap_labs, &qtd_dias, lab_day, m_desemp, &ehtrue);
					if (ehtrue == 1) {
						calcular_indicadores(num_labs, cap_labs, qtd_dias, lab_day, total_dia,
						                     media_diaria, taxa_media);
					}
					break;
				case 2:
					exibir_tabela_ocupacao(num_labs, qtd_dias, lab_day);
					break;
				case 3:
					exibir_indicadores(num_labs, qtd_dias, lab_day, total_dia, media_diaria,
					                   taxa_media, cap_labs, m_desemp);
					break;
				case 4:
					laboratorio_mais_ocupado(num_labs, qtd_dias, lab_day);
					break;
				case 5:
					classificacao_laboratorios(num_labs, taxa_media, m_desemp);
					break;
				case 6:
					menu_relatorio(num_labs, qtd_dias, cap_labs, lab_day, media_diaria, taxa_media,
					               m_desemp);
					break;
				case 0:
					printf("\nEncerrando o programa...\n");
					break;
				default:
					printf("\nOpcao invalida! Tente novamente.\n");
			}
		}

		if (opcao != 0) {
			pausar();
		}
	} while (opcao != 0);
	return 0;
}
