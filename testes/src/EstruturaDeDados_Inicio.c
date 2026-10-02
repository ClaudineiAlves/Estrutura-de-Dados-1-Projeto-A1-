#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LABS 20
#define DAYS 30
#define coluna 30

// Descarta o que sobrou na linha depois do scanf (o '\n' do ENTER ou letras digitadas
// no lugar de numero). Sem isso, uma letra fica presa na entrada e o while de validacao
// le a mesma coisa para sempre. Se a entrada acabar (EOF), nao ha mais o que ler,
// entao o programa encerra em vez de repetir o menu sem parar.
void limpar_buffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
	if (c == EOF) {
		printf("\nFim da entrada. Encerrando...\n");
		exit(0);
	}
}

// Segura a tela ate apertar ENTER
void pausar()
{
	printf("\nPressione ENTER para continuar...");
	limpar_buffer();
}

// MENU DE CADASTRO -> 1. Cadastrar Dados Manualmente
// (fica antes de menu_cadastro porque e chamada por ela)
void cadastro_manual(int *num_labs, int cap_labs[], int *qtd_dias, int lab_day[][DAYS],
                     double m_desemp[])
{
	int i, j;

	// Numero de laboratorios:
	printf("\nInsira o numero de laboratorios (1 a %d): ", LABS);
	// Se o scanf falhar (letra), a variavel nao muda. Comecar com um valor invalido
	// garante que a letra caia no while de "Valor invalido" em vez de passar.
	*num_labs = 0;
	scanf("%d", num_labs); // num_labs ja e ponteiro, entao nao leva &
	limpar_buffer();
	while (*num_labs < 1 || *num_labs > LABS) {
		printf("Valor invalido! Tente novamente: ");
		*num_labs = 0;
		scanf("%d", num_labs);
		limpar_buffer();
	}

	// Capacidade de cada laboratorio:
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

	// Quantidade de dias:
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

	// Ocupacao de cada lab em cada dia (Leitura da Matriz):
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

	// Media de desempenho de cada laboratorio:
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

// MENU DE CADASTRO -> 2. Cadastrar Dados Aleatoriamente(para testes)
// (fica antes de menu_cadastro porque e chamada por ela)
void cadastro_aleatorio(int *num_labs, int cap_labs[], int *qtd_dias, int lab_day[][DAYS],
                        double m_desemp[])
{
	int i, j;

	// Numero de laboratorios:
	*num_labs = (rand() % 20) + 1;
	while (*num_labs < 1 || *num_labs > LABS) {
		*num_labs = (rand() % 20) + 1;
	}

	// Capacidade de cada laboratorio:
	for (i = 0; i < *num_labs; i++) {
		cap_labs[i] = (rand() % 50) + 1;
		while (cap_labs[i] <= 0) {
			cap_labs[i] = (rand() % 50) + 1;
		}
	}

	// Quantidade de dias:
	*qtd_dias = (rand() % 20) + 1;
	while (*qtd_dias < 1 || *qtd_dias > DAYS) {
		*qtd_dias = (rand() % 20) + 1;
	}

	// Ocupacao de cada lab em cada dia (Leitura da Matriz):
	for (i = 0; i < *num_labs; i++) {
		for (j = 0; j < *qtd_dias; j++) {
			lab_day[i][j] = (rand() % 50) + 1;

			while (lab_day[i][j] < 0 || lab_day[i][j] > cap_labs[i]) {
				lab_day[i][j] = (rand() % 50) + 1;
			}
		}
	}

	// Media de desempenho de cada laboratorio:
	for (i = 0; i < *num_labs; i++) {
		m_desemp[i] = ((double)rand() / RAND_MAX) * 10.0;
		while (m_desemp[i] < 0 || m_desemp[i] > 10) {
			m_desemp[i] = ((double)rand() / RAND_MAX) * 10.0;
		}
	}
}

// MENU PRINCIPAL -> 1. Cadastrar Dados
void menu_cadastro(int *num_labs, int cap_labs[], int *qtd_dias, int lab_day[][DAYS],
                   double m_desemp[], int *ehtrue)
{
	int opcao2;

	do {
		// Exibe o menu na tela
		printf("\n--- MENU DE CADASTRO ---\n");
		printf("1. Cadastrar Dados Manualmente\n");
		printf("2. Cadastrar Dados Aleatoriamente(para testes)\n");
		printf("3. Sair\n");
		printf("Escolha uma opcao: ");

		// Lê a escolha do usuário
		opcao2 = 0;
		scanf("%d", &opcao2);
		limpar_buffer();

		switch (opcao2) {
			case 1:
				cadastro_manual(num_labs, cap_labs, qtd_dias, lab_day, m_desemp);
				*ehtrue = 1;
				break;
			case 2:
				cadastro_aleatorio(num_labs, cap_labs, qtd_dias, lab_day, m_desemp);
				*ehtrue = 1;
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
void visualizar_dados(int num_labs, int cap_labs[], int qtd_dias, double m_desemp[])
{
	int i;

	printf("\n--- DADOS INSERIDOS ---\n");
	printf("Numero de laboratorios: %d\n", num_labs);
	printf("Quantidade de dias: %d\n", qtd_dias);

	// Capacidade e media de desempenho de cada lab
	printf("\nLab | Capacidade | Media desempenho\n");
	for (i = 0; i < num_labs; i++) {
		printf("%3d | %10d | %16.2f\n", i + 1, cap_labs[i], m_desemp[i]);
	}
}

// MENU PRINCIPAL -> 3. Exibir Tabela de Ocupacao
void exibir_tabela_ocupacao(int num_labs, int qtd_dias, int lab_day[][DAYS])
{
	int i, j;

	// Ocupacao: linha = lab, coluna = dia
	printf("\nOcupacao por dia:\n");
	printf("Lab ");
	for (j = 0; j < qtd_dias; j++) {
		printf("D%-3d", j + 1); // cabeçalho dos dias
	}

	printf("\n");
	for (i = 0; i < num_labs; i++) {
		printf("%3d ", i + 1);
		for (j = 0; j < qtd_dias; j++) {
			printf("%-4d", lab_day[i][j]);
		}
		printf("\n");
	}
}

// MENU PRINCIPAL -> 4. Calcular Indicadores
void calcular_indicadores(int num_labs, int cap_labs[], int qtd_dias, int lab_day[][DAYS],
                          int total_dia[], float media_diaria[], float taxa_media[], int *aux2)
{
	int i, j, aux;

	printf("\n");
	for (j = 0; j < qtd_dias; j++) // for que começa o calculo de alunos no total de cada dia
	{
		total_dia[j] = 0;              // reinicia sempre para começar outro dia
		for (i = 0; i < num_labs; i++) // usa esse for para passar de lab em lab no mesmo dia
		{
			total_dia[j] = total_dia[j] + lab_day[i][j];
			// o total de aluno começou em 0, e para
			// cada lab ele aumenta um i e permanece
			// no mesmo J até acabar os labs do dia
		}
		printf("%d eh o numero de alunos no dia %d\n", total_dia[j],
		       j + 1); // PRINT DE TESTE
	}
	for (i = 0; i < num_labs; i++) // lab é fixo, então começa usando i no for
	{
		media_diaria[i] = 0;
		for (j = 0; j < qtd_dias; j++) {
			media_diaria[i] = media_diaria[i] + lab_day[i][j];
		}
		media_diaria[i] =
		    media_diaria[i] / qtd_dias; // média da quantidade pela quantidade de dias na pesquisa
	}
	for (i = 0; i < num_labs; i++) // PRINT DE TESTE
	{
		printf("\n%.2f eh a media do lab %d\n", media_diaria[i], i + 1);
	}
	j = 0;
	aux = total_dia[j];

	*aux2 = 0;
	for (j = 0; j < qtd_dias; j++) {
		if (aux < total_dia[j + 1]) {
			aux = total_dia[j + 1];
			// erro do dia errado
			*aux2 = j + 1;
		} else {
		}
	}
	printf("\nO maior dia eh %d\n", *aux2 + 1); // PRINT DE TESTE
	for (i = 0; i < num_labs; i++) {
		taxa_media[i] = 0;
		taxa_media[i] = (media_diaria[i] / cap_labs[i]) * 100;
		printf("\nTaxa media do laboratorio %d eh %.2f \n", i + 1, taxa_media[i]);
	}
}

// MENU PRINCIPAL -> 5. Exibir Indicadores
void exibir_indicadores(int num_labs, int qtd_dias, int total_dia[], float media_diaria[],
                        float taxa_media[], int aux2)
{
	int i, j;

	printf("\n--- INDICADORES ---\n");

	// Total de alunos de cada dia
	printf("\nDia | Total de alunos\n");
	for (j = 0; j < qtd_dias; j++) {
		printf("%3d | %15d\n", j + 1, total_dia[j]);
	}
	printf("\nDia de maior movimentacao: %d\n", aux2 + 1);

	// Media diaria e taxa media de ocupacao de cada lab
	printf("\nLab | Media diaria | Taxa media (%%)\n");
	for (i = 0; i < num_labs; i++) {
		printf("%3d | %12.2f | %14.2f\n", i + 1, media_diaria[i], taxa_media[i]);
	}
}

// MENU PRINCIPAL -> 6. Laboratorio mais ocupado
// TODO: adicionar os parametros necessarios
void laboratorio_mais_ocupado() {}

// MENU PRINCIPAL -> 7. Classificacao dos laboratorios
// TODO: adicionar os parametros necessarios
void classificacao_laboratorios() {}

// MENU PRINCIPAL -> 8. Exibir Relatorio
void menu_relatorio()
{
	int opcao3;

	do {
		printf("\n--- MENU DE RELATÓRIO ---\n");
		printf("1. Relatório de um laboratório\n");
		printf("2. Relatório final\n");
		printf("3. Sair\n");
		printf("Escolha uma opcao: ");

		// Lê a escolha do usuário
		opcao3 = 0;
		scanf("%d", &opcao3);
		limpar_buffer();
		switch (opcao3) {
			case 1:
				break;
			case 2:
				break;
			case 3:
				printf("\nVoltando para o menu.\n");
				break;
			default:
				printf("\nOpcao invalida! Tente novamente.\n");
		}
	} while (opcao3 != 3);
}

int main()
{
	int num_labs, qtd_dias;
	int cap_labs[LABS];      // Capacidade dos laboratorios
	int lab_day[LABS][DAYS]; // Matriz de cada laboratorio por dia
	double m_desemp[LABS];   // Media de desempenho
	int opcao, ehtrue = 0;
	int total_dia[DAYS];
	float media_diaria[DAYS];
	float taxa_media[LABS];
	int aux2;

	srand(time(NULL));

	do {
		// Exibe o menu na tela
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

		// Lê a escolha do usuário
		opcao = 0;
		scanf("%d", &opcao);
		limpar_buffer();

		// Controla o fluxo com switch-case
		switch (opcao) {
			case 1:
				menu_cadastro(&num_labs, cap_labs, &qtd_dias, lab_day, m_desemp, &ehtrue);
				break;
			case 2:
				// verificação se dados foram inseridos
				if (ehtrue == 0) {
					printf("\nFazer o cadastro dos dados primeiro.\n");
					break;
				}
				visualizar_dados(num_labs, cap_labs, qtd_dias, m_desemp);
				exibir_tabela_ocupacao(num_labs, qtd_dias, lab_day);

				break;
			case 3:
				// verificação se dados foram inseridos
				if (ehtrue == 0) {
					printf("\nFazer o cadastro dos dados primeiro.\n");
					break;
				}
				exibir_tabela_ocupacao(num_labs, qtd_dias, lab_day);
				break;
			case 4:
				// verificação se dados foram inseridos
				if (ehtrue == 0) {
					printf("\nFazer o cadastro dos dados primeiro.\n");
					break;
				}
				calcular_indicadores(num_labs, cap_labs, qtd_dias, lab_day, total_dia, media_diaria,
				                     taxa_media, &aux2);
				break;
			case 5:
				// verificação se dados foram inseridos
				// verificação se dados foram calculados
				if (ehtrue == 0) {
					printf("\nFazer o cadastro dos dados primeiro.\n");
					break;
				}
				exibir_indicadores(num_labs, qtd_dias, total_dia, media_diaria, taxa_media, aux2);
				break;
			case 6:
				// verificação se dados foram inseridos
				// verificação se dados foram calculados
				if (ehtrue == 0) {
					printf("\nFazer o cadastro dos dados primeiro.\n");
					break;
				}
				laboratorio_mais_ocupado();
				break;
			case 7:
				// verificação se dados foram inseridos
				// verificação se dados foram calculados
				if (ehtrue == 0) {
					printf("\nFazer o cadastro dos dados primeiro.\n");
					break;
				}
				classificacao_laboratorios();
				break;
			case 8:
				// verificação se dados foram inseridos
				// verificação se dados foram calculados
				if (ehtrue == 0) {
					printf("\nFazer o cadastro dos dados primeiro.\n");
					break;
				}
				menu_relatorio();
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
