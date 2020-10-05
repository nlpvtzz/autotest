Este programa, autotest.c, realiza o teste automático de outros programas. 
Isto é, ele verifica se a saída de um programa é igual à uma saída pré-definida.
Para isto é necessário criar os aquivos de entreda (input_i.txt) e de saída (output_i.txt), onde i é o sufixo dos respectivos arquivos. 
Pode-se ter quantos arquivos de entrada e saída quantos forem necessários, sempre aos pares: para cada arquivo de entrada deve-se ter um de saída.
Por exemplo, vamos supor que um programa recebe dois números e calcaula a soma destes dois números. 
Então um arquivo de entrada teria duas duas linhas: uma para cada numero e deveria se chamar input_1.txt.
O seu respectivo arquivo de saida, output_1.txt, deve ter uma linha com a soma dos dois valores descritos no arquivo input_1.txt.
Por exemplo:

a)
Arquivo de entrada input_1.txt
2
5
Arquivo de saida output_1.txt
7

b)
Arquivo de entrada input_2.txt
7
6
Arquivo de saida output_2.txt
13

Obs.: as saídas são comparadas caracter a caracter, portanto, espaços a mais ou a menos em uma string acusará falha no teste.

Resumo do modo de usar:
1) Em uma pasta qualquer copie o executável do autotest.c (autotest.exe)
2) Crie os arquivos de entrada (input_i.txt) e os respectivos de saída (output_i.txt)
3) Dentro desta pasta, crie uma subpasta chamada bin
4) Dentro da subpasta bin, crie uma subpasta chamada Debug
5) Na pasta raiz do autotest, execute o seguinte comando DOS: autotest nome_programa_a_ser_testado
