#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define ASCII7SIZE 127

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
        printf("bin %c\n", binary[j]);
        if(temp==0){
            if(binary[j]=='1'){
                temp = 1;
                printf("Começar da contagem");
            
            };
        }
        else{
            if(binary[j]=='0'){
                count = count+1;
                printf("count: %d \n", count);
            }
        }
    }
    printf("O numero de zeros consecutivos e: %d\n", count);
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

//Segue a mesma teoria que a função intInIntArray
int findFirstEmptyIdx(int *arr, int arrLength){
    int arrL = sizeof(arr)/sizeof(int);
    for(int i=0; i<arrL; i++){
        if(arr[i]!=-1){
            return i;
        };
    };
    return -1;
}

/*
    Esta função já está dividida entre as linhas de código então vou seguir a mesma estrutura para fazer a explicação:
    LEITURA DO FICHEIRO - Para realizar a leitura do ficheiro começamos por realizar a declaração da variavel fp como 'FILE'. 
    'FILE *fp' faz com que fp possa ser usado como ponteiro de ficheiros. Por sua vez nós definimos fp como ponteiro do ficheiro
    colocado como input com o fopen(file_name) o string "r" no fim corresponde a um dos diversos códigos existentes para esta função.
    Aqui "r" permite apenas a leitura do ficheiro que é necessáriamente o que precisamos neste caso.
    Mais informação: https://www.programiz.com/c-programming/c-file-input-output
    De modo a realizar a leitura do ficheiro começámos por utilizar um troço de código muito importante nestas últimas duas funções da 
    parte do Lab em C. fseek() é uma função que permite procurar determinadas posições consoante o termo colocado como último input.
    SEEK_END como input faz com que seja procurada a última posição do ponteiro e SEEK_SET faz com que retorne à posição original do 
    ponteiro. 
    Mais informação: https://www.tutorialspoint.com/c_standard_library/c_function_fseek.htm
    ftell() apenas guarda numa variavel, neste caso, fpL, a posição do ponteiro dado. Desta forma temos agora o ponteiro inicial e final que
    por sua vez nos permite obter a dimensão do ficheiro que por sua vez nos permite navegar todos os termos do array onde vamos colocar os
    dados lidos do ficheiro.
    COLOCAÇÃO E CONTAGEM - Seguidamente criamos dois arrays distintos, asciiLetter e asciiCount, com dimensão de 127 [hardcoded através da
    constante global ASCII7SIZE], valor correspondente ao número de símbolos 
    existentes em ASCII-7 (ascii utilizado em C). Estas vão funcionar como HashMap/Linked List uma vez que os id's da data guardada são partilhados
    (o idx de 'a' em asciiLetter é o mesmo idx que 'a' em asciiCount). Estas duas listas vão ser ambas passadas em emptyIntArray() que coloca todas as posições do
    array a -1 (vai ser explicado o porquê da necessidade de ser -1 e não zero para a frente) para ser possível realizar a contagem dos símbolos presentes.
    SIDENOTE - É possível reduzir a dimensao destes dois arrays para 125 se for adicionada uma condição para filtragem de ' ' e ENTER [seria adicionado
    na linha 172]
    VERIFICAÇÃO DO MAIOR/MENOR - aqui tal como o nome indica realizamos a contagem e para isso temos duas variáveis cruciais em qualquer linguagem
    para a realização desta operaçã, ou seja, maior e menor. Menor e maior começam como o primeiro valor ímpossivel (máximo seria 126 por isso usamos 127 no
    caso de menor e -1 em maior porque o mínimo seria 0). Seguidamente temos os arrays menorArr e menorArr da dimensão necessária para caso 
    necessário guardar todos os símbolos como símbolos mais frequentes e menos frequentes (no caso em que isto acontece o mais frequente é também
    o menos frequente por isso a dimensão deve sempre ser esta para responder sem falha ao pedido). Por fim mas não menos importante temos maiorIdx
    e menorIdx que guardam os indexes das posições em que podemos escrever/adicionar os indexes (asciiLetter e asciiCount) de símbolos que sejam tão frequentes ou tão infrequentes
    como o que estamos agora a considerar maior ou menor. Seguidamente passamos em todas as posições de asciiCount que sejam diferentes de 0 (ou seja inexistentes
    no ficheiro) de modo a obter a data que queremos relativa a mais frequentes e menos frequentes. Uma vez que o método de verificação é análogo vou explicar 
    apenas a relação de maior: Começamos por verificar se o asciiCount atual é superior ao símbolo mais frequente e caso o seja colocamos todas as posições do 
    maiorArr a -1 (index fora do intervalo possível de indexes o que faz com que possa ser identificado se se está a referir a uma posição "vazia" ou temos um indexe com valor
    neste contexto). Seguidamente colocamos o maiorIdx a 0 para que possamos começar a escrever mais uma vez os termos com maior contagem dentro do ficheiro. 
    Com estes podemos agora definir o maiorArr[maiorIdx] como o index atual do novo maior valor (este agora é o único que aqui se encontra). Por fim incrementamos o idx
    por motivos obvios. A restante condição necessária corresponde a se este valor for igual ao que já temos na contagem de maior. Nesse caso não é "esvaziado" o o array
    e apenas adicionamos o index correspondente a este valor ao maiorArr[maiorIdx] e seguidamente incrementamos maiorIdx.
    PRINT DOS RESULTADOS - Filtragem básica dos arrays maiorArr e menorArr e caso o array em questão tiver apenas um elemento dar print desse apenas com uma frase 
    sintaxicamente apropriada e caso seja multipla é realizado um for() para que realize print apropriado sintaxicamente e apresente também todos os items mais e menos
    frequentes.
    Importante notar que um documento sem qualquer símbolo, ou seja, vazio, não realizaria qualquer tipo de Print.
*/

void most_frequent_symbol( char *file_name ){
    //LEITURA DO FICHEIRO
    FILE *fp;
    fp = fopen(file_name, "r");
    fseek(fp, 0, SEEK_END);
    int fpL = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    int asciiArray[fpL];
    if (fp == NULL)
   {
      perror("Error reading the file.\n");
   };
   //COLOCAÇÃO E CONTAGEM
   int asciiLetter[ASCII7SIZE]; //ASCII-7 size
   emptyIntArray(asciiLetter, ASCII7SIZE);
   int asciiCount[ASCII7SIZE]; //ASCII-7 size
   emptyIntArray(asciiCount, ASCII7SIZE);
   for(int i=0; i<ASCII7SIZE; i++){
        if(intInIntArray(asciiArray, fpL, asciiLetter[i])) asciiCount[asciiArray[i]]++;
        else{
            int temp = findFirstEmptyIdx(asciiLetter, ASCII7SIZE);
            asciiLetter[temp] = asciiArray[i];
            asciiCount[temp] = 1;
        };
   };
   //VERIFICAÇÃO DE MAIOR/MENOR
    int menor = ASCII7SIZE;
    int maior = -1;
    int maiorArr[ASCII7SIZE];
    int maiorIdx = 0;
    int menorArr[ASCII7SIZE];
    int menorIdx = 0;
    for(int i=0; i<ASCII7SIZE; i++){
        if(asciiCount[i]!=-1){
            if(asciiCount[i]>asciiCount[maior]){
                emptyIntArray(maiorArr, ASCII7SIZE);
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
                emptyIntArray(menorArr, ASCII7SIZE);
                menorArr[menorIdx] = asciiLetter[i];
                menorIdx++;
                menor = i;
            }
            if(asciiCount[i]==asciiCount[menor]){
                maiorArr[menorIdx] = asciiLetter[i];
                menorIdx++;
            }
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


/*
    Esta função funciona de maneira bastante semelhante à anterior pelo que a única coisa que quero adicionar é que para a criação de um array 
    com a data negada utilizamos a função fgetc() que nos retorna o char naquela posição de memória e seguidamente realizamos a operação XOR
    com 255 que faz com que os bits fiquem negados. Para além disso no fopen() seguinte utilizámos "wb" que permite escrever bit a bit no ficheiro.
    A função rename() apenas altera o nome do ficheiro para o desejado e caso tenha sucesso retorna 0.
*/
void negative_file( char *input_file_name, char *output_file_name) {
    //LEITURA DO FICHEIRO
    FILE *fp;
    fp = fopen(input_file_name, "rb");
    if (fp == NULL){
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
    }

    //CALCULAR TAMANHO DO FICHEIRO
    fseek(fp, 0, SEEK_END);
    int fpL = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    //CRIAR ARRAY COM PRODUTO NEGADO
    int notFp[fpL];
    for(int i=0; i<fpL; i++){
        notFp[i] = fgetc(fp) ^ 255;
    }
    fclose(fp);

    //ESCRITA DO RESULTADO DA NEGAÇÃO
    fp = fopen(input_file_name, "wb");
    for(int i = 0; i < fpL; i++){
        fputc(notFp[i], fp);
    }

    fclose(fp);

    //MUDANÇA DE NOME DO FICHEIRO
    if (rename(input_file_name, output_file_name) != 0) {
        printf("The file could not be renamed.");
    } else {
        printf("The file is renamed successfully.");
    }
}

void testCountZeros(int val){
    int temp = count_zeros(val);
    bool result;
    if(temp==2) result = true;
    else result = false;
    if(result==false) printf("Count Zeros function is not working \n");
    else printf("Count Zeros function is working");
}

void testCountOnes(int val){
    int temp = count_ones(val);
    bool result;
    if(temp==7) result = true;
    else result = false;
    if(result==false) printf("Count ones function is not working");
    else printf("Count ones funcion is working");
}

int main() {
    int countTestValue = 475;
    char binary[32];
    intToBinary(countTestValue, binary);
    printf("Binary value is: %s \n", binary);
    printf("Should equal: 00000000000000000000000111011011 \n");
    testCountZeros(countTestValue);
    testCountOnes(countTestValue);
}