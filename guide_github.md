# Como usar o GitHub Desktop neste projeto

Guia para os integrantes do grupo instalarem os programas, baixarem o projeto, trabalharem nele e enviarem as alterações, tudo sem usar o terminal. O código é escrito e compilado no **Code::Blocks** e enviado pelo **GitHub Desktop**.

- **Repositório:** https://github.com/ClaudineiAlves/Estrutura-de-Dados-1-Projeto-A1-
- **Projeto:** PED · 1º Projeto (A1): Monitoramento de Laboratórios

> 💡 Resumo do dia a dia: **Fetch origin / Pull origin antes de começar → programar no Code::Blocks e salvar → marcar os arquivos + Commit to main → Pull origin → Push origin.**

> ℹ️ O GitHub Desktop só tem interface em inglês. Este guia usa os nomes exatos dos botões e menus. No macOS, troque `Ctrl` por `Cmd` nos atalhos.

---

## 1. Preparação (só na primeira vez)

### 1.1 Criar uma conta e aceitar o convite
1. Crie uma conta em <https://github.com> se ainda não tiver.
2. Mande seu **nome de usuário do GitHub** para o dono do repositório.
3. Aceite o convite que chega por e-mail, ou abra <https://github.com/notifications>.
   **Sem aceitar o convite, você consegue baixar o projeto, mas não consegue enviar alterações.**

### 1.2 Instalar o GitHub Desktop
O GitHub Desktop já vem com o Git embutido. Não é preciso instalar o Git separado.

- **Windows** (10 ou mais novo, 64 bits): abra <https://desktop.github.com>, clique em **Download for Windows** e execute o instalador que foi para a pasta Downloads. Ele instala sozinho e abre o programa no final.
- **macOS** (12 ou mais novo): no mesmo site, clique em **Download for macOS**, abra o `.zip` baixado e arraste o **GitHub Desktop** para a pasta **Aplicativos**. Depois abra o programa por lá.
- **Linux:** não há versão oficial. Use a versão da comunidade ([shiftkey/desktop](https://github.com/shiftkey/desktop)), que funciona do mesmo jeito:
  - qualquer distribuição, via Flatpak: `flatpak install flathub io.github.shiftey.Desktop`;
  - Arch: pacote `github-desktop-bin` do AUR (`yay -S github-desktop-bin`);
  - Ubuntu/Debian e Fedora: baixe o `.deb` ou o `.rpm` na [página de releases](https://github.com/shiftkey/desktop/releases).

### 1.3 Entrar na sua conta
1. Na tela de boas-vindas, clique em **Sign in to GitHub.com**.
2. O navegador abre a página do GitHub. Entre na sua conta e clique em **Authorize desktop**. Se o navegador perguntar, permita abrir o GitHub Desktop.
3. De volta ao programa, na tela **Configure Git**, confira o **nome** e o **e-mail**. Use o **mesmo e-mail da sua conta do GitHub**, assim seus commits aparecem com o seu nome e a sua foto no repositório.
4. Clique em **Finish**.

Se você pulou algum passo, dá para refazer depois:
- conta: **File → Options… → Accounts** (no macOS, **GitHub Desktop → Settings… → Accounts**);
- nome e e-mail: **File → Options… → Git**.

### 1.4 Instalar o Code::Blocks
- **Windows:** em <https://www.codeblocks.org/downloads/binaries/>, baixe o **`codeblocks-25.03mingw-setup.exe`**. O instalador com **mingw** no nome já traz o compilador (GCC). Os outros vêm sem compilador, e aí o programa não compila.
- **Linux:** instale os pacotes `codeblocks` e `gcc` pelo gerenciador da sua distribuição (no Ubuntu/Debian: `sudo apt install codeblocks gcc`).
- **macOS:** a versão atual do Code::Blocks não funciona no Mac. Programe no editor que preferir e peça a um colega para testar a compilação no Code::Blocks antes da entrega.

Na primeira vez que o Code::Blocks abrir, ele procura os compiladores instalados. Selecione **GNU GCC Compiler**, clique em **Set as default** e depois em **OK**.

---

## 2. Baixar o projeto (clonar)

Faça isso **uma vez só**.

1. Abra **File → Clone repository…** (`Ctrl+Shift+O`).
2. Na aba **GitHub.com**, digite `Estrutura-de-Dados` na busca e selecione o repositório.
   Se ele não aparecer, use a aba **URL** e cole `https://github.com/ClaudineiAlves/Estrutura-de-Dados-1-Projeto-A1-`.
3. Em **Local path**, escolha onde o projeto vai ficar. Use uma pasta **fora** do OneDrive/Dropbox, para não dar conflito de sincronização.
4. Clique em **Clone**.

Para abrir a pasta clonada no computador, use **Repository → Show in Explorer** (`Ctrl+Shift+F`; no macOS, *Show in Finder*). Para trabalhar nela com o Code::Blocks, siga a seção 3.

---

## 3. Organizar a pasta com o Code::Blocks

O Code::Blocks é onde vocês escrevem e compilam o código, e o GitHub Desktop é onde vocês enviam. Os dois trabalham na **mesma pasta**: a que você clonou no passo 2. O GitHub Desktop só enxerga o que está dentro dela. **Um arquivo salvo em outro lugar**, como a pasta padrão do Code::Blocks, **nunca chega ao GitHub.**

### 3.1 Onde cada coisa fica
```
Estrutura-de-Dados-1-Projeto-A1-/   ← a pasta clonada
├── src/           → o arquivo .c da entrega: é aqui que vocês programam
├── testes/        → entradas e casos de teste
├── relatorio/     → relatório em PDF da entrega
├── .vscode/       → configuração de quem usa o VSCodium (não mexa)
├── README.md
├── guide_github.md
└── .gitignore     → lista do que o Git deve ignorar
```

A entrega exige **um único `.c`**, com todo o código nele e sem `.h` separados. Por isso não é preciso criar um projeto do Code::Blocks (`.cbp`): o arquivo compila sozinho, e o Code::Blocks abre o arquivo direto.

### 3.2 Abrir, criar e compilar
- **Abrir um arquivo:** **File → Open…** (`Ctrl+O`), entre na pasta clonada, depois em `src/`, e escolha o `.c`.
- **Criar um arquivo novo:** **File → New → Empty file** (`Ctrl+Shift+N`) e salve (`Ctrl+S`) dentro de `src/`, com a extensão `.c`. Use nomes sem espaço e sem acento, por exemplo `monitoramento_labs.c`.
- **Compilar e executar:** **Build → Build and run** (`F9`). O Code::Blocks cria o executável (`.exe`) e o arquivo objeto (`.o`) ao lado do `.c`, dentro de `src/`. Eles não vão para o GitHub (veja o passo 3.3).

### 3.3 O que vai e o que não vai para o GitHub

| Arquivo | Vai para o GitHub? |
|---|---|
| Os `.c` de `src/` | Sim |
| Os arquivos de `testes/` e o PDF de `relatorio/` | Sim |
| `.exe` e `.o`, gerados ao compilar | Não. O `.gitignore` já os ignora |
| `bin/`, `obj/`, `.layout` e `.depend`, que aparecem se alguém criar um projeto do Code::Blocks | Não. O `.gitignore` já os ignora |
| `.vscode/` | Não mexa |

Arquivos ignorados nem aparecem na aba **Changes**. Se aparecer ali algum outro arquivo gerado pelo Code::Blocks, deixe a caixinha dele desmarcada e avise o grupo.

> No **Linux**, o executável sai sem extensão (por exemplo, `src/monitoramento_labs`) e aparece na aba **Changes**. Deixe-o desmarcado.

### 3.4 Usando os dois programas juntos
- **Salve antes de ir ao GitHub Desktop.** Ele só vê o que está salvo no disco. No Code::Blocks, **File → Save everything** (`Ctrl+Shift+S`) salva tudo. Aba com `*` no nome ainda tem alteração não salva.
- **Faça o commit antes do Pull.** Se o Pull trouxer mudanças num arquivo aberto, o Code::Blocks mostra a janela **Reload file?**, avisando que o arquivo *is modified outside the IDE*. Clique em **Yes** para ver a versão nova. Alterações que ainda não estavam salvas se perdem nessa hora.
- **Para renomear, mover ou apagar arquivos,** feche o arquivo no Code::Blocks (`Ctrl+W`) e faça a mudança na pasta pelo Explorador de Arquivos (**Repository → Show in Explorer**, no GitHub Desktop). A mudança aparece na aba **Changes** e vai no próximo commit, como qualquer outra.

---

## 4. Trabalho do dia a dia

### Onde fica cada coisa na tela
- **Barra de cima:** *Current repository* (qual projeto está aberto), *Current branch* (deixe em `main`) e o botão de sincronizar, que muda de nome conforme a situação: **Fetch origin**, **Pull origin** ou **Push origin**.
- **Coluna da esquerda:** a aba **Changes** lista os arquivos que você alterou; a aba **History** mostra os commits já feitos.
- **Canto de baixo, à esquerda:** os campos **Summary** e **Description** e o botão **Commit to main**.
- **Área da direita:** as diferenças do arquivo selecionado. Verde é linha nova e vermelho é linha removida.

### 4.1 Antes de começar: atualizar
Sempre traga as alterações dos colegas antes de mexer em qualquer coisa:
1. Clique em **Fetch origin** (`Ctrl+Shift+T`). Ele só consulta o GitHub, sem mexer nos seus arquivos.
2. Se o botão virar **Pull origin** com uma setinha para baixo e um número, clique nele (`Ctrl+Shift+P`). Isso baixa o que os colegas enviaram.

### 4.2 Depois de trabalhar: fazer o commit
Um **commit** é um ponto salvo no histórico do projeto, com uma mensagem dizendo o que mudou.
1. Salve tudo no Code::Blocks (`Ctrl+Shift+S`) e vá para o GitHub Desktop, na aba **Changes** (`Ctrl+1`).
2. Confira a lista. Só vai para o commit o que estiver com a **caixinha marcada**. Clique em cada arquivo para revisar as diferenças à direita.
3. Em **Summary**, escreva uma mensagem curta dizendo **o que** mudou, por exemplo `Implementa o cadastro dos laboratórios`. O campo **Description** é opcional.
4. Clique em **Commit to main** (`Ctrl+Enter`).

O commit fica só no seu computador até você enviá-lo (passo 4.3).

> 👥 Programaram juntos no mesmo computador? Clique no ícone de pessoa ao lado do **Summary** (**Add co-authors**) e adicione os colegas. O commit aparece no GitHub com o nome de todos.

### 4.3 Enviar para o GitHub
1. Se aparecer **Pull origin**, clique nele primeiro para pegar o que os colegas enviaram nesse meio-tempo.
2. Clique em **Push origin** (`Ctrl+P`).

Pronto: o commit está no GitHub. Confira em **Repository → View on GitHub** (`Ctrl+Shift+G`).

Se você tentar enviar e algum colega tiver enviado algo antes, o programa avisa que há commits novos no GitHub e oferece o botão **Fetch**. Clique nele, depois em **Pull origin** e, por último, em **Push origin**.

### 4.4 Ver o histórico
A aba **History** (`Ctrl+2`) lista todos os commits: quem fez, quando e o que mudou em cada arquivo.

### 4.5 Boas práticas no grupo
- **Commits pequenos e frequentes**, com mensagem clara ("Adiciona menu principal", e não "update" ou "asdf").
- **Combinem quem mexe em quê.** Duas pessoas editando o mesmo trecho do mesmo arquivo ao mesmo tempo é o que causa conflito.
- **Trabalhem direto na `main`.** Não criem branches sem combinar com o grupo.
- **Nunca use Force push.** Se essa opção aparecer, não clique: ela apaga o trabalho dos colegas.
- Não envie executáveis nem arquivos de compilação (veja o passo 3.3).
- Antes de dar push, confira se o código **compila no Code::Blocks** (`F9`).

---

## 5. Problemas comuns

### O repositório não aparece na aba GitHub.com
Você ainda não aceitou o convite (passo 1.1) ou entrou com outra conta (**File → Options… → Accounts**). Enquanto isso, dá para clonar pela aba **URL**, mas não dá para enviar.

### Erro de permissão ao dar push
O convite de colaborador ainda não foi aceito (passo 1.1) ou o programa está com outra conta.

### Salvei o arquivo, mas ele não aparece na aba Changes
Ele foi salvo fora da pasta clonada. No Code::Blocks, use **File → Save file as…** e salve dentro de `src/` da pasta clonada (seção 3).

### Conflito ao dar Pull
Você e um colega mudaram as mesmas linhas. O programa abre a janela **Resolve conflicts before Merge** com a lista dos arquivos em conflito. Para cada arquivo, escolha uma saída:
- **Juntar as duas versões:** abra o arquivo no Code::Blocks (**File → Open…**) e procure `<<<<<<<` com `Ctrl+F`. O Git marca o trecho em conflito assim:
  ```
  <<<<<<< HEAD
  (a sua versão)
  =======
  (a versão do colega)
  >>>>>>> ...
  ```
  Deixe o trecho como ele deve ficar, apague as marcações `<<<<<<<`, `=======` e `>>>>>>>`, salve e confira se o código compila (`F9`).
- **Ficar com uma versão inteira:** no menu do arquivo, escolha **Use the modified file from main** (a sua) ou **Use the modified file from origin/main** (a do colega).

Quando todos os arquivos estiverem resolvidos, clique em **Continue merge** e depois em **Push origin**. Para desistir e voltar ao estado de antes do Pull, clique em **Abort merge**.

Na dúvida, **pare e chame o grupo** antes de apagar o código de alguém.

### Quero descartar o que fiz num arquivo e voltar ao último commit
Feche o arquivo no Code::Blocks. Na aba **Changes**, clique com o botão direito no arquivo e escolha **Discard changes…**. ⚠️ As alterações não commitadas desse arquivo somem do projeto. O GitHub Desktop manda uma cópia para a Lixeira, mas não conte com isso.

### Fiz um commit errado
- **Ainda não dei push:** clique em **Undo**, logo abaixo do botão de commit, ou, na aba **History**, clique com o botão direito no commit e escolha **Undo commit**. As alterações voltam para a aba **Changes**.
- **Já dei push:** na aba **History**, clique com o botão direito no commit e escolha **Revert changes in commit**. Isso cria um commit novo que desfaz o errado. Depois dê **Push origin**.

### Apareceu um arquivo que não deveria ir para o repositório
Desmarque a caixinha dele antes do commit. Se ele nunca deve ser enviado, clique com o botão direito e escolha **Ignore file (add to .gitignore)**, e avise o grupo.

### Meus commits aparecem sem o meu nome ou a minha foto no GitHub
O e-mail configurado não é o da sua conta. Corrija em **File → Options… → Git** (passo 1.3).

---

## 6. Colinha

| Quero... | Onde | Atalho |
|---|---|---|
| Baixar o projeto (1ª vez) | GitHub Desktop: **File → Clone repository…** | `Ctrl+Shift+O` |
| Ver se os colegas enviaram algo | GitHub Desktop: **Fetch origin** | `Ctrl+Shift+T` |
| Baixar o que os colegas enviaram | GitHub Desktop: **Pull origin** | `Ctrl+Shift+P` |
| Abrir um `.c` | Code::Blocks: **File → Open…** | `Ctrl+O` |
| Compilar e executar | Code::Blocks: **Build → Build and run** | `F9` |
| Salvar tudo antes do commit | Code::Blocks: **File → Save everything** | `Ctrl+Shift+S` |
| Ver o que mudou | GitHub Desktop: aba **Changes** | `Ctrl+1` |
| Ver o histórico | GitHub Desktop: aba **History** | `Ctrl+2` |
| Salvar um ponto no histórico | GitHub Desktop: marcar os arquivos + **Summary** + **Commit to main** | `Ctrl+Enter` |
| Enviar para o GitHub | GitHub Desktop: **Push origin** | `Ctrl+P` |
| Abrir a pasta do projeto | GitHub Desktop: **Repository → Show in Explorer** | `Ctrl+Shift+F` |
| Abrir o repositório no site | GitHub Desktop: **Repository → View on GitHub** | `Ctrl+Shift+G` |

Quem já usa o Git pelo terminal ou pelo Source Control do VS Code pode continuar assim. Tudo funciona no mesmo repositório.


Quando o git pull reclamar de "local changes would be overwritten"

1. Veja o que está pendente:
git status
git diff
2. Escolha um caminho:

   A) Suas mudanças importam e você quer mantê-las:
git add .
git commit -m "descreva o que fez"
git pull --rebase
   Se der conflito, o Git marca os trechos com <<<<<<< e >>>>>>>. Edite o arquivo deixando a versão certa e depois rode:
git add <arquivo>
git rebase --continue

   B) Você não tem certeza se as mudanças importam (foi o que eu fiz):
git stash push -m "backup"
git pull --ff-only
git stash pop        # tenta reaplicar; se der conflito, resolva como no caminho A

   C) Suas mudanças não importam (testes, rascunho):
git restore <arquivo>
git pull --ff-only
   ⚠️ Isso apaga suas alterações sem volta.

Dica rápida

Para saber se o GitHub tem algo novo antes de puxar:
git fetch
git status          # mostra "behind by N commits"
git log --oneline main..origin/main   # lista o que chegou

Se quiser, posso deixar o Git configurado para usar rebase no pull por padrão (git config pull.rebase true). Fica mais fácil de seguir o caminho A.
