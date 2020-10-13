#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define FILE_NAME_SIZE 100
#define COMMAND_SIZE 500
#define PROGRAM_NAME_SIZE 500
#define OUTPUT_ROW_SIZE 500

int outputCompare (char *, char *, char *);
int buffer2Row (char *, int, char [][OUTPUT_ROW_SIZE]);
int commandMaker (char *, char *, char *, char *);
int fileRead (char *, char *);
int stringCount(char [], int, char [], int);
int testCount (char *, char *, int);
long fileSize (char *);

int main (int argc, char *argv[]) {
    char workDir [FILE_NAME_SIZE];
    char programName[PROGRAM_NAME_SIZE];
    char programFullName[2*PROGRAM_NAME_SIZE];
    char command[COMMAND_SIZE];
    char inputFileName[FILE_NAME_SIZE];
    char outputFileName[FILE_NAME_SIZE];
    char testFileName[FILE_NAME_SIZE];
    int fails=0;

    if (argc==1) {
        printf("Program to test: ");
        fflush(stdin);
        gets(programFullName);
        strcpy(programName, programFullName);

        printf("Directory of tests: ");
        fflush(stdin);
        gets(workDir);

    } else {
        sprintf(programName, "%s", argv[1]);
        strcpy (workDir, ".\\");
        sprintf (programFullName, "\"%s%s\"", workDir, programName);
    }

    //printf("\nDir\n%s\n\n", workDir);
    //printf("Program\n%s\n\n", programName);
    //printf("Full name\n%s\n\n", programFullName);

    int qtInput = testCount("input_", workDir, sizeof("input_")-1);
    if(qtInput == 0){
        printf("Error: no test files are found\n");
        return -1;
    }
    int qtOutput = testCount("output_", workDir, sizeof("output_")-1);
    if (qtInput != qtOutput) {
        printf("Error: the number of input and output files are not the same\n");
        return -1;
    }

    int qtTest = qtInput;
    for (int i=1; i<=qtTest; i++) {
        // make the input and output files names
        //printf("Work dir: %s\n", workDir);
        sprintf(inputFileName, "%s\\input_%d.txt", workDir, i);
        sprintf(testFileName, "%s\\outputTest_%d.txt", workDir, i);
        sprintf(outputFileName, "%s\\output_%d.txt", workDir, i);

        // make the execution command name
        strcpy(command, "");
        commandMaker(inputFileName, testFileName, programFullName, command);
        //printf ("Command:\n%s\n", command);
        int systemReturn = system (command);
        if (systemReturn!=0) {
            printf("\nError trying to execute the command:\n%s\n", command);
            return -1;
        }

        printf("\nTest %d ", i);
        fails += outputCompare(inputFileName, outputFileName, testFileName);
        //if (fails  == -1)
          //  break;
    }
    if(fails){
        printf("\n---------- Resultado Final: FALHA -------------\n\n");
    } else {
        printf("\n---------- Resultado Final: SUCESSO -----------\n\n");
    }
    return 0;
}

int outputCompare (char *inputFileName, char *outputFileName, char *testOutputFileName){
    int fails = 0;

    int inputFilesize = fileSize(inputFileName);
    if (inputFilesize<0) return -1;
    char* inputBuffer = (char *) malloc(inputFilesize+1 * sizeof(char));

    int outputFileSize = fileSize(outputFileName);
    if (outputFileSize<0) return -1;
    char* outputBuffer = (char *) malloc(outputFileSize+1 * sizeof(char));

    int testFileSize = fileSize(testOutputFileName);
    if (testFileSize<0) return -1;
    char* testBuffer = (char *) malloc(testFileSize+1 * sizeof(char));

    int r = fileRead(inputFileName, inputBuffer);
    if (r!=0) return -1;
    inputBuffer[inputFilesize]='\0';
    //printf ("\nInput buffer\n%s\n", inputBuffer);

    r = fileRead(outputFileName, outputBuffer);
    if (r!=0) return -1;
    outputBuffer[outputFileSize]='\0';
    //printf ("\nOutput buffer\n%s\n", outputBuffer);

    r = fileRead(testOutputFileName, testBuffer);
    if (r!=0) return -1;
    testBuffer[testFileSize]='\0';
    //printf ("\nTest buffer\n%s\n", testBuffer);

    if (outputFileSize != testFileSize) {
        printf("-------------> Falha: saidas possuem tamanhos diferentes\n");
        fails++;
        //return -1;
    } else {
        for (int i=0; i<=outputFileSize; i++) {
            if(outputBuffer[i] != testBuffer[i]) {
                fails++;
                printf("--> Falha: saida realizada diferente da esperada\n");
                break;
            }
        }
    }

    if (fails) {
        printf("--> Entrada:\n%s\n", inputBuffer);
        printf("--> Saida Realizada:\n%s\n", testBuffer);
        printf("--> Saida Esperada:\n%s\n", outputBuffer);

        return fails;
    } else {
        printf ("  -->  ok\n");
    }

    return fails;
}

/*
int outputCompare (char *inputFileName, char *outputFileName, char *testOutputFileName){
    int inputFilesize = fileSize(inputFileName);
    if (inputFilesize<0) return -1;
    char* inputBuffer = (char *) malloc(inputFilesize+1 * sizeof(char));

    int outputFileSize = fileSize(outputFileName);
    if (outputFileSize<0) return -1;
    char* outputBuffer = (char *) malloc(outputFileSize+1 * sizeof(char));

    int testFileSize = fileSize(testOutputFileName);
    if (testFileSize<0) return -1;
    char* testBuffer = (char *) malloc(testFileSize+1 * sizeof(char));

    int r = fileRead(inputFileName, inputBuffer);
    if (r!=0) return -1;
    inputBuffer[inputFilesize]='\0';
    printf ("\nInput buffer\n%s\n", inputBuffer);

    r = fileRead(outputFileName, outputBuffer);
    if (r!=0) return -1;
    outputBuffer[outputFileSize]='\0';
    printf ("\nOutput buffer\n%s\n", outputBuffer);

    r = fileRead(testOutputFileName, testBuffer);
    if (r!=0) return -1;
    testBuffer[testFileSize]='\0';
    printf ("\nTest buffer\n%s\n", testBuffer);

    char rowIn[10][OUTPUT_ROW_SIZE];
    buffer2Row(inputBuffer, inputFilesize, rowIn);

    char rowOut[10][OUTPUT_ROW_SIZE];
    int lc = buffer2Row(outputBuffer, outputFileSize, rowOut);

    char rowTest[10][OUTPUT_ROW_SIZE];
    int lt = buffer2Row(testBuffer, testFileSize, rowTest);

    for (int i=0; i<=lt; i++) {
        if (lt != lc) {
            printf("-------------> Falha: saidas possuem tamanhos diferentes\n");
            return -1;
        }

        if(strcmp(rowTest[i], rowOut[i])==0) {
            printf("--> ok\n");
        } else {
            printf("--> Falha\n");
            printf("--> Entrada:\n%s\n", inputBuffer);
            printf("--> Saida Realizada:\n%s\n", rowTest[i]);
            printf("--> Saida Esperada:\n%s\n", rowOut[i]);

            return -1;
        }
    }
    return 0;
}
*/

int buffer2Row (char *buffer, int size, char rows[][OUTPUT_ROW_SIZE]) {
    int c=0;
    int l=0;
    int i=0;

    while (i<=size) {
        if (buffer[i]=='\n') {
            rows[l][c] = '\0';
            l++;
            c=0;
        }
        else {
            rows[l][c] = buffer[i];
            c++;
        }
        i++;
    }
    return l;
}

int commandMaker (char *input, char *output, char *arquivo, char *text) {
    strcat (text, arquivo);
    strcat (text, " < ");
    strcat (text, input);
    strcat (text, " > ");
    strcat (text, output);

    return 0;
}

long fileSize (char *fileName) {
    FILE *id_arq;

    id_arq = fopen(fileName, "rb");
    if (id_arq == NULL) {
        printf("ERROR! The file %s cannot be open!\n", fileName);
        return -1;
    }
    // Read the file size
    fseek(id_arq, 0, SEEK_END);
    long size = ftell(id_arq);

    fclose(id_arq);

    return size;
}

int fileRead (char *arquivoName, char *buffer) {
    FILE *id_arq;

    id_arq = fopen(arquivoName, "rb");
    if (id_arq == NULL) {
        printf("ERRO! O arquivo %s não foi aberto!\n", arquivoName);
        return -1;
    }

    /* Read the file size */
    fseek(id_arq, 0, SEEK_END);
    long size = ftell(id_arq);
    rewind(id_arq);

    /* Store the initial position*/
    if(buffer == NULL) {
        printf("Erro ao tentar alocar o buffer de memoria para o arquivo %s.\n", arquivoName);
        return -2;
    }

    /* Read the full file */
    size_t elementos_lidos = fread(buffer, 1, size, id_arq);
    if(elementos_lidos != size) {
        printf("Erro ao tentar ler o arquivo %s.\n", arquivoName);
        return -3;
    }

    fclose(id_arq);

    return 0;
}

int testCount (char fileName[], char dir[], int tam) {
    int ocorrs = 0;
    char command [COMMAND_SIZE];
    char fileFullName [FILE_NAME_SIZE];

    sprintf(fileFullName, "%s\\qtTest.txt", dir);
    sprintf(command, "dir %s /b >> %s", dir, fileFullName);
    system (command);

    int testFileSize = fileSize(fileFullName);
    if (testFileSize == -1) return -1;

    char* buffer = (char *) malloc(testFileSize+1 * sizeof(char));

    int r = fileRead(fileFullName, buffer);
    if (r!=0) return -1;
    buffer[testFileSize]='\0';

    char rows[100][OUTPUT_ROW_SIZE];
    int l = buffer2Row(buffer, testFileSize, rows);

    for (int i= 0; i<l; i++)   {
        ocorrs += stringCount(rows[i], sizeof(rows[i]), fileName, tam);
    }
    //printf("Qt arquivos de teste: %d\n", ocorrs);

    sprintf(command, "del %s", fileFullName);
    system (command);

    return ocorrs;
}

int stringCount(char a[], int m, char b[], int n) {
    int ocorrs=0, i=0, j=0;

    for (i=0; i<m; i++) {
        j=0;
        while (a[i]==b[j]) {
            i++; j++;
            if (i==m || j==n) break;
        }
        if (j==n) {
            ocorrs++;
        }
    }

    return ocorrs;
}

