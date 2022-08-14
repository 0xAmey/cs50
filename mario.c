#include <cs50.h>
#include <stdio.h>

void printPyramid(height) {
    for(int i = 0; i < height; i++ ) {
        for(int doti = height - i; doti > 0; doti--) {
            printf(" ");
        }
        for(int subi = 0; subi <= i; subi++) {
            printf("#");
        }
        printf("\n");
    }
}

int main(void)
{
    int height = get_int("height: ");
    if(height < 9 && height > 0)
    {
        printPyramid(height);
    }
    else
    {
        while (height > 8 || height < 1)
        {
            height = get_int("height: ");
        }
        printPyramid(height);
    }
}

//
