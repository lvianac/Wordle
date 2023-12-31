#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

// user-defined function prototypes
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);

int main(int argc, string argv[])
{
    // ensure proper usage
    // TODO #1
    if (argc != 2)
    {
        printf("wordsize\n");
        return 1;
    }

    int wordsize = 0;

    // ensure argv[1] is either 5, 6, 7, or 8 and store that value in wordsize instead
    // TODO #2

    if (strcmp(argv[1], "5") == 0 || strcmp(argv[1], "6") == 0 || strcmp(argv[1], "7") == 0 || strcmp(argv[1], "8") == 0)
    {
        wordsize = atoi(argv[1]);
    }

    else
    {
        printf("Error: wordsize must be either 5, 6, 7, or 8\n");
        return 1;
    }

    // open correct file, each file has exactly LISTSIZE words
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    // load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // pseudorandomly select a word for this game
    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // print greeting, using ANSI color codes to demonstrate
    printf(GREEN"This is WORDLE50"RESET"\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    // main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // obtain user's guess
        string guess = get_guess(wordsize);

        // array to hold guess status, initially set to zero
        int status[wordsize];

        // set all elements of status array initially to 0, aka WRONG
        // TODO #4
        for (int st = 0; st < wordsize; st++)
        {
            status[st] = 0;
        }

        // Calculate score for the guess
        int score = check_word(guess, wordsize, status, choice);

        printf("Guess %i: ", i + 1);

        // Print the guess
        print_word(guess, wordsize, status);

        // if they guessed it exactly right, set terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }

    // Print the game's result
    // TODO #7

    if (won == true){
        printf("You won!\n");
    }

    else
    {
        printf("You lose!, the target word was: %s\n", choice);
    }

    // that's all folks!
    return 0;
}

string get_guess(int wordsize)
{
    string guess = "";
    // ensure users actually provide a guess that is the correct length
    // TODO #3
    do
    {
        guess = get_string("Input a %d-letter word:",wordsize);
    }
    while (strlen(guess)!=wordsize );

    //changing Uppercase to lowercase
    for (int letter = 0; letter < wordsize; letter++)
    {
        if (!islower(guess[letter]))
        {
            guess[letter] = tolower(guess[letter]);
        }
    }
    return guess;
}

int check_word(string guess, int wordsize, int status[], string choice)
{
    int score = 0;
    printf("%s ", choice);

    // compare guess to choice and score points as appropriate, storing points in status
    // TODO #5
    for (int cl = 0; cl < wordsize; cl++)
    {

        if (choice[cl] == guess[cl])
        {
            //printf("La letra se encuentra en posicion %c %c\n", choice[cl], guess[cl]);
            score+=EXACT;
            status[cl] = EXACT;
        }

        else
        {   for (int gl = 0; gl < wordsize; gl++)
            {
                if (choice[cl] == guess[gl])
                {
                    //printf("La letra se encuentra en la palabra %c %c\n", choice[cl], guess[gl]);
                    score+=CLOSE;
                    status[gl] = CLOSE;
                }
            }
        }
    }

    //printf("score %d\n", score);
    return score;
}

void print_word(string guess, int wordsize, int status[])
{
    // print word character-for-character with correct color coding, then reset terminal font to normal
    // TODO #6
    //printf("%i %i %i %i %i \n", status[0], status[1], status[2], status[3], status[4]);

    for (int c = 0; c < wordsize; c++)
    {
        if (status[c] == 2)
        {

            printf(GREEN"%c"RESET,guess[c]);
        }

        else if (status[c] == 1)
        {
            printf(YELLOW"%c"RESET,guess[c]);
        }

        else
        {
            printf(RED"%c"RESET,guess[c]);
        }

    }

    printf("\n");
    return;
}
