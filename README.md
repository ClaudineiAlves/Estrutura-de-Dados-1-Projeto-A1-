# PED · 1º Projeto (A1): Monitoramento de Laboratórios

> ⚠️ **Conteúdo avaliado.** Programação e Estrutura de Dados (prática), 2026.
> Enunciado: [`../PRIMEIRO PROJETO-1.pdf`](../PRIMEIRO%20PROJETO-1.pdf)
> Entrega: **04/10/2026 até 23h59**, pelo Canvas. Times de 3 a 4 alunos, cadastrados em Pessoas → ATIV_01.

## Estrutura

```
projeto_1_labs/
├── .vscode/
│   ├── tasks.json              → compilar / compilar e executar (gcc)
│   ├── launch.json             → depurar com gdb (F5)
│   └── c_cpp_properties.json   → IntelliSense apontando para o gcc do sistema
├── src/          → código-fonte .c
├── testes/       → entradas e casos de teste
├── relatorio/    → relatório em PDF da entrega
├── build/        → executáveis gerados (criada ao compilar; ignorada pelo git)
└── .gitignore
```

### `src/`
Código do programa. A entrega exige **um único arquivo `.c` compatível com o CodeBlocks**, então todo o código deve ficar nesse arquivo, sem `.h` separados. Antes de entregar, teste a compilação no CodeBlocks.

### `testes/`
Entradas usadas para conferir o programa, por exemplo arquivos `.txt` para colar no terminal ou usar com `./build/<programa> < testes/<caso>.txt`. Casos que vale cobrir:
- o exemplo do enunciado (4 laboratórios × 5 dias);
- os limites (1 laboratório × 1 dia e 20 laboratórios × 30 dias);
- empates na maior e na menor ocupação;
- entradas inválidas;
- opções do menu fora de ordem, como pedir indicadores antes do cadastro.

### `relatorio/`
Relatório em **PDF** exigido pelo enunciado:
- capa com nome e RA em ordem alfabética;
- introdução;
- desenvolvimento, com as dificuldades e soluções, as estruturas usadas e a decisão sobre a classificação tomada com o professor;
- referências (sites com data de acesso).

## Como usar no VSCodium

```bash
codium 2_second_semester/data_structures/projetos/projeto_1_labs
```

| Ação | Atalho |
|---|---|
| Compilar o `.c` aberto | `Ctrl+Shift+B` |
| Compilar e executar (terminal interativo, `scanf` funciona) | Terminal → Run Task → *Compilar e executar arquivo atual* |
| Depurar com breakpoints | `F5` |

O programa é compilado com `gcc -Wall -Wextra -g`. Trate os avisos (*warnings*) como erros a corrigir.

## Entrega (checklist)
- [ ] `.c` único, compilando no CodeBlocks
- [ ] PDF do relatório
- [ ] Os dois arquivos enviados no Canvas até 04/10 às 23h59

## Planejamento
As tarefas estão no Notion, no Projects Tracker, no projeto **Estrutura de Dados — 1º Projeto (A1)**.
