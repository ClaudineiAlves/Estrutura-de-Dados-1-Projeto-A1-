#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LABS 20
#define DAYS 30

int main()
{
	int num_labs, qtd_dias, i, j;
	int cap_labs[LABS];                   // Capacidade dos laboratorios
	int lab_day[LABS][DAYS];              // Matriz de cada laboratorio por dia
	double m_desemp[LABS];                // Media de desempenho
	int qtd_alunos = 0, total_alunos = 0; // quantidades de alunos nos laboratórios e total no dia
	int opcao, opcao2, opcao3, ehtrue = 0;
	int coluna = 0;
	int total_diario, media_diaria, maior_ocupacao, menor_ocupacao, dia_de_maior_mov;
	srand(time(NULL));

	do {
		// Exibe o menu na tela
		printf("\n--- MENU PRINCIPAL ---\n");
		printf("1. Cadastrar Dados\n");
		printf("2. Visualizar Dados Inseridos\n");
		printf("3. Exibir Tabela de Ocupação\n");
		printf("4. Calcular Indicadores\n");
		printf("5. Exibir Indicadores\n");
		printf("6. Laboratório mais oucapado\n");
		printf("7. Classificação dos laboratóric\n");
		printf("8. Exibir Relatório\n");

		printf("9. Sair\n");
		printf("Escolha uma opcao: ");

		// Lê a escolha do usuário
		scanf("%d", &opcao);

		// Controla o fluxo com switch-case
		switch (opcao) {
			case 1:
				do {
					// Exibe o menu na tela
					printf("\n--- MENU DE CADASTRO ---\n");
					printf("1. Cadastrar Dados Manualmente\n");
					printf("2. Cadastrar Dados Aleatoriamente(para testes)\n");
					printf("3. Sair\n");
					printf("Escolha uma opcao: ");

					// Lê a escolha do usuário
					scanf("%d", &opcao2);

					switch (opcao2) {
						case 1:
							// Numero de laboratorios:
							printf("Insira o numero de laboratorios (1 a %d): ", LABS);
							scanf("%d", &num_labs);
							while (num_labs < 1 || num_labs > LABS) {
								printf("Valor invalido! Tente novamente: ");
								scanf("%d", &num_labs);
							}

							// Capacidade de cada laboratorio:
							printf("\nInsira a capacidade de cada laboratorio:\n");
							for (i = 0; i < num_labs; i++) {
								printf("Laboratorio %d: ", i + 1);
								scanf("%d", &cap_labs[i]);

								// Ainda não decidido se pode passar a capacidade maxima
								/*
								while (cap_labs[i] <= 0) {
								    printf("Capacidade invalida! Deve ser maior que 0: ");
								    scanf("%d", &cap_labs[i]);
								}
								*/
							}

							// Quantidade de dias:
							printf("\nInsira a quantidade de dias que deseja acompanhar (1 a %d): ",
							       DAYS);
							scanf("%d", &qtd_dias);
							while (qtd_dias < 1 || qtd_dias > DAYS) {
								printf("Valor invalido! Tente novamente: ");
								scanf("%d", &qtd_dias);
							}

							// Ocupacao de cada lab em cada dia (Leitura da Matriz):
							printf("\nInsira o numero de ocupacao de cada laboratorio em cada "
							       "dia:\n");
							for (i = 0; i < num_labs; i++) {
								for (j = 0; j < qtd_dias; j++) {
									printf("Lab %d, dia %d: ", i + 1, j + 1);
									scanf("%d", &lab_day[i][j]);
									while (lab_day[i][j] < 0 || lab_day[i][j] > cap_labs[i]) {
										printf(
										    "Invalido! O numero inserido deve estar entre 0 e %d: ",
										    cap_labs[i]);
										scanf("%d", &lab_day[i][j]);
									}
								}
							}

							// Media de desempenho de cada laboratorio:
							printf("\nInforme a media de desempenho de cada laboratorio (0 a "
							       "10):\n");
							for (i = 0; i < num_labs; i++) {
								printf("Laboratorio %d: ", i + 1);
								scanf("%lf", &m_desemp[i]);
								while (m_desemp[i] < 0 || m_desemp[i] > 10) {
									printf("Nota invalida! Deve estar entre 0 e 10: ");
									scanf("%lf", &m_desemp[i]);
								}
							}
							ehtrue = 1;
							break;
						case 2:
							// Numero de laboratorios:
							num_labs = (rand() % 20) + 1;
							while (num_labs < 1 || num_labs > LABS) {
								num_labs = (rand() % 20) + 1;
							}

							// Capacidade de cada laboratorio:
							for (i = 0; i < num_labs; i++) {
								cap_labs[i] = (rand() % 50) + 1;
								while (cap_labs[i] <= 0) {
									cap_labs[i] = (rand() % 50) + 1;
								}
							}

							// Quantidade de dias:
							qtd_dias = (rand() % 20) + 1;
							while (qtd_dias < 1 || qtd_dias > DAYS) {
								qtd_dias = (rand() % 20) + 1;
							}

							// Ocupacao de cada lab em cada dia (Leitura da Matriz):
							for (i = 0; i < num_labs; i++) {
								for (j = 0; j < qtd_dias; j++) {
									lab_day[i][j] = (rand() % 50) + 1;

									// Ainda não decidido se pode passar a capacidade maxima
									/*
									while (cap_labs[i] <= 0) {
									    lab_day[i][j] =  (rand() % 50) + 1;
									}
									*/
								}
							}

							// Media de desempenho de cada laboratorio:
							for (i = 0; i < num_labs; i++) {
								m_desemp[i] = ((double)rand() / RAND_MAX) * 10.0;
								while (m_desemp[i] < 0 || m_desemp[i] > 10) {
									m_desemp[i] = ((double)rand() / RAND_MAX) * 10.0;
								}
							}
							ehtrue = 1;
							break;
						case 3:
							printf("\nSaindo do programa...\n");
							break;
						default:
							printf("\nOpcao invalida! Tente novamente.\n");
					}
				} while (opcao2 != 3);

				break;
			case 2:
				// verificação se dados foram inseridos
				if (ehtrue == 0) {
					printf("Faça o cadastro dos dados primeiro.");
					break;
				}
				break;
			case 3:
				// verificação se dados foram inseridos
				if (ehtrue == 0) {
					printf("Faça o cadastro dos dados primeiro.");
					break;
				}
				break;
			case 4:
				// verificação se dados foram inseridos
				if (ehtrue == 0) {
					printf("Faça o cadastro dos dados primeiro.");
					break;
				}

				for (i = 0; i < num_labs; i++) {
					//=+ num_labs[i][0];
				}

				break;
			case 5:
				// verificação se dados foram inseridos
				// verificação se dados foram calculados
				if (ehtrue == 0) {
					printf("Faça o cadastro dos dados primeiro.");
					break;
				}
				break;
			case 6:
				// verificação se dados foram inseridos
				// verificação se dados foram calculados
				if (ehtrue == 0) {
					printf("Faça o cadastro dos dados primeiro.");
					break;
				}
				break;
			case 7:
				// verificação se dados foram inseridos
				// verificação se dados foram calculados
				if (ehtrue == 0) {
					printf("Faça o cadastro dos dados primeiro.");
					break;
				}
				break;
			case 8:
				// verificação se dados foram inseridos
				// verificação se dados foram calculados
				if (ehtrue == 0) {
					printf("Faça o cadastro dos dados primeiro.");
					break;
				}
				do {
					printf("\n--- MENU DE RELATÓRIO ---\n");
					printf("1. Relatório de um laboratório\n");
					printf("2. Relatório final\n");
					printf("3. Sair\n");
					printf("Escolha uma opcao: ");

					// Lê a escolha do usuário
					scanf("%d", &opcao3);
					switch (opcao3) {
						case 1:
							break;
						case 2:
							break;
						case 3:
							printf("\nSaindo do programa...\n");
							break;
						default:
							printf("\nOpcao invalida! Tente novamente.\n");
					}
				} while (opcao3 != 3);
				break;
			case 9:
				printf("\nSaindo do programa...\n");
				break;
			default:
				printf("\nOpcao invalida! Tente novamente.\n");
		}
	} while (opcao != 3);
	/*

	*/
	return 0;
}
