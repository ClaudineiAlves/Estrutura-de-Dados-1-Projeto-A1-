# Casos de teste · Monitoramento de Laboratórios

Entradas prontas em `entradas/`, uma por caso. Cada arquivo tem **um valor por linha**, na ordem em que o programa faz as perguntas.

## Como rodar

Na raiz do projeto:

```bash
gcc -Wall -Wextra -g testes/src/EstruturaDeDados_Final.c -o build/labs
./build/labs < testes/entradas/01_exemplo_enunciado.txt
```

Para rodar todos e guardar as saídas (o `timeout` impede que um laço infinito trave o terminal):

```bash
mkdir -p testes/saidas
for f in testes/entradas/*.txt; do
  timeout 2 ./build/labs < "$f" > "testes/saidas/$(basename "$f")"
  echo "$(basename "$f"): código de saída $?"   # 124 = travou e foi interrompido
done
```

> **Linhas em branco** nas entradas são o ENTER do "Pressione ENTER para continuar...", que aparece depois de cada opção do menu principal (menos a 0). Os submenus de cadastro e de relatório não pausam. Depois de um cadastro, o submenu volta sozinho para o menu principal, então a linha seguinte aos dados é o ENTER da pausa.

> As entradas seguem **o menu do enunciado** (1 cadastrar · 2 tabela · 3 indicadores · 4 lab mais ocupado · 5 classificação · 6 relatório · 0 encerrar; nos submenus, 0 = voltar). Se o menu mudar, atualizem os arquivos. Todo caso termina com `0`: se a saída acabar em "Fim da entrada. Encerrando..." em vez de "Encerrando o programa...", a sequência do arquivo saiu de ordem.

### Sequência usada nos casos 01 a 04

Depois do cadastro manual (`1` → `1` → dados → ENTER), o programa recebe:

```
2   tabela de ocupação
3   indicadores (calculados automaticamente após o cadastro)
4   laboratório mais ocupado → <dia>
5   classificação
6   relatório → 1 → <lab>   (relatório de um laboratório)
            → 2           (relatório final)
            → 0           (volta ao menu)
0   encerrar
```

---

## Resumo

Versão testada: `testes/src/EstruturaDeDados_Final.c` (04/10/2026). Todos os casos terminam pelo `0 - Encerrar`.

| # | Arquivo | O que testa | Situação na versão testada |
|---|---|---|---|
| 01 | `01_exemplo_enunciado.txt` | exemplo do enunciado (4 labs × 5 dias) | ✅ todos os valores conferem |
| 02 | `02_limite_minimo_1x1.txt` | limite mínimo: 1 lab × 1 dia | ✅ |
| 03 | `03_limite_maximo_20x30.txt` | limite máximo: 20 labs × 30 dias | ✅ inclusive as 11 menores ocupações |
| 04 | `04_empates.txt` | empates na maior e menor ocupação, no dia mais movimentado e no lab mais ocupado do dia | ✅ todos os empates listados |
| 05 | `05_invalidos_cadastro.txt` | valores numéricos fora do intervalo em todos os campos (inclui `nan`) | ✅ todos rejeitados |
| 06 | `06_capacidade_invalida.txt` | capacidade 0 e negativa | ✅ rejeitadas |
| 07 | `07_entrada_nao_numerica.txt` | letras no menu, no submenu e no cadastro | ✅ rejeitadas, sem travar |
| 08 | `08_menu_fora_de_ordem.txt` | pedir opções antes do cadastro; opções inexistentes | ✅ |
| 09 | `09_cadastro_aleatorio.txt` | cadastro aleatório (opção 1 → 2) | ✅ dados conferidos por `validar_dados` |
| 10 | `10_capacidade_total_atingida.txt` | dia de maior movimentação lotando todos os labs | ✅ "Atingiu a capacidade total!" |
| 11 | `11_fronteira_80_porcento.txt` | taxa de exatamente 80% e 50% na classificação (erro de arredondamento do `float`) | ✅ 80% → Excelente · 50% → Regular |

---

## Bugs encontrados (versão de 01/10, todos corrigidos)

**A. O menu principal encerra na opção errada.** O `do-while` termina com `while (opcao != 3)`. Resultado:
- escolher **3** (Tabela) **fecha o programa**;
- escolher **9** imprime "Saindo do programa..." e **volta ao menu**;
- se a entrada acabar depois do 9, o programa repete o menu sem parar (testado com `printf '9\n' | ./build/labs`).

**B. Capacidade 0 é aceita.** A validação está comentada ("ainda não decidido"). Com capacidade 0, a única ocupação aceita é 0, e a taxa de ocupação dividiria por zero.

**C. Letras no `scanf` causam laço infinito.** Quando `scanf("%d")` falha, a letra continua na entrada, e o `while` de validação lê a mesma coisa para sempre. Isso acontece em todo `scanf` do programa, inclusive no menu.

**D. O cadastro aleatório pode gerar ocupação maior que a capacidade.** A ocupação é sorteada de 1 a 50 (`rand() % 50 + 1`) independentemente de `cap_labs[i]`. Além disso, o sorteio de dias vai só até 20 (`rand() % 20 + 1`), nunca até 30.

---

## Casos e valores esperados

Preencham **Obtido** a cada versão. Os valores esperados foram calculados à mão a partir dos dados de entrada.

> **04/10 (versão Final):** nos casos 01 a 04, todos os valores obtidos foram iguais aos esperados.

### 01 · Exemplo do enunciado

Capacidades escolhidas por nós, porque o enunciado não informa: Lab 1 = 30, Lab 2 = 15, Lab 3 = 30, Lab 4 = 10. Desempenho: 7,5 · 6,0 · 8,0 · 5,5.

| Lab | Dia 1 | Dia 2 | Dia 3 | Dia 4 | Dia 5 |
|---|---|---|---|---|---|
| 1 | 18 | 22 | 16 | 25 | 20 |
| 2 | 10 | 8 | 13 | 9 | 11 |
| 3 | 25 | 28 | 30 | 26 | 29 |
| 4 | 5 | 7 | 4 | 8 | 6 |

| Indicador | Esperado | Obtido | OK? |
|---|---|---|---|
| Total diário | D1 = 58 · D2 = 65 · D3 = 61 · D4 = 68 · D5 = 66 | | |
| Média diária por lab | Lab 1 = 20,0 · Lab 2 = 10,0 · Lab 3 = 27,6 · Lab 4 = 6,0 | | |
| Maior ocupação | 30, Lab 3, Dia 3 (única) | | |
| Menor ocupação | 4, Lab 4, Dia 3 (única) | | |
| Dia de maior movimentação | Dia 4 (68 alunos) | | |
| Taxa média de ocupação | Lab 1 = 66,67% · Lab 2 = 66,67% · Lab 3 = 92,00% · Lab 4 = 60,00% | | |
| Lab mais ocupado no dia 4 | Lab 3 (26) | | |
| Dia 4 × capacidade total | 68 de 85 (80,00%): não atingiu, sobraram 17 vagas | | |
| Relatório do Lab 3 | cap. 30 · média 27,6 · maior 30 (D3) · menor 25 (D1) · taxa 92,00% · desempenho 8,0 · classificação: Excelente | | |
| Classificação | Lab 1 Regular · Lab 2 Regular · Lab 3 Excelente · Lab 4 Regular | | |

### 02 · Limite mínimo (1 × 1)

1 lab, capacidade 1, 1 dia, ocupação 1, desempenho 10.

| Indicador | Esperado | Obtido | OK? |
|---|---|---|---|
| Total diário | D1 = 1 | | |
| Média diária | Lab 1 = 1,0 | | |
| Maior e menor ocupação | as duas são 1, Lab 1, Dia 1 (a mesma célula) | | |
| Dia de maior movimentação | Dia 1 | | |
| Taxa média | 100,00% | | |
| Lab mais ocupado no dia 1 | Lab 1 | | |

### 03 · Limite máximo (20 × 30)

Dados gerados por fórmula. Capacidade do lab *i* = 29 + *i* (de 30 a 49). Ocupação do lab *i* no dia *j* = `((i−1)·7 + (j−1)·3) mod (capacidade + 1)`. Desempenho do lab *i* = `(i−1) mod 11`, que cobre os extremos 0 e 10.

| Indicador | Esperado | Obtido | OK? |
|---|---|---|---|
| Aceita 20 labs e 30 dias sem erro | sim | | |
| Maior ocupação | 49, Lab 20, Dia 23 (única) | | |
| Menor ocupação | 0, **11 ocorrências**: (L1,D1) (L2,D20) (L4,D28) (L5,D15) (L7,D24) (L8,D10) (L10,D20) (L11,D5) (L13,D16) (L16,D12) (L19,D8) | | |
| Dia de maior movimentação | Dia 6 (461 alunos) | | |
| Lab 1 | média 14,57 · taxa 48,56% · desempenho 0 | | |
| Lab 20 | média 24,83 · taxa 50,68% · desempenho 8 · maior 49 (D23) · menor 1 (D7) | | |
| Lab mais ocupado no dia 30 | Lab 13 (42) | | |

### 04 · Empates

2 labs com capacidade 10, 3 dias, desempenho 7 e 7.

| Lab | Dia 1 | Dia 2 | Dia 3 |
|---|---|---|---|
| 1 | 5 | 10 | 3 |
| 2 | 10 | 5 | 3 |

| Indicador | Esperado | Obtido | OK? |
|---|---|---|---|
| Total diário | D1 = 15 · D2 = 15 · D3 = 6 | | |
| Maior ocupação | 10, **duas vezes**: (Lab 2, Dia 1) e (Lab 1, Dia 2) | | |
| Menor ocupação | 3, **duas vezes**: (Lab 1, Dia 3) e (Lab 2, Dia 3) | | |
| Dia de maior movimentação | **empate**: Dia 1 e Dia 2 (15). Decisão do time: listar todos os dias empatados | | |
| Lab mais ocupado no dia 3 | **empate**: Lab 1 e Lab 2 (3). Decisão do time: listar todos os labs empatados | | |
| Média e taxa | os dois labs: média 6,0 · taxa 60,00% | | |
| Classificação | os dois labs devem ter a **mesma** classificação | | |

### 05 · Valores inválidos no cadastro

| Campo | Digitado (em ordem) | Esperado | Obtido (04/10) | OK? |
|---|---|---|---|---|
| Nº de labs | 0, 21, −1, **2** | rejeita os três primeiros | rejeitou | ✅ |
| Capacidades | **20, 20** | aceita | aceitou | ✅ |
| Nº de dias | 0, 31, **2** | rejeita 0 e 31 | rejeitou | ✅ |
| Ocupação Lab 1 | −1, 21, **10, 20** | rejeita −1 e 21 (capacidade 20) | rejeitou | ✅ |
| Ocupação Lab 2 | **5, 15** | aceita | aceitou | ✅ |
| Desempenho | −0,5, 10,5, nan, **7, 8** | rejeita −0,5, 10,5 e nan | rejeitou | ✅ |
| Tabela (opção 2) | Lab 1: 10 20 · Lab 2: 5 15 | | igual | ✅ |

### 06 · Capacidade inválida

1 lab. Capacidade digitada: 0, −5, **10**. Depois: 1 dia, ocupação 5, desempenho 6.

| Esperado | Obtido (04/10) | OK? |
|---|---|---|
| rejeita 0 e −5, aceita 10; tabela Lab 1: 5 | igual | ✅ |

### 07 · Entrada não numérica

`abc` no menu principal, `x` no submenu de cadastro, `abc` no nº de laboratórios e `xyz` na primeira nota, dentro de um cadastro válido de 2 labs × 2 dias.

| Esperado | Obtido (04/10) | OK? |
|---|---|---|
| "Opcao invalida!" no menu e no submenu (letras **não** podem cair no `0`, que encerra/volta) | igual | ✅ |
| avisa que é inválido, descarta a entrada e segue com o cadastro | igual; tabela Lab 1: 10 20 · Lab 2: 5 15 | ✅ |

### 08 · Menu fora de ordem

Sequência: 2, 3, 4, 5, 6 (tudo antes de cadastrar), depois 7, −1 e `abc` (inexistentes), depois 1 → 0 (volta sem cadastrar), 3 e 0.

| Opção | Esperado | Obtido (04/10) | OK? |
|---|---|---|---|
| 2 a 6 sem cadastro | aviso "Fazer o cadastro dos dados primeiro." e volta ao menu | igual | ✅ |
| 7, −1 e `abc` | "Opcao invalida!" | igual | ✅ |
| 1 → 0 e depois 3 | volta sem cadastrar; o 3 continua pedindo o cadastro | igual | ✅ |
| 0 | encerra | igual | ✅ |

### 09 · Cadastro aleatório

Depois de gerar, roda 2 (tabela), 3 (indicadores), 5 (classificação) e 6 → 2 (relatório final).

| Esperado | Obtido (04/10) | OK? |
|---|---|---|
| nº de labs entre 1 e 20 e nº de dias entre 1 e 30 | `rand() % LABS + 1` e `rand() % DAYS + 1` | ✅ |
| toda ocupação ≤ capacidade e desempenho entre 0 e 10 | conferido por `validar_dados` (mesmas regras do manual); 300 execuções sem nenhum dado inválido | ✅ |

### 10 · Capacidade total atingida

2 labs (capacidades 10 e 5), 2 dias. Lab 1: 3, 10 · Lab 2: 4, 5. Desempenho 7 e 8.

| Esperado | Obtido (04/10) | OK? |
|---|---|---|
| Dia de maior movimentação: Dia 2 (15); capacidade total 15 (100,00%); "Atingiu a capacidade total!" | igual | ✅ |

### 11 · Fronteira de 80% na classificação

2 labs, 5 dias. Lab 1: capacidade 9, ocupação 7, 7, 7, 7, 8 (média 7,2 → **80% exato**), desempenho 9. Lab 2: capacidade 10, ocupação 5 em todos os dias (média 5,0 → **50% exato**), desempenho 6.

O `float` guarda 7,2 ÷ 9 × 100 como 79,999992. Antes da correção, o Lab 1 aparecia com "80.00%" na tela mas era classificado como **Bom** (faixa média). A função `obter_classificacao` agora soma uma margem (`TOLERANCIA`, 0,001) antes de comparar.

| Esperado | Obtido (04/10) | OK? |
|---|---|---|
| Lab 1: 80,00% · Excelente (na classificação e no relatório do Lab 1) | igual | ✅ |
| Lab 2: 50,00% · Regular | igual | ✅ |

> Verificação exaustiva (fora dos arquivos de entrada): todas as combinações de capacidade 1–50, dias 1–30, soma possível e notas 0 / 4,99 / 5 / 7,99 / 8 / 10 (3.566.250 casos) foram comparadas com a classificação calculada só com inteiros. Nenhuma divergência. Sem a margem, havia 60 casos errados, todos na fronteira de 80%.

---

## Casos para acrescentar depois

| # | Ideia | Esperado | Obtido | OK? |
|---|---|---|---|---|
| 12 | dia fora do intervalo na opção 4 (0, ou maior que o nº de dias) | | | |
| 13 | lab fora do intervalo no relatório de um laboratório | | | |
| 14 | cadastrar duas vezes seguidas (o segundo cadastro substitui o primeiro?) | | | |
| 15 | ocupação 0 em todos os dias de um lab (taxa 0%, menor ocupação com empate) | | | |
| 16 | um lab de cada faixa da classificação definida com o professor | | | |
| 17 | compilar e rodar no **CodeBlocks** (exigência da entrega) | | | |
