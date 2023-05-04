#include <stdio.h>
#include <stdbool.h>

#define ASCII7SIZE 127

void intToBinary(int val, char binary[32]) {
    for (int i = 31; i >= 0; i--) {
        binary[i] = (val & 1) ? '1' : '0';
        val >>= 1;
    }
    binary[32] = '\0';
}

int count_zeros(int val) {
    char binary[32];
    intToBinary(val, binary);
    int count = 0;
    int temp = 0;
    for (int i = 0; i < 32; i++) {
        if (binary[i] == '1') {
            temp = 1;
        }
        if (temp == 1 && binary[i] == '0') {
            count++;
        }
    }
    return count;
}

int count_ones(int val) {
    char binary[32];
    intToBinary(val, binary);
    int count = 0;
    for (int i = 0; i < 32; i++) {
        if (binary[i] == '1') {
            count++;
        }
    }
    return count;
}

void testCountZeros(){
    int val1 = 0b10101010101010101010101010101010; //binary representation of 1431655765
    int val2 = 0b11111111111111111111111111111111; //binary representation of -1
    int val3 = 0b00000000000000000000000000000000; //binary representation of 0
    char binary1[32], binary2[32], binary3[32];
    intToBinary(val1, binary1);
    intToBinary(val2, binary2);
    intToBinary(val3, binary3);
    int count1 = count_zeros(val1);
    int count2 = count_zeros(val2);
    int count3 = count_zeros(val3);
    printf("val1 = %d, binary representation = %s, count_zeros = %d\n", val1, binary1, count1);
    printf("val2 = %d, binary representation = %s, count_zeros = %d\n", val2, binary2, count2);
    printf("val3 = %d, binary representation = %s, count_zeros = %d\n", val3, binary3, count3);
}

void testCountOnes(){
    int val1 = 0b10101010101010101010101010101010; //binary representation of 1431655765
    int val2 = 0b11111111111111111111111111111111; //binary representation of -1
    int val3 = 0b00000000000000000000000000000000; //binary representation of 0
    char binary1[32], binary2[32], binary3[32];
    intToBinary(val1, binary1);
    intToBinary(val2, binary2);
    intToBinary(val3, binary3);
    int count1 = count_ones(val1);
    int count2 = count_ones(val2);
    int count3 = count_ones(val3);
    printf("val1 = %d, count_ones = %d\n", val1, count1);
    printf("val2 = %d, count_ones = %d\n", val2, count2);
    printf("val3 = %d, count_ones = %d\n", val3, count3);
}

/////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void print_bits( int val ) {
    char binary[32];
    int i = val;
    intToBinary(i, binary);
    for (i = 0 ; i <sizeof(binary); i++) {
        printf("%c", binary[i]);
    };
    printf("\n");
}

void teste_print_bits(){
    int val1 = 0b10101010101010101010101010101010; //binary representation of 1431655765
    int val2 = 0b11111111111111111111111111111111; //binary representation of -1
    int val3 = 0b00000000000000000000000000000000; //binary representation of 0
    print_bits(val1);
    print_bits(val2);
    print_bits(val3);
}

////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

char most_frequent_symbol(char *file_name){
    FILE *fp;
    fp = fopen(file_name, "r");

    if (fp == NULL)
   {
      perror("Error reading the file.\n");
   };

    char c;

    char asciiLetter[ASCII7SIZE]; //linked list no fundo
    int asciiNumberOfOccurrences[ASCII7SIZE];

    int asciiLetterIdx = 0;

   while ((c = fgetc(fp)) != EOF) {

        int ifFoundIdx = -1;

        for(int i=0; i<=asciiLetterIdx; i++){
            if(c==asciiLetter[i]){
                ifFoundIdx = i;
                break;
            }
        }

        if(ifFoundIdx!=-1){
            asciiNumberOfOccurrences[ifFoundIdx] = asciiNumberOfOccurrences[ifFoundIdx] + 1;
        }
        else{
            asciiLetter[asciiLetterIdx] = c;
            asciiNumberOfOccurrences[asciiLetterIdx] = 1;
            asciiLetterIdx = asciiLetterIdx + 1;
        }

   }

   fclose(fp);

    int most_freq_symbols[asciiLetterIdx+1]; //posiçao das symbs mais usadas
    int most_freq_symbols_IDX = 1; //idx para adicionar se for igual

    most_freq_symbols[0] = 0;

   for (int mostFreqIdx = 0; mostFreqIdx < asciiLetterIdx; mostFreqIdx++) {
    
        if (asciiNumberOfOccurrences[most_freq_symbols[0]] < asciiNumberOfOccurrences[mostFreqIdx]) {
            most_freq_symbols[0] = mostFreqIdx;
            most_freq_symbols_IDX = 1;
        }
        else if (asciiNumberOfOccurrences[most_freq_symbols[0]] == asciiNumberOfOccurrences[mostFreqIdx]) {
            most_freq_symbols[most_freq_symbols_IDX] = mostFreqIdx;
            most_freq_symbols_IDX++;
        }

    }

   if(most_freq_symbols_IDX==1){
    //printf("%c \n", asciiLetter[most_freq_symbols[0]]);
    return asciiLetter[most_freq_symbols[0]];
   }
   else{
    //printf("More than one symbol had the most frequency on given file");
    return asciiLetter[most_freq_symbols[0]];
   }

}

void teste_most_freq_symb(){
    
    char teste1 = most_frequent_symbol("teste1.txt");
    
    if(teste1!='3') printf("valor esperado: '3' -> valor recebido: %c \n", teste1);
    else printf("most_freq_symb de teste1.txt passado \n");

    char teste2 = most_frequent_symbol("teste2.txt");

    if(teste2!='a') printf("valor esperado: 'a' -> valor recebido: %c \n", teste2);
    else printf("most_freq_symb de teste2.txt passado \n");

}

////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

void negative_file( char *input_file_name, char *output_file_name) {
    //LEITURA DO FICHEIRO
    FILE *fp;
    fp = fopen(input_file_name, "rb");
    if (fp == NULL){
      perror("Error while opening the file.\n");
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

void teste_negative_file(){
    //os ficheiros devem alterar entre si entre negado e nao negado
    negative_file("teste_neg.txt", "teste_neg.txt");
    negative_file("teste2_neg.txt", "teste2_neg.txt");
}


int main() {
    testCountOnes();
    testCountOnes();
    teste_print_bits();
    teste_most_freq_symb();
    teste_negative_file();
    return 0;
}