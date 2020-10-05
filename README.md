Este programa, autotest, realiza o teste automático de outros programas. 
Isto é, ele verifica se a saída de um programa qq são iguais às saídas pré-definidas.
Para isto é necessário criar os aquivos de entreda (input_i) e de saída (output_i), onde i é o sufixo dos respectivos arquivos.
Por exemplo, vamos supor que um programa recebe dois números e calcaula a soma destes dois números. 
Então um arquivo de entrada teria duas duas linhas: uma para cada numero, e deveria se charmar input_1.txt.
Um segundo arquivo, com valores diferentes, deveria se chamar input_2.txt, e assim por diante.
Um arquivo de saida com o valor esperado para a entrada input_1.txt deveria ser criado com o nome de output_1.txt contendo a resposta esperada
para esta entrada. Por exemplo:

- Arquivo de entrada input_1.txt
2
5
- Arquivo de saida output_1.txt
7

- Arquivo de entrada input_2.txt
7
6
- Arquivo de saida output_2.txt
13

Podem ser criados arquivos de entrada e saida tantos quantos forem necessários.

Modo de usar:
1) Em uma pasta qualquer copie o executável do autotest
2) Crie os arquivos de entrada (input_i.txt) e os de saída (output_i.txt)
3) Dentro desta pasta, crie uma subpata chamada bin
4) Dentro da subpasta bin, crie uma subpasta chamada Debug
5) Na pasta raiz do autotest, execute o seguinte comando DOS: autotest nome_programa_a_ser_testado

