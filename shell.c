// Universidade Federal de Viçosa - Campus Rio Paranáiba (UFV-CRP)
// Trabaho prático 1 da disciplina Sistemas Operacionais - SIN 351 
// Desenvolvido por Jhonatha Cordeiro (5984) e Viviane Renizia (5209)
// Professor: Rodrigo Moreira 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define TRUE 1  
#define tokDelim " ," // string de delimitados para a função srtok
#define numAuxiliarCommands 3 // variavel de controle do numero de comandos auxialiares

int cdFunction(char **args);
int helpFunction();
int quitFunction();
int auxiliarFunctions(int option, char **args);
int execCommands(char **args);
int execute(char **args);
char *readLine();
char **splitLine(char *line);
void intro();
void init(); 

char *auxiliarStrings[] = { "cd", "help", "quit" }; // variavel global contendo os comandos auxiliares

int auxiliarFunctions(int option, char **args) {
  switch(option) {
    case 0:
      cdFunction(args); // chama a função que muda de diretorio
      break;
    case 1:
      helpFunction(); // chama a função de ajuda
      break;
    case 2:
      quitFunction(); // chama a função de encerrar o programa
      break; 
  }
}

int cdFunction(char **args) {
  if (args[1] == NULL) { // verifica se a função cd possui um diretorio a ser acessado
    fprintf(stderr, "VJSHELL: digite o nome do diretório que deseja acessar.\n");
  } else {
    if (chdir(args[1]) != 0) { // trata se a função chdir foi executada corretamente
      perror("VJSHELL");
    }
  }
  return 1;
}

int helpFunction() {
  int i;
  printf("VJSHELL v1.0\n");
  printf("Powered by Jhonatha and Viviane\n");
  printf("------------------------------------\n");
  printf("Comandos auxiliares disponiveis: ");
  for (i = 0; i < numAuxiliarCommands; i++) {
    printf("%s", auxiliarStrings[i]);
    if(!(i == (numAuxiliarCommands-1))) { // "gambiarra" para não imprimir uma virgula no final da string
      printf(", ");
    }
  }
  printf("\nUse o comando > man < para obter informações sobre outros programas do linux.\n");
  printf("Exemplo: man sudo\n");
  printf("------------------------------------\n");
  return 1;
}

int quitFunction() {
  printf("Até logo :)\n");
  return 0;
}

int execCommands(char **args) {
  pid_t pid;
  int status; // variavel de controle de execução do programa 
  pid = fork(); // realiza uma chamada de sistema para poder executar o processo filho
  if (pid == 0) {
    // Processo filho
    if (execvp(args[0], args) == -1) { // verifica e executa se a função exevp executou corretamente
      perror("VJSHELL");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) { // verificação se o fork funcionou corretamente
    perror("VJSHELL");
  } else {
    //processo pai
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status)); // trata possiveis erros de execução no processo filho
  }
  return 1;
}

int execute(char **args) {
  int i;
  // nenhum comando digitado
  if (args[0] == NULL) {
    return 1;
  }
  // verifica se o comando digitado é algum dos auxiliares(exit, cd, help)
  for (i = 0; i < numAuxiliarCommands; i++) {
    if (strcmp(args[0], auxiliarStrings[i]) == 0) {
      return auxiliarFunctions(i, args); // caso o comando digitado seja algum comando auxiliar, essa função determina e executa o selecionado
    }
  }
  return execCommands(args); // função que de fato executa o comando caso não seja algum dos auxiliares
}

char *readLine() {
  char *buffer = malloc(512 * sizeof(char));
  int i = 0, caracter;
  if (buffer == NULL) {
    printf("Erro na alocação de memória\n");
    exit(EXIT_FAILURE);
  }
  while(TRUE) {
    caracter = getchar();
    if (caracter == EOF) {
      exit(EXIT_SUCCESS);
    } else if (caracter == '\n') {
      buffer[i] = '\0';
      return buffer;
    } else {
      buffer[i] = caracter;
    }
    i++;
  }
}

char **splitLine(char *line) {
  int i = 0;
  char **string = malloc(512 * sizeof(char*));
  char *subString;
  if (string == NULL) {
    printf("Erro na alocação de memória\n");
    exit(EXIT_FAILURE);
  }
  subString = strtok(line, tokDelim);
  while (subString != NULL) {
    string[i] = subString;
    subString = strtok(NULL, tokDelim);
    i++;
  }
  string[i] = NULL;
  return string;
}

void intro() {
  printf(" __        __  __________  __________  __\n");
  printf("|  |      |  ||___    ___||   _______||  |        ________  __      __\n");
  printf(" |  |    |  |     |  |    |  |_______ |  |______ |  ____  ||  |    |  |\n");
  printf("  |  |  |  |   _  |  |    |________  ||   ___   || |____|_||  |    |  |\n");
  printf("   |  ||  |   | |_|  |     _______|  ||  |   |  || |______ |  |___ |  |___\n");
  printf("    |____|    |______|    |__________||__|   |__||________||______||______|\n");
  printf("\nBem vindo(a) %s, o horário atual é: %s\n", getenv("USER"), __TIME__);
}

void init() {
  char **args;
  char *line; 
  int state;
  intro();
  do {
    printf("VJShell -> ");
    line = readLine(); // função p/ ler a string digitada
    args = splitLine(line); // função que dividi a string por espaço e virgula
    state = execute(args); // função que trata da execução das linhas de codigo
    free(line); //libera memoria alocada
    free(args); //libera memoria alocada
  } while (state);
}

int main() {
  init();
  return 0;
}
