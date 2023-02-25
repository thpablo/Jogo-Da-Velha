#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Funcao Resetar Tabuleiro e deixar lacunas.
void resetaTabuleiro(char tabuleiro[3][3]) {
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      tabuleiro[i][j] = ' ';
}
//Funcao mostrar Enunciado Jogo Da Velha
void mostraEnunciado(char enunciado[], int tam) {

  printf("\t\t\t");
  for (int i = 0; i < tam; i++) {
    printf("_");
  }
  printf("%s", enunciado);
  printf("\t\t\t");
  for (int i = 0; i < tam; i++) {
    printf("_");
  }
  printf("\n\n");
}

//Funcao Verifica Condicoes para o Fim de Jogo.
int verificaFimJogo(char tabuleiro[3][3], char caracterDaVez, int numeroJogadas){
  int quantAcertos = 0;
  //Verifica se houve velha na DIAGONAL
  for(int i = 0; i < 3; i++){
    if(tabuleiro[i][i] == caracterDaVez)
      quantAcertos++;
    else{
      quantAcertos = 0;
      break;
    }    
    if(quantAcertos == 3)
      return 1; //Deu Velha.
  }
  //Verifica se houve velha na DIAGONAL SECUNDARIA.
  for(int i = 0; i < 3; i++){ 
    if(tabuleiro[i][2-i] == caracterDaVez)
      quantAcertos++;
    else{
      quantAcertos = 0;
      break;
    }    
    if(quantAcertos == 3)
      return 1; //Deu Velha.
  }
  //Verifica se houve velha na HORIZONTAL.
  for(int i = 0; i < 3; i++){ 
    for(int j = 0; j < 3; j++){
      if(tabuleiro[i][j] == caracterDaVez)
        quantAcertos++; 
      if(quantAcertos == 3)
        return 1; //Deu Velha.
    }
    quantAcertos = 0;
  }
  //Verifica se houve velha na VERTICAL.
  for(int i = 0; i < 3; i++){ 
    for(int j = 0; j < 3; j++){
      if(tabuleiro[j][i] == caracterDaVez)
        quantAcertos++; 
      if(quantAcertos == 3)
        return 1; //Deu Velha.
    }
    quantAcertos = 0;
  }
  //Verifica se houve número limites de jogada (9)
  if(numeroJogadas == 9)
    return 2; //Retorna 2 para uma mensagem de Empate.
  
  return 0; //Continua Jogo
}

//Funcao Verifica se Entradas de X ou O são válidas.
int verificaEntrada(char *entrada1, char *entrada2) {
  printf("Escolha seu símbolo:\n");
  printf("JOGADOR 1 - Escolha X ou O: ");
  *entrada1 = getchar();
  while(getchar() != '\n'); //Retira buffer e outras caracteres além da   primeira.
  *entrada1 = toupper(*entrada1);

  system("clear||cls"); //Limpar terminal Tanto para Linux/Windows
  
  if (*entrada1 == 'X' )
    *entrada2 = 'O';
  else if(*entrada1 == 'O'){
    *entrada2 = 'X';
  }
  //Entradas Válidas:
  if ((*entrada1 == 'X' || *entrada1 == 'O'))
    return 0;
  //Entradas Inválidas:
  else
    printf("\n! Entradas Inválidas! Insira os os símbolos de maneira correta !\n\n");
  return 1;
}

//Função Printar Tabuleiro.
void mostraTabuleiro(char tabuleiro[3][3]) {
  char a[] = " A   B   C";
  printf("\t%s\n", a);
  for (int i = 0; i < 3; i++) {
    printf("\n%d\t ", i + 1);
    for (int j = 0; j < 3; j++) {
      printf("%c", tabuleiro[i][j]);
      if (j < 2)
        printf(" | ");
    }
    printf("\n\t");
    for (int j = 0; j < 3 && i < 2; j++) {
      printf("___ ");
    }
    printf("\n");
  }
}

//Função escolher posicao onde será marcado o símbolo.
int escolherCoordenada(char tabuleiro[3][3], int jogadaDaVez,
                       char caracterDoJogador) {

  int valida = 0;
  mostraTabuleiro(tabuleiro);
  while (!valida) {
    int i = 0, j = 0;
    char col = ' ';
    while(i < 1 || i > 3){
      printf("Linha: ");
      scanf("%d", &i);
      while(getchar() != '\n'); //Retira buffer e outras caracteres além da primeira.  
      if(i < 1 || i > 3)
        printf("Insira um valor válido para a linha (1 a 3).\n");
    }
    while(col != 'A' && col != 'B' && col != 'C'){
      printf("Coluna: ");
      col = getchar();
      while(getchar() != '\n'); //Retira buffer e outras caracteres além da   primeira.
    
      col = toupper(col);
      if(col != 'A' && col != 'B' && col != 'C')
        printf("Insira um valor válido para a coluna (A, B ou C).\n");
    }
    //Converter Coluna Char para Coluna int
    if      (col == 'A') j = 0;
    else if (col == 'B') j = 1;
    else if (col == 'C') j = 2;

    //Verificação se o local está disponivel.
    if (tabuleiro[i - 1][j] == ' ') {
      tabuleiro[i - 1][j] = caracterDoJogador;
      valida = 1; //Sai do loop.
    } else {
      printf("A posição já está preenchida, escolha outra.\n");
      valida = 0;
    }
  }
  system("clear||cls"); //Limpar terminal Tanto para Linux/Windows
  return !jogadaDaVez;  /* Alternancia de 0 (false) e outro valor (true) diferente 
                           de 0, sempre mudando o jogador da Vez */
}

//Função informa instrucoes para marcar a posiçao a ser marcada
int iniciaJogada(char tabuleiro[3][3], char caracterJogador1,
                  char caracterJogador2, int decideJogada, int *jogadorDaVez) {
  char caracterDaVez; //Qual simbolo sera marcado na rodada
  int fimDeJogo = 0, numeroJogadas = 1;
  while (!fimDeJogo) {
    printf("[ JOGADA N%d - VEZ DO JOGADOR %d ]\n", numeroJogadas, decideJogada + 1);
    printf("\nEscolha a coordenada de onde será marcado, sendo primeiro a linha (números) e depois a coluna (letras):\n\n");
    if (decideJogada == 0){
      caracterDaVez = caracterJogador1; //Simbolo do Jogador1
      *jogadorDaVez = 1; //Esse valor retornar pelo ponteiro para informar o vencedor
    }
    else{
      caracterDaVez = caracterJogador2; //Simbolo do Jogador1
      *jogadorDaVez = 2; //Esse valor retornar pelo ponteiro para informar o vencedor
    }
    //Decide Jogada irá alternar o valor pela funcao, assim alternando o jogador da vez
    decideJogada = escolherCoordenada(tabuleiro, decideJogada, caracterDaVez);
    fimDeJogo = verificaFimJogo(tabuleiro, caracterDaVez, numeroJogadas);
    numeroJogadas++;
  }
  return fimDeJogo; //Retorna o resultado do Jogo.
}

//Funcao iniciar a uma nova Partida
int iniciaPartida(char tabuleiro[3][3], int *fim){
    int pontosJogador1 = 0, pontosJogador2 = 0;
    char caracterJogador1, caracterJogador2;
    int valido = 1;

    // decideJogada irá dizer qual jogador está jogando, sendo '0'       para jogador 1
    // e outro valor para jogador 2.
    srand(time(NULL));
    int decideJogada = rand() % 10;
    int jogadorVencedor;

    resetaTabuleiro(tabuleiro);

    char enunciado[] = "\n\n\t\t\t      JOGO DA VELHA\n";
    int tamanhoEnunciado = strlen(enunciado);
  while (!*fim){
    mostraEnunciado(enunciado, tamanhoEnunciado);

    // Entrada Simbolos
    while (valido)
      valido = verificaEntrada(&caracterJogador1, &caracterJogador2);
    
    /* Sorteio para ver qual jogador será o primeiro a jogar 
    (Verifica numero aleatorio de 0 a 9 e compara se par ou impar.) */
    
    if (decideJogada % 2 != 0)
      decideJogada = 1;
    else
      decideJogada = 0;

    printf("\n[ JOGADOR 1 SERÁ [%c] | JOGADOR 2 SERÁ [%c] ]\n",
           caracterJogador1, caracterJogador2);

    printf("\n>> Por sorteio, a primeira jogada será do jogador %d.\n",
           decideJogada + 1);
    for(int i = 0; i < 52; i++)
      printf("_");
    printf("\n\n");
    *fim = iniciaJogada(tabuleiro, caracterJogador1, caracterJogador2, decideJogada, &jogadorVencedor);
  }
  return jogadorVencedor;
}

int verificaJogarNovamente(char tabuleiro[3][3], int *fim, int numeroJogadorVencedor, int * quantVencedor1, int * quantVencedor2){
  
  for(int i = 0; i < 55; i++)
    printf("_");
  
  printf("\n\n\tFIM DE JOGO\n\n");
  mostraTabuleiro(tabuleiro);
  if(*fim == 2){
    printf("\nVELHA! Empate para os jogadores!\n");
    numeroJogadorVencedor = 0; //Nenhum Jogador Venceu.
  }
  else{
    printf("☆ ☆ O Jogador %d é o vencedor! ☆ ☆\n\n", numeroJogadorVencedor);
  }
  switch(numeroJogadorVencedor){
    case 1:
      *quantVencedor1 += 1;
    break;
    case 2:
      *quantVencedor2 += 1;
    break;
  }  
  printf("[ PLACAR: JOGADOR 1 [%d] - JOGADOR 2 [%d] ]\n", *quantVencedor1, *quantVencedor2);

  printf("*\nSe deseja jogar novamente DIGITE 1\nSe deseja sair, digite qualquer outro valor\n"); 
  scanf("%d", fim);
    while(getchar() != '\n'); //Retira buffer e outras caracteres além da   primeira.
  
  if(*fim == 1){
    resetaTabuleiro(tabuleiro); 
    system("clear||cls"); //Limpar terminal Tanto para Linux/Windows
    return 0; //Retorna fim = 0, criando loop.
  }
  return 1; //Retorna fim  = 1, terminando looping.
}
int main() {;
  char tabuleiro[3][3];
  int quantVencedor1 = 0, quantVencedor2 = 0; //Valores para o placar
  int fim = 0; //Variavel que verifica se deu velha.
  int numeroJogadorVencedor; //Numero que será informado qual jogador venceu;
  while(!fim){
    numeroJogadorVencedor = iniciaPartida(tabuleiro, &fim);
    fim = verificaJogarNovamente(tabuleiro, &fim, numeroJogadorVencedor, &quantVencedor1, &quantVencedor2);
  }
  printf("Obrigado por jogar!\nPablo G. Almeida - 1 Periodo - UFOP.");
  return 0;
}
/* Deve-se passar o endereço de quantVencedorX para que quando saia da funcao verificaJogarNovamente, seus valores nao resetarem */
