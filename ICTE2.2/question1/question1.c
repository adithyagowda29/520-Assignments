#include <stdio.h>
#include <string.h>

int main() {
    char input_str[20];
    char *p;
    int vowels_count, consonants_count;
    vowels_count = consonants_count = 0;

    //Inputting a string from user
    printf("Input a string: ");
    gets(input_str);

    p = input_str;

    //Iterating through string using pointer
    while (*p != '\0') {
        //Counting vowels one by one
        if (*p == 'a' || *p == 'e' || *p == 'i' || *p == 'o' || *p == 'u' || 
            *p == 'A' || *p == 'E' || *p == 'I' || *p == 'O' || *p == 'U') {
            vowels_count++;
        } 
        //Counting consonants one by one
        else if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z')) {
            consonants_count++;
        }

        p++;
    }

    //Printing result of number of vowels and consonants
    printf("Number of vowels: %d\n", vowels_count);
    printf("Number of consonants: %d\n", consonants_count);

    return 0;
}