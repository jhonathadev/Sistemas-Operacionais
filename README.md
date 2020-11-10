# Interpretador VJShell

>Status: :o2: Incompleto (Infelizmente não conseguimos finalizar dentro do prazo!)

**Repositório GIT:** [*Interpretador VJShell*](https://github.com/renizia/Trabalho-1-Sistemas-Operacionais)

**Equipe:**

Jhonatha Cordeiro Gomes - 5984

Viviane Renizia Mendes Silva - 5209

### Seções:

:small_blue_diamond:[*VJShell*](#VJShell)

:small_blue_diamond:[*Funcionamento*](#Funcionamento)

:small_blue_diamond:[*Bugs*](#Bugs)

### VJShell
VJShell é um projeto desenvolvido para a disciplina de Sistemas Operacionais - SIN351. O objetivo visa o desenvolvimento de um interpretador Shell em linguagem C, que seja capaz de receber, iterativamente, entradas dos usuários (comandos), processá-los (caso ele
exista) e exibir a saída na tela de Prompt. 

**Casos de erros:**

- Números de argumentos;

- Comando inexistente ou impossível de ser executado (caso de erro);

- A quantidade de caracteres por linha de comando é limitada a 512;

- Entrada vazia como comando não deve ser considerada;

- Espaço extra entre comandos deverá ser desconsiderado.

### Funcionamento
O código fonte se encontra no arquivo shell.c e há um arquivo makefile para compilar o código.

:small_blue_diamond:Primeira compilação: Comando make no terminal Linux para que o executável será gerado.

:small_blue_diamond:Já compilou anteriormente: Utilize o comando make clean seguido do comando make.

:small_blue_diamond:Já compilou: Utilize o comando ./file.

**Tela de operação do VJShell**

<img src="https://github.com/vivianerenizia/Trabalho-1-Sistemas-Operacionais/blob/master/VJShell.jpeg" height="400" width="700">

### Bugs 

Não conseguimos implementar a execução de mais de um comando seguido, separado pela virgula ou pelo pipe, como exemplificado na imagem abaixo:

<img src="https://github.com/vivianerenizia/Trabalho-1-Sistemas-Operacionais/blob/master/VJShellBug.jpeg" height="400" width="700">

> **Exemplos de ocorrência de erros:** ls -l , cat file / ls -l , cat file , grep foo file2 

> Em considerações finais, gostaríamos de agradecer ao autor do [*Tutorial - Write a Shell in C*](https://brennan.io/2015/01/16/write-a-shell-in-c/), Stephen Brennan! Thank you, sir! :shipit:
