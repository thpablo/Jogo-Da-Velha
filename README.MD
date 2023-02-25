# :hash: JOGO DA VELHA 

Trata-se do famoso jogo da velha desenvolvido em C para a conclusão do Trabalho Prático proposto pela faculdade.

# Instalação

## Compilador C para Windows

Para a execução do código, é necessário apenas o compilador de C/C++. Você pode instalar o [MinGW](https://sourceforge.net/projects/mingw/).

## Compilador C para Linux

Nativamente o compilador para C já vem instalado em sistemas Linux. Para checar, você pode testar no prompt.

`$ gcc -v`

> Caso não esteja instalado, você o encontra no seguinte link: <http://gcc.gnu.org/install/>.

# Instruções

O jogo apresenta comandos básicos, onde primeiramente o Jogador 1 irá escolher seu símbolo para representar sua marcações selecionadas, sendo **X** ou **O**. O Jogador 2 irá ficar com o símbolo que não foi selecionado.

A primeira jogada é sorteada após a seleção do símbolo feita pelo Jogador 1.

Após o sorteio é perguntado a linha em que será escolhido a marcação da posição, sendo um valor entre 1 e 3. Em seguida, a coluna, sendo uma A, B ou C, conforme é mostrado no tabuleiro.