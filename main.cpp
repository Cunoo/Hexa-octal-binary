/*
Riešte problém na výpočet súčtu členov postupnosti čísel. Počet členov postupnosti nie je dopredu známy,
 končí sa stlačením tlačidla ESC. Daný súčet podľa voľby užívateľa potom môže program previesť buď do:
    • Binárnej sústavy
    • Osmičkovej sústavy
    • Šestnástkovej sústavy

*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//v ascii tabulke ma escape id 27
//#define esc 27

//const for size array
const int SIZE = 32;
///const for END program
const char END = 'k';


bool isNumber(const char isnum[]);
void hexadecimal(int h_number, int op);
char *allocate(int size);
void printing(int number[]);

void binary(int b_number, int op);
//octal
int convertDecimalToOctal(int decimalNumber, int op);

//GLObal variables
//int count_b = 0;
//int count_o = 0;

int main(void){

    char *input = NULL;
    input = allocate(SIZE);
    int result = 0;
    char choice[2];
    char choice_continue[2];
    char negative;


    printf("Tento program ti umozni previest rozne cislo do binarnej, osmickovej a 16stnastkovej sustavy\n Zadavaj postupnost a zadavanie ukoncis tlacidlom escape (musis potvrdit vstupy z enterom) \n");

    do {
        printf("Zadaj cislo: ");

        scanf(" %s", input);
        
        //meranie prevodu cisiel
        clock_t start = clock();

        if(strlen(input) > SIZE){
            printf("Zadal si vacsie cislo ako je dovolene vypinam program\n");
            exit(1);

        }

        if(*input == END){
            printf("Zadal si escape ukoncujem postupnost\n");
        }
        
        
        else if(input[0] == '-'){
            if(isNumber(input)){
                result += atoi(input);
            }
            negative = '-';
        }
        /*if(input[0] != '-'){
            if(isNumber(input));
                result += atoi(input);
        
        }*/
        else if (isNumber(input)){
            result += atoi(input);
            //printf("spocitane cislo je :%ld \n", result);
       }

        clock_t end = clock();
        double elapsed = (double(end - start)/CLOCKS_PER_SEC);
        printf("Meranie prevodu: %f seconds.\n", elapsed);
    }while((*input != END));

    //rozpustenie retazca lebo nam uz neposluzi
    free(input);
    //free(input_negative_number);

    if(result == 0){
        printf("Tvoja postupnost je rovna 0 ukoncujem program\n");
        exit(0);
    } else{
        printf("Ukoncil si postupnost a cislo je %d \n", result);
    }

    while(1){

        printf("Co chces urobit ? Prevod do binarnej sustavy(1), Osmickovej(2) alebo sestnastkovej(3)?\n alebo do vsetkych naraz (4)? Ak chces hned ukoncit program stlac (q) \n");
        scanf("%s", choice);

            //binary(result,0);
        clock_t start = clock();


        switch(*choice){

            case 'q':
                exit(0);
            case 'Q':
                exit(0);
            case '1':
                if(negative == '-'){
                    printf("Tvoje cislo v binarnej sustave je : ");
                    printf("%c", negative);
                    binary(abs(result),2);
                } else{
                    printf("Tvoje cislo v binarnej sustave je : ");
                    binary(result,2);

                }
                //binary(result);
                break;
            case '2':
                if(negative == '-'){
                    printf("Tvoje cislo v osmickovej sustave je : %c%d \n", negative, convertDecimalToOctal(abs(result), 8));
                    //printf("%d\n", convertDecimalToOctal(abs(result), 8));
                } else{
                    printf("Tvoje cislo v osmickovej sustave je : %d\n", convertDecimalToOctal(result, 8));
                }
                //octal(result);
                break;
            case '3':
                //printf("Tvoje cislo v 16stnaskovej sustave je : ");
                if(negative == '-'){
                    printf("Tvoje cislo v 16stnaskovej sustave je : ");
                    printf("%c", negative);
                    hexadecimal(abs(result), 16);

                } else{
                    printf("Tvoje cislo v 16stnaskovej sustave je : ");
                    hexadecimal(result,16);
                }
                break;
            case '4':
                if(negative == '-'){ 
                    printf("tvoje cislo v binarnej sustave je : %c", negative);
                    binary(abs(result),2);
                    printf("tvoje cislo v osmickovej sustave je : %c", negative);
                    convertDecimalToOctal(abs(result), 8);
                    printf("Tvoje cislo v 16stnaskovej sustave je : %c", negative);
                    hexadecimal(abs(result),16);
                } else{
                    printf("tvoje cislo v binarnej sustave je : ");
                    binary(result,2);
                    printf("tvoje cislo v osmickovej sustave je : ");
                    convertDecimalToOctal(result, 8);
                    printf("tvoje cislo v 16stnastkovej sustave je : ");
                    hexadecimal(result,16);
                }
                break;
            default:
                printf("Nespravny vyber! \n");
                continue;
        }
    /*clock_t end = clock();
        double elapsed = (double(end - start)/CLOCKS_PER_SEC);
        printf("(cas pri prevode cisla: %f seconds.\n", elapsed);*/
        //GOTO FUNCTION
        MENU:
        printf("Chces previest cislo do inej sustavy ? ano (Y) alebo nie ? (N)\n");
        scanf(" %s", choice_continue);

        /*if((choice_continue == 'Y') || (choice_continue == 'y'))
            continue;
        else if ((choice_continue == 'N') || (choice_continue == 'n'))
        {
            printf("Ukoncujem program..\n");
            return 0;
        } else {
            printf("zadal si zly vyber prosim opakuj\n");
            //GOTO FUNCTION
            goto MENU;
        }*/

        switch (*choice_continue){
            case 'Y':
            case 'y':
                continue;
            case 'n':
            case 'N':
            case 'q':
            case 'Q':
               printf("Ukoncujem program..\n");
                exit(0);
            default:
                printf("zadal si zly vyber prosim opakuj\n");
                //GOTO FUNCTION
                goto MENU;

        }

    }

    return 0;
}

//kontrola retazca ci je cislo
bool isNumber(const char isnum[]) {
    //ak isnum[0] je "-" tak i bude 1 a zacne znak po znaku kontrolovat
    int i = isnum[0] == '-' ? 1 : 0;
    
    //ak isnum[0] je rovne len znaku '-' vrati chybu false
    bool isANumber = false;

    for(; isnum[i] != '\0'; ++i){
        if(isdigit(isnum[i]) == false){
            printf("Zadali ste v retazci pismeno alebo znak\n");
            return false;
        }
        isANumber = true;
    }

    if(isANumber == false)
        printf("Zadali ste v retazci pismeno alebo znak\n");

    return isANumber;
}

void binary(int b_number, int op){

    //meranie binarnej funkcie
    clock_t start = clock();
    int i = 0;
    int binary_num[SIZE];
    while (b_number != 0){
        binary_num[i++] = b_number % op;
        b_number /= op;
        
    }
    
    for(int j = i-1; j >= 0; j--){
        printf("%d", binary_num[j]);

        
        //printf("%d", binary_num[j]);
    }
    
    printf("\n");
    clock_t end = clock();
    double elapsed = (double(end - start)/CLOCKS_PER_SEC);
    printf("cas pri prevode binarneho cisla: %f seconds.\n", elapsed);
}

int convertDecimalToOctal(int decimalNumber, int op)
{
    clock_t start = clock();
    int octalNumber = 0, i = 1;

    while (decimalNumber != 0)
    {
        octalNumber += (decimalNumber % op) * i;
        decimalNumber /= op;
        i *= 10;
    }

    clock_t end = clock();
    double elapsed = (double(end - start)/CLOCKS_PER_SEC);
    printf("\ncas pri prevode do osmickovej sustavy (programiz): %f seconds.\n", elapsed);

    return octalNumber;
}

void hexadecimal(int h_number, int op){

    int hexadecimal_num[SIZE];
    int i = 0;

    while (h_number != 0){

        switch(h_number % op){
            case 10: hexadecimal_num[i++] = 'A'; break;
            case 11: hexadecimal_num[i++] = 'B'; break;
            case 12: hexadecimal_num[i++] = 'C'; break;
            case 13: hexadecimal_num[i++] = 'D'; break;
            case 14: hexadecimal_num[i++] = 'E'; break;
            case 15: hexadecimal_num[i++] = 'F'; break;
            default:

            // 0x30 nepouziva 10 cisiel ale 16 a keby sme pouzili na miesto 0x30 48 na tom nezalezi
                hexadecimal_num[i++] = (h_number % op) + 0x30;
                //break;
        }
        h_number = h_number / op;
    }
    //nacitanie retazca odzadu
    for(int j = i -1; j >= 0; j--){
        printf("%c", hexadecimal_num[j]);
    }

    printf("\n");

}



char *allocate(int size){

    char *ptr = (char*)calloc(size, sizeof(char));
    if(!ptr)
        printf("failed to allocate memory\n");

    return ptr;

}


/*
bool special_character(char str){
    char special[30] = {'~','@','#','$','%','^','&','*', '(', ')', '_', '-', '=', '+',
                        '{', '[', ']', '}', '\'', '|', ';', ':', '"', ',', '<', '>', '.',
                        '?', '/', '`'};
    for(int j = 0; j < 1; j++){
        for(int i = j; i <= strlen(special); i++){
            if(special[i] == 1){
                printf("zadali ste v retazci znak !\n");
                return false;

            }
        }
    }
    return true;
}*/


/*void func_strcpy(char *source, char* destination){
    char temp[SIZE] = {'\0'};
    int  index = 1;

    while (destination[index] != '\0')
    {
        source[index] = destination[index];
        index++;
    }

    for (index = 0; index < SIZE; index++)
    {
        source[index] = '\0';
    }
}*/

/*
void printing(int number, int decision){
    int help;
    int array_numbers[SIZE];
    int i = 0;
    if (decision == 1){
        help = 2;
        while (number != 0){
        array_numbers[i++] = number % 2;
        number /= 2;
        }
        for(int j = i -1; j >= 0; j--){
        printf("%d", octal_num[j]);
    }
    }
    i = 0;
    if (decision == 2){
        while (number != 0){
            array_numbers[i++] = o_number % 8;
            o_number /= 8;
        }
        for(int j = i -1; j >= 0; j--){
        printf("%d", octal_num[j]);
    }
}*/


/////////STATIC METHOD
/*
void printing(int number[]){
    int i = 0;
    while(number[i] != 0){
        i++;
    }

    for(int j = i-1; j > 0; j--){
    printf("%d", abs(number[j]));

        
        //printf("%d", binary_num[j]);
    }
}

int *binary(int b_number){
    int i = 0;
    static int binary_num[SIZE];
    while (b_number != 0){
        binary_num[i++] = b_number % 2;
        b_number /= 2;
    }

    
    
    for(int j = i-1; j > 0; j--){
        printf("%d", abs(binary_num[j]));

        
        //printf("%d", binary_num[j]);
    }
    printf("\n");
    return binary_num;
}*/
