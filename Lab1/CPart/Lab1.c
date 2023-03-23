#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_FILE_SIZE 1000 //leitura maxima de uma ficheiro de 1000 Bytes


//intToBinary é só um algoritmo base que converte um valor inteiro num array de char (no fundo um string) que representa o valor inteiro em binario.
//A parte do algoritmo pode ser facilmente encontrado na net (tanto que foi daí que veio), no entanto como não sei como retornar um array fiz com que a função altera-se um array que recebe como input
void intToBinary(int num, char* binary) {
    int i = 0;
    int j = 0;
    int bits = sizeof(int) * 8;
    for (i = bits - 1; i >= 0; i--) {
        binary[j] = ((num >> i) & 1) ? '1' : '0';
        j++;
    }
    binary[j] = '\0';
}

//count_ones passa por todos as posições do array recebido ao utilizar intToBinary com um array de 32 elementos (numero de bits de um int)
//e incrementa uma variavel cada vez que este é igual a 1
int count_ones(int val){
    char binary[32];
    intToBinary(val, binary);
    int count = 0;
    int temp = 0;
    for(int j=0; j<32; j++){
        if(temp==0){
            if(binary[j]=='1'){
                temp = 1;
                count++;
            };
        } else{
            if(binary[j]=='1'){
                count++;
            };
        };
    }
    return count;
} 

//count_zeros tem o mesmo funcionamento que a função countOnes com a distinção que apenas inicia a contagem dos 0 após encontrar o primeiro 1
int count_zeros(int val){ 
    char binary[32];
    intToBinary(val, binary);
    int count = 0;
    int temp = 0;
    for(int j=0; j<32; j++){
        if(temp==0){
            if(binary[j]=='1'){
                temp = 1;
            };
        } else{
            if(binary[j]=='0'){
                count++;
            };
        };
    }
    return count;
}

//print_bits passa em todas as posições do array binario gerado por intToBin e dá um print regular a cada um deles
void print_bits( int val ) {
    char binary[32];
    int i = val;
    intToBinary(i, binary);
    for (i = 0 ; i <sizeof(binary); i++) {
        printf("%c", binary[i]);
    };
    printf("\n");
}

/*
    int *arr corresponde a um ponteiro para a posição de memória onde se pode encontrar o array
    em C quando escrevemos uma variavel estamos no fundo a escrever a posição de memoria em que 
    se encontra ent isto nao gere conflito com colocar diretamente o nome do array como input
    pelo contrario, até é conveniente porque assim recebe a posição do primeiro elemento do array,
    ou seja, posição de arr[0].
    Com isso passa a ser possivel navegar as posições do array.
    Questão que eu tinha que por acaso acho bacano entender: "Porque é que não posso passar apenas
    int arr como input e calcular o arrLength dentro da função?"
    A função sizeof() utilizada para calcular o tamanho do objeto (o método como é feito pode ser
    observado várias vezes lá para a frente) retorna o tamanho do objeto em bytes, no entanto, quando
    passado um array para uma função em C, o nome do array é convertido na primeira posição do mesmo,
    tal como mencionado acima. Pelo que seria impossivel calcular o tamanho lá dentro uma vez que iria
    retornar apenas a dimensão da posição da memoria/tamanho do ponteiro no elemento [0].
*/
bool intInIntArray(int *arr, int arrLength, int val){
    for(int i=0; i<arrLength; i++){
        if(arr[i]==val){
            return true;
        }
    }
    return false;
}

//Segue a mesma teoria que a função intInIntArray
void emptyIntArray(int *arr, int arrLength){
    for(int i=0; i<arrLength; i++){
        arr[i] = -1;
    }
}

//testar mais uma vez o upload
int findFirstEmptyIdx(int *arr, int arrLength){
    int arrL = sizeof(arr)/sizeof(int);
    int firstEmptyIndex = -1;
    for(int i=0; i<arrL; i++){
        if(arr[i]!=-1){
            firstEmptyIndex = i;
            break;
        };
    };
    return firstEmptyIndex;
}


void most_frequent_symbol( char *file_name ){
    //LEITURA DO FICHEIRO
    FILE *fp;
    fp = fopen(file_name, "r");
    int asciiArray[MAX_FILE_SIZE]; // array to hold contents of file
    int fpL = fread(asciiArray, sizeof(int), MAX_FILE_SIZE, fp);
    if (fp == NULL)
   {
      perror("Error while opening the file.\n");
   };
   //COLOCAÇÃO E CONTAGEM
   int asciiLetter[127]; //ASCII-7 size
   emptyIntArray(asciiLetter, 127);
   int asciiCount[127]; //ASCII-7 size
   emptyIntArray(asciiCount, 127);
   for(int i=0; i<127; i++){
        if(intInIntArray(asciiArray, fpL, asciiLetter[i])) asciiCount[asciiArray[i]]++;
        else{
            int temp = findFirstEmptyIdx(asciiLetter, 127);
            asciiLetter[temp] = asciiArray[i];
            asciiCount[temp] = 1;
        };
   };
   //VERIFICAÇÃO DE MAIOR/MENOR
    int menor = 127;
    int maior = 0;
    int maiorArr[127];
    int maiorIdx = 0;
    int menorArr[127];
    int menorIdx = 0;
    for(int i=0; i<127; i++){
        if(asciiCount[i]>asciiCount[maior]){
            emptyIntArray(maiorArr, 127);
            maiorIdx=0;
            maiorArr[maiorIdx] = asciiLetter[i];
            maiorIdx++;
            maior = i;
        };
        if(asciiCount[i]==asciiCount[maior]){
            maiorArr[maiorIdx] = asciiLetter[i];
            maiorIdx++;
        }
        if(asciiCount[i]<asciiCount[menor]){
            menorIdx = 0;
            emptyIntArray(menorArr, 127);
            menorArr[menorIdx] = asciiLetter[i];
            menorIdx++;
            menor = i;
        }
        if(asciiCount[i]==asciiCount[menor]){
            maiorArr[menorIdx] = asciiLetter[i];
            menorIdx++;
        }
    }
    //PRINT DE RESULTADOS
    if(maiorIdx==1){
        printf("The most frequent symbol is ");
        putchar(maiorArr[0]);
        printf(" and it appeared %d times\n", asciiCount[maiorArr[0]]);
    }
    else{
        printf("The most frequent symbols are ");
        for(int i=0; i<maiorIdx; i++){
            putchar(maiorArr[i]);
            if(i!=maiorIdx-1){
                printf(", ");
            }
        }
        printf(" and they appeared %d times\n", asciiCount[maiorArr[0]]);
    }
    if(menorIdx==1){
        printf("The least frequent symbol is ");
        putchar(menorArr[0]);
        printf(" and it appeared %d times\n", asciiCount[menorArr[0]]);
    }
    else{
        printf("The least frequent symbols are ");
        for(int i=0; i<menorIdx; i++){
            putchar(menorArr[i]);
            if(i!=menorIdx-1){
                printf(", ");
            }
        }
        printf(" and they appeared %d times\n", asciiCount[menorArr[0]]);
    }
}

void changeFileName(char *input_file_name, char *output_file_name){
    int result = rename(input_file_name, output_file_name);
    if (result == 0) {
        printf("The file is renamed successfully.");
    } else {
        printf("The file could not be renamed.");
    }
}


//ESTA FUNÇÃO NÃO É FINAL DE TODO!!!! ESTA FUNÇÃO FOI ALTERADA IMENSO PELO AI! Eu ainda
//vou escrever esta função de uma maneira que faça sentido para as nossas capacidades agora que entendo mais.
//A original que fizemos hoje nao estava a funcionar por muitas razões e eu depois quando tiver tempo para comentar
//tudo explico em pormenor.
void negative_file( char *input_file_name, char *output_file_name) {
    //LER O FICHEIRO EM BINÁRIO
    FILE *fp = fopen(input_file_name, "rb");
    if (fp == NULL){
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
    }
    
    // Obter o tamanho do ficheiro
    fseek(fp, 0, SEEK_END);
    int fpL = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    // Ler o ficheiro para uma matriz de inteiros
    int notFp[fpL];
    for(int i = 0; i < fpL; i++){
        notFp[i] = fgetc(fp) ^ 255;
    }
    
    fclose(fp);
    
    // Escrever a matriz de inteiros invertidos de volta para o ficheiro original
    fp = fopen(input_file_name, "wb");
    for(int i = 0; i < fpL; i++){
        fputc(notFp[i], fp);
    }
    
    fclose(fp);
    
    // Renomear o arquivo
    if (rename(input_file_name, output_file_name) != 0) {
        printf("The file could not be renamed.");
    } else {
        printf("The file is renamed successfully.");
    }
}

int main() {
    char teste[] = "teste.txt";
    char teste1[] = "teste1.txt";
    negative_file(teste, teste1);
    //negative_file(teste1, teste);
}
