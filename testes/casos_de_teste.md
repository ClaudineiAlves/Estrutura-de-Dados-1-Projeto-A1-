# Casos de teste · Monitoramento de Laboratórios

Entradas prontas em `entradas/`, uma por caso. Cada arquivo tem **um valor por linha**, na ordem em que o programa faz as perguntas.

## Como rodar

Na raiz do projeto:

```bash
gcc -Wall -Wextra -g src/<arquivo>.c -o build/labs
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

> ⚠️ As entradas seguem **a numeração do menu atual** (1 cadastrar · 2 visualizar · 3 tabela · 4 calcular · 5 exibir indicadores · 6 lab mais ocupado · 7 classificação · 8 relatório · 9 sair). Se o menu mudar (o enunciado usa **0 para encerrar**), atualizem os arquivos.

### Sequência usada nos casos 01 a 04

Depois do cadastro manual (`1` → `1` → dados → `3` para sair do submenu), o programa recebe:

```
2   visualizar dados
3   tabela de ocupação
4   calcular indicadores
5   exibir indicadores
6   laboratório mais ocupado → <dia>
7   classificação
8   relatório → 1 → <lab>   (relatório de um laboratório)
            → 2           (relatório final)
            → 3           (sai do submenu)
9   sair
```

---

## Resumo

Versão testada: commit `f0f18e5` (01/10/2026). Só o cadastro está implementado nessa versão.

| # | Arquivo | O que testa | Situação na versão testada |
|---|---|---|---|
| 01 | `01_exemplo_enunciado.txt` | exemplo do enunciado (4 labs × 5 dias) | ⚠️ cadastra, mas **encerra ao escolher 3** (ver bug A) |
| 02 | `02_limite_minimo_1x1.txt` | limite mínimo: 1 lab × 1 dia | ⚠️ igual ao 01 |
| 03 | `03_limite_maximo_20x30.txt` | limite máximo: 20 labs × 30 dias | ⚠️ igual ao 01 |
| 04 | `04_empates.txt` | empates na maior e menor ocupação, no dia mais movimentado e no lab mais ocupado do dia | ⚠️ igual ao 01 |
| 05 | `05_invalidos_cadastro.txt` | valores numéricos fora do intervalo em todos os campos | ✅ todos rejeitados |
| 06 | `06_capacidade_invalida.txt` | capacidade 0 e negativa | ❌ **trava** (ver bug B) |
| 07 | `07_entrada_nao_numerica.txt` | letras no lugar de número | ❌ **trava** (ver bug C) |
| 08 | `08_menu_fora_de_ordem.txt` | pedir opções antes do cadastro; opções inexistentes | ⚠️ encerra ao escolher 3 (bug A) |
| 09 | `09_cadastro_aleatorio.txt` | cadastro aleatório (opção 1 → 2) | ⚠️ ocupação pode passar da capacidade (ver bug D) |

---

## Bugs encontrados

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

### 01 · Exemplo do enunciado

Capacidades escolhidas por nós, porque o enunciado não informa: Lab 1 = 30, Lab 2 = 15, Lab 3 = 30, Lab 4 = 10. Desempenho: 7,5 · 6,0 · 8,0 · 5,5.

| Lab | Dia 1 | Dia 2 | Dia 3 | Dia 4 | Dia 5 |
|---|---|---|---|---|---|
| 1 | 18 | 22 | 15 | 25 | 20 |
| 2 | 10 | 8 | 12 | 9 | 11 |
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
| Relatório do Lab 3 | cap. 30 · média 27,6 · maior 30 (D3) · menor 25 (D1) · taxa 92,00% · desempenho 8,0 · classificação: ___ | | |
| Classificação | (critério definido com o professor) | | |

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
| Dia de maior movimentação | **empate**: Dia 1 e Dia 2 (15). O enunciado não diz o que fazer; registrem a decisão do time | | |
| Lab mais ocupado no dia 3 | **empate**: Lab 1 e Lab 2 (3). Registrem a decisão do time | | |
| Média e taxa | os dois labs: média 6,0 · taxa 60,00% | | |
| Classificação | os dois labs devem ter a **mesma** classificação | | |

### 05 · Valores inválidos no cadastro

| Campo | Digitado (em ordem) | Esperado | Obtido (01/10) | OK? |
|---|---|---|---|---|
| Nº de labs | 0, 21, −1, **2** | rejeita os três primeiros | rejeitou | ✅ |
| Capacidades | **20, 20** | aceita | aceitou | ✅ |
| Nº de dias | 0, 31, **2** | rejeita 0 e 31 | rejeitou | ✅ |
| Ocupação Lab 1 | −1, 21, **10, 20** | rejeita −1 e 21 (capacidade 20) | rejeitou | ✅ |
| Ocupação Lab 2 | **5, 15** | aceita | aceitou | ✅ |
| Desempenho | −0,5, 10,5, **7, 8** | rejeita −0,5 e 10,5 | rejeitou | ✅ |
| Tabela final | Lab 1: 10 20 · Lab 2: 5 15 | | não exibida (opção 3 fecha o programa, bug A) | ⚠️ |

### 06 · Capacidade inválida

1 lab. Capacidade digitada: 0, −5, **10**. Depois: 1 dia, ocupação 5, desempenho 6.

| Esperado | Obtido (01/10) | OK? |
|---|---|---|
| rejeita 0 e −5, aceita 10; tabela Lab 1: 5 | aceita 0. A partir daí as respostas saem fora de ordem (o −5 é lido como nº de dias) e o programa fica preso em "deve estar entre 0 e 0" | ❌ bug B |

### 07 · Entrada não numérica

`abc` digitado como número de laboratórios, seguido de um cadastro válido de 2 labs × 2 dias.

| Esperado | Obtido (01/10) | OK? |
|---|---|---|
| avisa que é inválido, descarta `abc` e segue com o cadastro | repete "Valor invalido! Tente novamente:" sem parar | ❌ bug C |

### 08 · Menu fora de ordem

Sequência: 2, 3, 4, 5, 6, 7, 8 (tudo antes de cadastrar), depois 10 e −1 (inexistentes), depois 1 → 3 e 9.

| Opção | Esperado | Obtido (01/10) | OK? |
|---|---|---|---|
| 2 a 8 sem cadastro | aviso "cadastre os dados primeiro" e volta ao menu | 2 não faz nada; **3 fecha o programa** | ⚠️ bug A |
| 4 e 5 antes de calcular | (se o time separar "calcular" de "exibir") aviso "calcule os indicadores primeiro" | | |
| 10 e −1 | "Opcao invalida!" | | |
| 9 | encerra | | |

### 09 · Cadastro aleatório

| Esperado | Obtido (01/10) | OK? |
|---|---|---|
| nº de labs entre 1 e 20 | ✅ pelo código (`rand() % 20 + 1`) | ✅ |
| nº de dias entre 1 e 30 | só sorteia de 1 a 20 | ⚠️ bug D |
| toda ocupação ≤ capacidade do lab | pode passar (ocupação sorteada de 1 a 50, sem olhar a capacidade) | ❌ bug D |
| desempenho entre 0 e 10 | ✅ | ✅ |

Para conferir na prática: rodem `09` várias vezes depois que a opção 2 (visualizar) estiver pronta.

---

## Casos para acrescentar depois

| # | Ideia | Esperado | Obtido | OK? |
|---|---|---|---|---|
| 10 | dia fora do intervalo na opção 6 (0, ou maior que o nº de dias) | | | |
| 11 | lab fora do intervalo no relatório de um laboratório | | | |
| 12 | cadastrar duas vezes seguidas (o segundo cadastro substitui o primeiro?) | | | |
| 13 | ocupação 0 em todos os dias de um lab (taxa 0%, menor ocupação com empate) | | | |
| 14 | um lab de cada faixa da classificação definida com o professor | | | |
| 15 | compilar e rodar no **CodeBlocks** (exigência da entrega) | | | |
