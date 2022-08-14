#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);
    printf("Score 1: ");
    printf("%i\n", score1);
    printf("Score 2: ");
    printf("%i\n", score2);

    // TODO: Print the winner
    if (score1 > score2) {
        printf("Player 1 is the winner!\n");
    } else if (score1 < score2) {
        printf("Player 2 is the winner!\n");
    } else {
        printf("Both Players are tied!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int counter = 0;
    for (int i = 0, n = strlen(word); i < n; i++) {
        if(isupper(word[i])) {
            int upper = 65;
            int  upperPos = 0;
            while ((int)word[i] != upper) {
                upper++;
                upperPos++;
            }
            counter = counter + POINTS[upperPos];
            // printf("UPPER POINT: ");
            // printf("%i\n", counter);
            // printf("upper ");
            // printf("%c\n", word[i]);
        } else if(islower(word[i])) {
            int lower = 97;
            int  lowerPos = 0;
            while ((int)word[i] != lower) {
                lower++;
                lowerPos++;
            }
            counter = counter + POINTS[lowerPos];
            // printf("LOWER POINT: ");
            // printf("%i\n", counter);
            // printf("lower ");
            // printf("%c\n", word[i]);
        } else {
            counter = counter + 0;
            // printf("special ");
            // printf("%c\n", word[i]);
        }

    }
    return counter;
}

//Loop through string -> done
//Loop through ASCII characters

// You may find the functions isupper() and islower() to be helpful to you.
// These functions take in a character as the argument and return a boolean.

// To find the value at the nth index of an array called arr, we can write arr[n].
// We can apply this to strings as well, as strings are arrays of characters.

// Recall that computers represent characters using ASCII, a standard that represents each character as a number.
