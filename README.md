Este programa, autotest.c, realiza o teste automático de outros programas. 
Ele verifica se a saída de um programa é igual à uma saída pré-definida.
Para isto é necessário criar os aquivos de entreda (input_i.txt) e de saída (output_i.txt), onde i é o sufixo dos respectivos arquivos. 
Pode-se ter quantos arquivos de entrada e saída quantos forem necessários, sempre aos pares: para cada arquivo de entrada deve-se ter um de saída.
Por exemplo, vamos supor que um programa recebe dois números e calcaula a soma destes dois números. 
Então um arquivo de entrada teria duas duas linhas: uma para cada numero e deveria se chamar input_1.txt.
O seu respectivo arquivo de saida, output_1.txt, deve ter uma linha com a soma dos dois valores descritos no arquivo input_1.txt.
Pode-se ter quantos arquivos de testes quantos forem necessários, apenas deve-se mudar o sufixo i de cada arquivo. sendo i um inteiro incremental 
començando de 1.

Exemplo: arquivos que testam um programa que recebe dois números e fornece como saída a soma desdes dois números.

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

1) Em uma pasta qualquer copie o executável do autotest (autotest.exe)

2) Crie os arquivos de entrada (input_i.txt) e os respectivos de saída (output_i.txt), 
sendo i um numero inteiro comencando de zero e crescente

3) Execute o seguinte comando DOS: autotest caminho\nome_programa_a_ser_testado.exe
