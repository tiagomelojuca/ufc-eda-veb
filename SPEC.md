### Descrição geral do trabalho:

O objetivo do trabalho é implementar uma estrutura van Emde Boas com espaço linear no número de elementos, ou seja, usando tabela de dispersão com table doubling/halving. A estrutura deve ser feita para o tamanho de palavra de 32 bits. A entrada do programa é um arquivo de texto com várias operações sobre a estrutura (uma por linha). A saída do programa será um arquivo de texto com as operações contidas no arquivo de entrada e seus resultados em seguida, caso existam. 

### Operações:

- **Inclusão:** Uma operação de inclusão será identificada por uma linha escrito INC seguido de um espaço e depois um inteiro. Este elemento deve ser incluído na estrutura de dados.  
  
Exemplo na entrada:  
`INC 13`  
  
No arquivo de saída será gerado:
`INC 13`  
  
- **Remoção:** Uma operação de remoção será identificada por uma linha escrito REM seguido de um espaço e depois um inteiro. Este valor deve ser removido da estrutura, se existir.  
  
Exemplo na entrada:  
`REM 42`

No arquivo de saída será gerado:  
`REM 42`
  
- **Sucessor:** Uma operação de sucessor será identificada por uma linha escrito SUC seguido de um espaço e depois um inteiro. O sucessor do número x é o menor valor na estrutura que é estritamente maior que x. Esta operação gera como resultado o sucessor do inteiro dado como entrada.  
  
Exemplo na entrada:  
`SUC 50`  
  
No arquivo de saída será gerado:  
`SUC 50`  
`80`

- **Predecessor:** Uma operação de predecessor será identificada por uma linha escrito PRE seguido de um espaço e depois um inteiro. O predecessor do número x é o maior valor na estrutura que é estritamente menor que x. Esta operação gera como resultado o predecessor do inteiro dado como entrada.  
  
Exemplo na entrada:  
`PRE 50`  
  
No arquivo de saída será gerado:  
`PRE 50`  
`21`

- **Imprimir:** Uma operação de impressão será identificada por uma linha escrito IMP. A impressão de uma van Emde Boas oferece uma visão a partir do primeiro nível da estrutura. Neste caso, você deve imprimir o valor mínimo da estrutura, os valores que estão nos clusters não vazios.  
  
Exemplo na entrada:  
`IMP`  
No arquivo de saída será gerado:  
`IMP`  
`Min: 102, C[0]: 268, 322, 14756, C[3]: 456, 728, 152, C[65535]: 0, 65535`

### Grupos e Entrega:

- Cada equipe da graduação pode ser formada por até 3 membros.
- O trabalho na pós-graduação é individual.
Você deve enviar o seu código e indicando sua linguagem de programação e como compilar o seu programa. Deve haver um arquivo de descrição do trabalho que indica como rodar o seu programa e descrevendo as funções e estruturas (equivalente ao struct em C) que são usadas no seu código e em que arquivos eles se encontram.
