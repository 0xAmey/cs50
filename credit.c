#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long entryNum = get_long("Enter a Credit Card Number: ");
    int counter = 1;
    int sum1 = 0;
    int sum2 = 0;
    while (entryNum > 0)
    {
        int digit = entryNum % 10;

        if(counter % 2 == 0) {
            sum1 += digit*2;
            // printf("sum1: ");
            // printf("%i",sum1);
            // printf("\n");
        } else {
            sum2 += digit;
            // printf("sum2: ");
            // printf("%i", sum2);
            // printf("\n");
        }
        counter++;
        //printf("%i", digit);
        entryNum = entryNum / 10;
    }
    int final = sum1 + sum2;
    if (final % 10 == 0) {
        printf("Valid Credit Card");
        printf("\n");
    } else {
        printf("Invalid Credit Card");
        printf("\n");
    }
}

