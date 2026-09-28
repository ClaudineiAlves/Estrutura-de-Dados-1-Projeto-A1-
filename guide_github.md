# Como usar o GitHub Desktop neste projeto

Guia para os integrantes do grupo instalarem o GitHub Desktop, baixarem o projeto, trabalharem nele e enviarem as alterações, tudo sem usar o terminal.

- **Repositório:** https://github.com/ClaudineiAlves/Estrutura-de-Dados-1-Projeto-A1-
- **Projeto:** PED · 1º Projeto (A1): Monitoramento de Laboratórios

> 💡 Resumo do dia a dia: **Fetch origin / Pull origin antes de começar → trabalhar → marcar os arquivos + Commit to main → Pull origin → Push origin.**

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

### 1.4 Escolher o editor
Em **File → Options… → Integrations**, no campo **External editor**, escolha o **Visual Studio Code** ou o **VSCodium**. Assim o botão de abrir o projeto no editor já abre o programa certo.

---

## 2. Baixar o projeto (clonar)

Faça isso **uma vez só**.

1. Abra **File → Clone repository…** (`Ctrl+Shift+O`).
2. Na aba **GitHub.com**, digite `Estrutura-de-Dados` na busca e selecione o repositório.
   Se ele não aparecer, use a aba **URL** e cole `https://github.com/ClaudineiAlves/Estrutura-de-Dados-1-Projeto-A1-`.
3. Em **Local path**, escolha onde o projeto vai ficar. Use uma pasta **fora** do OneDrive/Dropbox, para não dar conflito de sincronização.
4. Clique em **Clone**.

Para abrir o projeto:
- no editor: **Repository → Open in Visual Studio Code** (`Ctrl+Shift+A`);
- na pasta do computador: **Repository → Show in Explorer** (`Ctrl+Shift+F`; no macOS, *Show in Finder*).

O `README.md` explica a estrutura das pastas e como compilar.

> ⚠️ No **Windows**, as configurações em `.vscode/` usam o caminho `/usr/bin/gcc`, que é do Linux. Para compilar no Windows, use o **CodeBlocks** ou ajuste o caminho do seu compilador (MinGW) nos arquivos da pasta `.vscode/`. **Não envie esse ajuste para o repositório**, porque ele quebraria a configuração dos outros integrantes: na hora do commit, deixe **desmarcados** os arquivos da pasta `.vscode/` (veja o passo 3.2).

---

## 3. Trabalho do dia a dia

### Onde fica cada coisa na tela
- **Barra de cima:** *Current repository* (qual projeto está aberto), *Current branch* (deixe em `main`) e o botão de sincronizar, que muda de nome conforme a situação: **Fetch origin**, **Pull origin** ou **Push origin**.
- **Coluna da esquerda:** a aba **Changes** lista os arquivos que você alterou; a aba **History** mostra os commits já feitos.
- **Canto de baixo, à esquerda:** os campos **Summary** e **Description** e o botão **Commit to main**.
- **Área da direita:** as diferenças do arquivo selecionado. Verde é linha nova e vermelho é linha removida.

### 3.1 Antes de começar: atualizar
Sempre traga as alterações dos colegas antes de mexer em qualquer coisa:
1. Clique em **Fetch origin** (`Ctrl+Shift+T`). Ele só consulta o GitHub, sem mexer nos seus arquivos.
2. Se o botão virar **Pull origin** com uma setinha para baixo e um número, clique nele (`Ctrl+Shift+P`). Isso baixa o que os colegas enviaram.

### 3.2 Depois de trabalhar: fazer o commit
Um **commit** é um ponto salvo no histórico do projeto, com uma mensagem dizendo o que mudou.
1. Salve os arquivos no editor e volte ao GitHub Desktop, na aba **Changes** (`Ctrl+1`).
2. Confira a lista. Só vai para o commit o que estiver com a **caixinha marcada**. Clique em cada arquivo para revisar as diferenças à direita.
3. Em **Summary**, escreva uma mensagem curta dizendo **o que** mudou, por exemplo `Implementa o cadastro dos laboratórios`. O campo **Description** é opcional.
4. Clique em **Commit to main** (`Ctrl+Enter`).

O commit fica só no seu computador até você enviá-lo (passo 3.3).

> 👥 Programaram juntos no mesmo computador? Clique no ícone de pessoa ao lado do **Summary** (**Add co-authors**) e adicione os colegas. O commit aparece no GitHub com o nome de todos.

### 3.3 Enviar para o GitHub
1. Se aparecer **Pull origin**, clique nele primeiro para pegar o que os colegas enviaram nesse meio-tempo.
2. Clique em **Push origin** (`Ctrl+P`).

Pronto: o commit está no GitHub. Confira em **Repository → View on GitHub** (`Ctrl+Shift+G`).

Se você tentar enviar e algum colega tiver enviado algo antes, o programa avisa que há commits novos no GitHub e oferece o botão **Fetch**. Clique nele, depois em **Pull origin** e, por último, em **Push origin**.

### 3.4 Ver o histórico
A aba **History** (`Ctrl+2`) lista todos os commits: quem fez, quando e o que mudou em cada arquivo.

### 3.5 Boas práticas no grupo
- **Commits pequenos e frequentes**, com mensagem clara ("Adiciona menu principal", e não "update" ou "asdf").
- **Combinem quem mexe em quê.** Duas pessoas editando o mesmo trecho do mesmo arquivo ao mesmo tempo é o que causa conflito.
- **Trabalhem direto na `main`.** Não criem branches sem combinar com o grupo.
- **Nunca use Force push.** Se essa opção aparecer, não clique: ela apaga o trabalho dos colegas.
- Não envie executáveis nem arquivos de compilação. A pasta `build/` já é ignorada pelo `.gitignore`.
- Antes de dar push, confira se o código **compila**.

---

## 4. Problemas comuns

### O repositório não aparece na aba GitHub.com
Você ainda não aceitou o convite (passo 1.1) ou entrou com outra conta (**File → Options… → Accounts**). Enquanto isso, dá para clonar pela aba **URL**, mas não dá para enviar.

### Erro de permissão ao dar push
O convite de colaborador ainda não foi aceito (passo 1.1) ou o programa está com outra conta.

### Conflito ao dar Pull
Você e um colega mudaram as mesmas linhas. O programa abre a janela **Resolve conflicts before Merge** com a lista dos arquivos em conflito. Para cada arquivo, escolha uma saída:
- **Juntar as duas versões:** clique em **Open in Visual Studio Code**. O Git marca o trecho em conflito assim:
  ```
  <<<<<<< HEAD
  (a sua versão)
  =======
  (a versão do colega)
  >>>>>>> ...
  ```
  O editor mostra os botões *Accept Current Change*, *Accept Incoming Change* e *Accept Both Changes*. Deixe o trecho como ele deve ficar, apague as marcações `<<<<<<<`, `=======` e `>>>>>>>`, salve e confira se o código compila.
- **Ficar com uma versão inteira:** no menu do arquivo, escolha **Use the modified file from main** (a sua) ou **Use the modified file from origin/main** (a do colega).

Quando todos os arquivos estiverem resolvidos, clique em **Continue merge** e depois em **Push origin**. Para desistir e voltar ao estado de antes do Pull, clique em **Abort merge**.

Na dúvida, **pare e chame o grupo** antes de apagar o código de alguém.

### Quero descartar o que fiz num arquivo e voltar ao último commit
Na aba **Changes**, clique com o botão direito no arquivo e escolha **Discard changes…**. ⚠️ As alterações não commitadas desse arquivo somem do projeto. O GitHub Desktop manda uma cópia para a Lixeira, mas não conte com isso.

### Fiz um commit errado
- **Ainda não dei push:** clique em **Undo**, logo abaixo do botão de commit, ou, na aba **History**, clique com o botão direito no commit e escolha **Undo commit**. As alterações voltam para a aba **Changes**.
- **Já dei push:** na aba **History**, clique com o botão direito no commit e escolha **Revert changes in commit**. Isso cria um commit novo que desfaz o errado. Depois dê **Push origin**.

### Apareceu um arquivo que não deveria ir para o repositório
Desmarque a caixinha dele antes do commit. Se ele nunca deve ser enviado, clique com o botão direito e escolha **Ignore file (add to .gitignore)**, e avise o grupo.

### Meus commits aparecem sem o meu nome ou a minha foto no GitHub
O e-mail configurado não é o da sua conta. Corrija em **File → Options… → Git** (passo 1.3).

---

## 5. Colinha

| Quero... | No GitHub Desktop | Atalho |
|---|---|---|
| Baixar o projeto (1ª vez) | **File → Clone repository…** | `Ctrl+Shift+O` |
| Ver se os colegas enviaram algo | **Fetch origin** | `Ctrl+Shift+T` |
| Baixar o que os colegas enviaram | **Pull origin** | `Ctrl+Shift+P` |
| Ver o que mudou | aba **Changes** | `Ctrl+1` |
| Ver o histórico | aba **History** | `Ctrl+2` |
| Salvar um ponto no histórico | marcar os arquivos + **Summary** + **Commit to main** | `Ctrl+Enter` |
| Enviar para o GitHub | **Push origin** | `Ctrl+P` |
| Abrir o projeto no editor | **Repository → Open in Visual Studio Code** | `Ctrl+Shift+A` |
| Abrir a pasta do projeto | **Repository → Show in Explorer** | `Ctrl+Shift+F` |
| Abrir o repositório no site | **Repository → View on GitHub** | `Ctrl+Shift+G` |

Quem já usa o Git pelo terminal ou pelo Source Control do VS Code pode continuar assim. Tudo funciona no mesmo repositório.
