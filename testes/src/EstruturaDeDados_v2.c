#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LABS 20
#define DAYS 30
#define BLOCO 15
#define TOLERANCIA 0.001f

// Versao sem funcoes: todo o programa fica dentro da main.
//
// Toda leitura segue o mesmo padrao:
//   1. a variavel recebe um valor invalido antes do scanf;
//   2. o scanf tenta ler (se o usuario digitar letras, a variavel continua invalida);
//   3. o resto da linha e descartado com getchar; se a entrada acabar (EOF), o programa encerra;
//   4. o while repete a pergunta enquanto o valor estiver fora da faixa.

int main() {
	int num_labs = 0;
	int qtd_dias = 0;

	int cap_labs[LABS];
	int lab_day[LABS][DAYS];

	double m_desemp[LABS];

	// Indicadores, calculados logo apos cada cadastro
	int total_dia[DAYS];
	float media_diaria[LABS];
	float taxa_media[LABS];
	int maior_lab[LABS]; // maior ocupacao de cada laboratorio (relatorios)
	int menor_lab[LABS]; // menor ocupacao de cada laboratorio (relatorios)
	const char *classificacao[LABS];

	int opcao, opcao2, opcao3;

	int ehtrue = 0;
	int cadastrou;
	int valido;

	int i, j, c;
	int inicio, fim;
	int maior, menor, maior_total, capacidade_total;
	int dia, lab;
	int primeiro;
	float taxa;

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
		while ((c = getchar()) != '\n' && c != EOF)
			;
		if (c == EOF) {
			printf("\nFim da entrada. Encerrando...\n");
			return 0;
		}

		if (opcao >= 2 && opcao <= 6 && ehtrue == 0) {
			printf("\nFazer o cadastro dos dados primeiro.\n");
		} else {
			switch (opcao) {
				// ==================== 1 - CADASTRAR DADOS ====================
				case 1:
					cadastrou = 0;

					do {
						printf("\n--- MENU DE CADASTRO ---\n");
						printf("1 - Cadastrar Dados Manualmente\n");
						printf("2 - Cadastrar Dados Aleatoriamente (para testes)\n");
						printf("0 - Voltar\n");
						printf("Escolha uma opcao: ");

						opcao2 = -1;
						scanf("%d", &opcao2);
						while ((c = getchar()) != '\n' && c != EOF)
							;
						if (c == EOF) {
							printf("\nFim da entrada. Encerrando...\n");
							return 0;
						}

						switch (opcao2) {
							// ---------- Cadastro manual ----------
							case 1:
								// Numero de laboratorios
								printf("\nInsira o numero de laboratorios (1 a %d): ", LABS);
								num_labs = 0;
								scanf("%d", &num_labs);
								while ((c = getchar()) != '\n' && c != EOF) //limpa a saida do teclado a cada scanf
									;
								if (c == EOF) {
									printf("\nFim da entrada. Encerrando...\n");
									return 0;
								}

								while (num_labs < 1 || num_labs > LABS) {
									printf("Valor invalido! Tente novamente: ");
									num_labs = 0;
									scanf("%d", &num_labs);
									while ((c = getchar()) != '\n' && c != EOF)
										;
									if (c == EOF) {
										printf("\nFim da entrada. Encerrando...\n");
										return 0;
									}
								}

								// Capacidade de cada laboratorio
								printf("\nInsira a capacidade de cada laboratorio:\n");
								for (i = 0; i < num_labs; i++) {
									printf("Laboratorio %d: ", i + 1);
									cap_labs[i] = 0;
									scanf("%d", &cap_labs[i]);
									while ((c = getchar()) != '\n' && c != EOF)
										;
									if (c == EOF) {
										printf("\nFim da entrada. Encerrando...\n");
										return 0;
									}

									while (cap_labs[i] <= 0) {
										printf("Capacidade invalida! Deve ser maior que 0: ");
										cap_labs[i] = 0;
										scanf("%d", &cap_labs[i]);
										while ((c = getchar()) != '\n' && c != EOF)
											;
										if (c == EOF) {
											printf("\nFim da entrada. Encerrando...\n");
											return 0;
										}
									}
								}

								// Quantidade de dias
								printf("\nInsira a quantidade de dias que deseja acompanhar (1 a "
								       "%d): ",
								       DAYS);
								qtd_dias = 0;
								scanf("%d", &qtd_dias);
								while ((c = getchar()) != '\n' && c != EOF)
									;
								if (c == EOF) {
									printf("\nFim da entrada. Encerrando...\n");
									return 0;
								}

								while (qtd_dias < 1 || qtd_dias > DAYS) {
									printf("Valor invalido! Tente novamente: ");
									qtd_dias = 0;
									scanf("%d", &qtd_dias);
									while ((c = getchar()) != '\n' && c != EOF)
										;
									if (c == EOF) {
										printf("\nFim da entrada. Encerrando...\n");
										return 0;
									}
								}

								// Ocupacao de cada laboratorio em cada dia
								printf("\nInsira o numero de ocupacao de cada laboratorio em cada "
								       "dia:\n");
								for (i = 0; i < num_labs; i++) {
									for (j = 0; j < qtd_dias; j++) {
										printf("Lab %d, dia %d: ", i + 1, j + 1);
										lab_day[i][j] = -1;
										scanf("%d", &lab_day[i][j]);
										while ((c = getchar()) != '\n' && c != EOF)
											;
										if (c == EOF) {
											printf("\nFim da entrada. Encerrando...\n");
											return 0;
										}

										while (lab_day[i][j] < 0 || lab_day[i][j] > cap_labs[i]) {
											printf("Invalido! O numero inserido deve estar entre 0 "
											       "e %d: ",
											       cap_labs[i]);
											lab_day[i][j] = -1;
											scanf("%d", &lab_day[i][j]);
											while ((c = getchar()) != '\n' && c != EOF)
												;
											if (c == EOF) {
												printf("\nFim da entrada. Encerrando...\n");
												return 0;
											}
										}
									}
								}

								// Media de desempenho de cada laboratorio
								printf("\nInforme a media de desempenho de cada laboratorio (0 a "
								       "10):\n");
								for (i = 0; i < num_labs; i++) {
									printf("Laboratorio %d: ", i + 1);
									m_desemp[i] = -1;
									scanf("%lf", &m_desemp[i]);
									while ((c = getchar()) != '\n' && c != EOF)
										;
									if (c == EOF) {
										printf("\nFim da entrada. Encerrando...\n");
										return 0;
									}

									// Condicao negada para recusar tambem "nan", que falha em
									// qualquer comparacao.
									while (!(m_desemp[i] >= 0 && m_desemp[i] <= 10)) {
										printf("Nota invalida! Deve estar entre 0 e 10: ");
										m_desemp[i] = -1;
										scanf("%lf", &m_desemp[i]);
										while ((c = getchar()) != '\n' && c != EOF)
											;
										if (c == EOF) {
											printf("\nFim da entrada. Encerrando...\n");
											return 0;
										}
									}
								}

								cadastrou = 1;
								opcao2 = 0;
								break;

							// ---------- Cadastro aleatorio ----------
							case 2:
								// Gera de novo enquanto algum valor nao passar na validacao
								do {
									num_labs = (rand() % LABS) + 1;

									for (i = 0; i < num_labs; i++) {
										cap_labs[i] = (rand() % 50) + 1;
									}

									qtd_dias = (rand() % DAYS) + 1;

									for (i = 0; i < num_labs; i++) {
										for (j = 0; j < qtd_dias; j++) {
											lab_day[i][j] = rand() % (cap_labs[i] + 1);
										}
									}

									for (i = 0; i < num_labs; i++) {
										m_desemp[i] = ((double)rand() / RAND_MAX) * 10.0;
									}

									// Confere com as mesmas regras do cadastro manual
									valido = 1;

									if (num_labs < 1 || num_labs > LABS) {
										printf("Numero de laboratorios invalido: %d\n", num_labs);
										valido = 0;
									} else if (qtd_dias < 1 || qtd_dias > DAYS) {
										printf("Quantidade de dias invalida: %d\n", qtd_dias);
										valido = 0;
									}

									for (i = 0; i < num_labs && valido; i++) {
										if (cap_labs[i] <= 0) {
											printf("Capacidade invalida no Lab %d: %d\n", i + 1,
											       cap_labs[i]);
											valido = 0;
										}

										for (j = 0; j < qtd_dias && valido; j++) {
											if (lab_day[i][j] < 0 || lab_day[i][j] > cap_labs[i]) {
												printf("Ocupacao invalida no Lab %d, dia %d: %d\n",
												       i + 1, j + 1, lab_day[i][j]);
												valido = 0;
											}
										}

										if (valido && !(m_desemp[i] >= 0 && m_desemp[i] <= 10)) {
											printf("Nota invalida no Lab %d: %.2f\n", i + 1,
											       m_desemp[i]);
											valido = 0;
										}
									}
								} while (!valido);

								printf(
								    "\nDados aleatorios cadastrados: %d laboratorios, %d dias.\n",
								    num_labs, qtd_dias);
								cadastrou = 1;
								opcao2 = 0;
								break;

							case 0:
								printf("\nVoltando para o menu.\n");
								break;

							default:
								printf("\nOpcao invalida! Tente novamente.\n");
						}
					} while (opcao2 != 0);

					// ---------- Calculo dos indicadores (apos cada cadastro) ----------
					if (cadastrou == 1) {
						ehtrue = 1;

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

						// Maior e menor ocupacao de cada laboratorio
						for (i = 0; i < num_labs; i++) {
							maior_lab[i] = lab_day[i][0];
							menor_lab[i] = lab_day[i][0];

							for (j = 1; j < qtd_dias; j++) {
								if (lab_day[i][j] > maior_lab[i]) {
									maior_lab[i] = lab_day[i][j];
								}
								if (lab_day[i][j] < menor_lab[i]) {
									menor_lab[i] = lab_day[i][j];
								}
							}
						}

						// Classificacao (taxa media x desempenho)
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
						for (i = 0; i < num_labs; i++) {
							// O float pode guardar 80% exato como 79.999992 (ex.: media 7.2 /
							// capacidade 9). A margem corrige isso sem mudar nenhum outro caso:
							// taxas possiveis diferentes distam pelo menos 100 / (50 * 30) = 0.067
							// ponto percentual entre si.
							taxa = taxa_media[i] + TOLERANCIA;

							if (taxa >= 80.0f && m_desemp[i] >= 8.0) {
								classificacao[i] = "Excelente";
							} else if (taxa >= 80.0f && m_desemp[i] >= 5.0) {
								classificacao[i] = "Muito bom";
							} else if (taxa >= 80.0f && m_desemp[i] < 5.0) {
								classificacao[i] = "Atencao";
							} else if (taxa >= 50.0f && m_desemp[i] >= 8.0) {
								classificacao[i] = "Bom";
							} else if (taxa >= 50.0f && m_desemp[i] >= 5.0) {
								classificacao[i] = "Regular";
							} else if (taxa >= 50.0f && m_desemp[i] < 5.0) {
								classificacao[i] = "Atencao";
							} else if (taxa < 50.0f && m_desemp[i] >= 8.0) {
								classificacao[i] = "Bom desempenho / baixa utilizacao";
							} else if (taxa < 50.0f && m_desemp[i] >= 5.0) {
								classificacao[i] = "Subutilizado";
							} else {
								classificacao[i] = "Critico";
							}
						}
					}
					break;

				// ==================== 2 - TABELA DE OCUPACAO ====================
				case 2:
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
					break;

				// ==================== 3 - INDICADORES ====================
				case 3:
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

					// Maior e menor ocupacao de toda a matriz
					printf("\n--- Maior e menor ocupacao ---");

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

					printf("Capacidade total dos laboratorios: %d alunos (%.2f%% ocupada)\n",
					       capacidade_total, (float)maior_total / capacidade_total * 100.0f);
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
					break;

				// ==================== 4 - LABORATORIO MAIS OCUPADO ====================
				case 4:
					printf("\nDigite o dia que deseja consultar (1 a %d): ", qtd_dias);
					dia = 0;
					scanf("%d", &dia);
					while ((c = getchar()) != '\n' && c != EOF)
						;
					if (c == EOF) {
						printf("\nFim da entrada. Encerrando...\n");
						return 0;
					}

					while (dia < 1 || dia > qtd_dias) {
						printf("Dia invalido! Digite um valor entre 1 e %d: ", qtd_dias);
						dia = 0;
						scanf("%d", &dia);
						while ((c = getchar()) != '\n' && c != EOF)
							;
						if (c == EOF) {
							printf("\nFim da entrada. Encerrando...\n");
							return 0;
						}
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
					break;

				// ==================== 5 - CLASSIFICACAO ====================
				case 5:
					printf("\n===== CLASSIFICACAO DOS LABORATORIOS =====\n");
					printf("\nLab | Taxa media | Desempenho | Classificacao\n");

					for (i = 0; i < num_labs; i++) {
						printf("%3d | %10.2f%% | %10.2f | %s\n", i + 1, taxa_media[i], m_desemp[i],
						       classificacao[i]);
					}
					break;

				// ==================== 6 - RELATORIO ====================
				case 6:
					do {
						printf("\n--- MENU DE RELATORIO ---\n");
						printf("1 - Relatorio de um laboratorio\n");
						printf("2 - Relatorio final\n");
						printf("0 - Voltar\n");
						printf("Escolha uma opcao: ");

						opcao3 = -1;
						scanf("%d", &opcao3);
						while ((c = getchar()) != '\n' && c != EOF)
							;
						if (c == EOF) {
							printf("\nFim da entrada. Encerrando...\n");
							return 0;
						}

						// Intervalo de laboratorios que o relatorio vai imprimir
						inicio = 0;
						fim = 0;

						switch (opcao3) {
							case 1:
								printf("\nDigite o laboratorio que deseja consultar (1 a %d): ",
								       num_labs);
								lab = 0;
								scanf("%d", &lab);
								while ((c = getchar()) != '\n' && c != EOF)
									;
								if (c == EOF) {
									printf("\nFim da entrada. Encerrando...\n");
									return 0;
								}

								while (lab < 1 || lab > num_labs) {
									printf("Laboratorio invalido! Digite um valor entre 1 e %d: ",
									       num_labs);
									lab = 0;
									scanf("%d", &lab);
									while ((c = getchar()) != '\n' && c != EOF)
										;
									if (c == EOF) {
										printf("\nFim da entrada. Encerrando...\n");
										return 0;
									}
								}

								printf("\n===== RELATORIO DO LABORATORIO =====\n");
								inicio = lab - 1;
								fim = lab;
								break;

							case 2:
								printf("\n========== RELATORIO FINAL ==========\n");
								printf("Laboratorios: %d | Dias: %d\n", num_labs, qtd_dias);

								// Tabela de ocupacao (mesmo codigo da opcao 2 do menu principal)
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

								inicio = 0;
								fim = num_labs;
								break;

							case 0:
								printf("\nVoltando para o menu.\n");
								break;

							default:
								printf("\nOpcao invalida! Tente novamente.\n");
						}

						// Bloco de informacoes de cada laboratorio do intervalo
						for (lab = inicio; lab < fim; lab++) {
							if (opcao3 == 2) {
								printf("\n-------------------------------------\n");
							}

							printf("Laboratorio: %d\n", lab + 1);
							printf("Capacidade: %d alunos\n", cap_labs[lab]);
							printf("Media de ocupacao: %.2f alunos\n", media_diaria[lab]);

							printf("Maior ocupacao: %d alunos (Dia ", maior_lab[lab]);
							primeiro = 1;
							for (j = 0; j < qtd_dias; j++) {
								if (lab_day[lab][j] == maior_lab[lab]) {
									if (!primeiro) {
										printf(", ");
									}
									printf("%d", j + 1);
									primeiro = 0;
								}
							}
							printf(")\n");

							printf("Menor ocupacao: %d alunos (Dia ", menor_lab[lab]);
							primeiro = 1;
							for (j = 0; j < qtd_dias; j++) {
								if (lab_day[lab][j] == menor_lab[lab]) {
									if (!primeiro) {
										printf(", ");
									}
									printf("%d", j + 1);
									primeiro = 0;
								}
							}
							printf(")\n");

							printf("Taxa media de ocupacao: %.2f%%\n", taxa_media[lab]);
							printf("Desempenho medio: %.2f\n", m_desemp[lab]);
							printf("Classificacao: %s\n", classificacao[lab]);
						}

						if (opcao3 == 2) {
							printf("\n=====================================\n");
						}
					} while (opcao3 != 0);
					break;

				case 0:
					printf("\nEncerrando o programa...\n");
					break;

				default:
					printf("\nOpcao invalida! Tente novamente.\n");
			}
		}

		// Pausa ate o ENTER (menos ao encerrar)
		if (opcao != 0) {
			printf("\nPressione ENTER para continuar...");
			while ((c = getchar()) != '\n' && c != EOF)
				;
			if (c == EOF) {
				printf("\nFim da entrada. Encerrando...\n");
				return 0;
			}
		}
	} while (opcao != 0);
	return 0;
}
