# Como usar o GitHub neste projeto

Guia para os integrantes do grupo baixarem o projeto, trabalharem nele e enviarem as alterações.

- **Repositório:** https://github.com/ClaudineiAlves/Estrutura-de-Dados-1-Projeto-A1-
- **Projeto:** PED · 1º Projeto (A1): Monitoramento de Laboratórios

> 💡 Resumo do dia a dia: **`git pull` antes de começar → trabalhar → `git add` + `git commit` → `git pull` → `git push`.**

---

## 1. Preparação (só na primeira vez)

### 1.1 Instalar o Git
- **Windows:** baixe em <https://git-scm.com/download/win> e instale com as opções padrão. Depois use o programa **Git Bash** para rodar os comandos deste guia.
- **Linux:** `sudo apt install git` (Ubuntu/Debian), `sudo pacman -S git` (Arch) ou `sudo dnf install git` (Fedora).
- **macOS:** rode `git --version` no Terminal. Se o Git não estiver instalado, o sistema oferece a instalação.

### 1.2 Criar uma conta e aceitar o convite
1. Crie uma conta em <https://github.com> se ainda não tiver.
2. Mande seu **nome de usuário do GitHub** para o dono do repositório.
3. Aceite o convite que chega por e-mail, ou abra <https://github.com/notifications>.
   **Sem aceitar o convite, você consegue baixar o projeto, mas não consegue enviar alterações.**

### 1.3 Dizer ao Git quem você é
Use o **mesmo e-mail da sua conta do GitHub**. Assim seus commits aparecem com o seu nome no repositório.
```bash
git config --global user.name "Seu Nome"
git config --global user.email "seu-email-do-github@exemplo.com"
```

### 1.4 Configurar o acesso (escolha UMA opção)

**Opção A: HTTPS (mais simples)**
Na primeira vez que você der `git push`, o Git pede login:
- **Windows:** abre uma janela do navegador para entrar no GitHub. É só autorizar.
- **Linux/macOS:** no lugar da senha, cole um **token**. Para criar um: GitHub → *Settings* → *Developer settings* → *Personal access tokens* → *Tokens (classic)* → *Generate new token*, marcando a permissão `repo`. Guarde o token, porque ele só aparece uma vez.

**Opção B: SSH (não pede senha depois de configurado)**
```bash
ssh-keygen -t ed25519 -C "seu-email-do-github@exemplo.com"   # aperte Enter em tudo
cat ~/.ssh/id_ed25519.pub                                    # copie o texto que aparecer
```
Cole o texto em GitHub → *Settings* → *SSH and GPG keys* → *New SSH key*. Para testar, rode `ssh -T git@github.com`. A resposta deve começar com "Hi <seu-usuário>!".

---

## 2. Baixar o projeto (clonar)

Faça isso **uma vez só**. Escolha uma pasta **fora** do OneDrive/Dropbox, para não dar conflito de sincronização.

```bash
cd ~/Documentos                 # ou a pasta que preferir
git clone https://github.com/ClaudineiAlves/Estrutura-de-Dados-1-Projeto-A1-.git           # HTTPS
# ou: git clone git@github.com:ClaudineiAlves/Estrutura-de-Dados-1-Projeto-A1-.git         # SSH
cd Estrutura-de-Dados-1-Projeto-A1-
```

Abra o projeto no VSCodium ou no VS Code (**Arquivo → Abrir Pasta**, ou `codium .` no terminal). O `README.md` explica a estrutura das pastas e como compilar.

> ⚠️ No **Windows**, as configurações em `.vscode/` usam o caminho `/usr/bin/gcc`, que é do Linux. Para compilar no Windows, use o **CodeBlocks** ou ajuste o caminho do seu compilador (MinGW) nos arquivos da pasta `.vscode/`. **Não envie esse ajuste para o repositório**, porque ele quebraria a configuração dos outros integrantes.

---

## 3. Trabalho do dia a dia

### 3.1 Antes de começar: atualizar
Sempre traga as alterações dos colegas antes de mexer em qualquer coisa:
```bash
git pull
```

### 3.2 Depois de trabalhar: salvar e enviar
```bash
git status                         # ver o que mudou
git add src/meu_arquivo.c          # escolher o que vai no commit (ou: git add . para tudo)
git commit -m "Implementa validação do cadastro"   # mensagem curta dizendo O QUE mudou
git pull                           # pegar o que os colegas enviaram nesse meio-tempo
git push                           # enviar para o GitHub
```

**Pelo editor, sem terminal:** no VSCodium/VS Code, abra o ícone **Source Control** (`Ctrl+Shift+G`), clique em **+** nos arquivos, escreva a mensagem, clique em **Commit** e depois em **Sync Changes**. O Sync faz o pull e o push juntos.

### 3.3 Boas práticas no grupo
- **Commits pequenos e frequentes**, com mensagem clara ("Adiciona menu principal", e não "update" ou "asdf").
- **Combinem quem mexe em quê.** Duas pessoas editando o mesmo trecho do mesmo arquivo ao mesmo tempo é o que causa conflito.
- **Nunca use `git push --force`.** Ele apaga o trabalho dos colegas.
- Não envie executáveis nem arquivos de compilação. A pasta `build/` já é ignorada pelo `.gitignore`.
- Antes de dar push, confira se o código **compila**.

---

## 4. Problemas comuns

### "rejected ... fetch first" ao dar `git push`
Algum colega enviou algo antes de você. Rode:
```bash
git pull
git push
```

### Conflito ("CONFLICT ... Merge conflict in ...")
Você e um colega mudaram as mesmas linhas. O Git marca o trecho assim:
```
<<<<<<< HEAD
(a sua versão)
=======
(a versão do colega)
>>>>>>> ...
```
1. Abra o arquivo. O VSCodium mostra os botões *Accept Current*, *Accept Incoming* e *Accept Both*.
2. Deixe o trecho como ele deve ficar, apague as marcações `<<<<<<<`, `=======` e `>>>>>>>` e confira se o código compila.
3. Finalize:
```bash
git add <arquivo>
git commit -m "Resolve conflito em <arquivo>"
git push
```
Na dúvida, **pare e chame o grupo** antes de apagar o código de alguém.

### Quero descartar o que fiz num arquivo e voltar ao último commit
```bash
git restore <arquivo>      # ⚠️ apaga as alterações não commitadas desse arquivo
```

### "Permission denied" / "403" ao dar push
Você ainda não aceitou o convite de colaborador (passo 1.2) ou está logado com outra conta.

### "Please tell me who you are"
Faltou o passo 1.3.

---

## 5. Colinha

| Quero... | Comando |
|---|---|
| Baixar o projeto (1ª vez) | `git clone <url>` |
| Atualizar com o que os colegas enviaram | `git pull` |
| Ver o que mudou | `git status` |
| Ver o histórico | `git log --oneline` |
| Preparar arquivos para o commit | `git add <arquivo>` ou `git add .` |
| Salvar um ponto no histórico | `git commit -m "mensagem"` |
| Enviar para o GitHub | `git push` |
