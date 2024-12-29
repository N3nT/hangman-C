#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void write_hangman(const char **hangman, int count);
void select_word(char *word); //select word from file
void write_board(char *word, char *quessed); //swaps letters with '_'
char *create_guessed_letters(char *word); //malloc for guessed letters
void check_letters(char *word, char *guessed, int *wrong_attempts);
void check_win(char *word, char *guessed_letters, char *answer);

int main(void) {
    const char *hangman[] = {"|----|\n", " |    |\n", " |    O\n", " |   /|\\\n", " |   / \\ \n"};
    char word[20], answer[20];
    int play = 1;
    srand(time(NULL));
    while(play == 1) {
        int wrong_attempts = 0;
        select_word(word);
        strcpy(answer, word);
        char *guessed_letters = create_guessed_letters(word);
        while (wrong_attempts <= 4) {
            if(wrong_attempts > 0) {
                write_hangman(hangman, wrong_attempts-1);
            }
            write_board(word, guessed_letters);
            check_letters(word, guessed_letters, &wrong_attempts);
            check_win(word, guessed_letters, answer);
        }
        write_hangman(hangman, 4);
        printf("\nYou lost!\n");
        printf("The answer was: %s", answer);
        free(guessed_letters);
        printf("Do you want play again? (1-Yes, 2-No):");
        scanf("%d", &play);
    }
    printf("Thanks for playing!");
}

void write_hangman(const char **hangman, int count) {
    for (int i = 0; i <= count; i++) {
        printf("%s", hangman[i]);
    }
}

void write_board(char *word, char *guessed) {
    printf("\n");
    for (int i = 0; i < strlen(word) - 1; i++) {
        if (word[i] == '*') {
            printf("%c", guessed[i]);
        } else printf("_ ");
    }
    printf("\n");
}

char *create_guessed_letters(char *word) {
    int len = strlen(word);
    return (char *)malloc(len * sizeof(char)); //not adding 1 bsc word include '/0'
}

void check_letters(char *word, char *guessed, int *wrong_attempts) {
    int len = strlen(word);
    int flag = 0, i = 0;
    char attempt;
    printf("Enter a letter: ");
    scanf(" %c", &attempt);
    while (getchar() != '\n');
    for(i = 0; i < len - 1; i++) {
        if(attempt == word[i]) {
            flag = 1;
            break;
        }
    }
    if(flag) {
        guessed[i] = attempt;
        word[i] = '*';
    } else {
        *wrong_attempts += 1;
    }
}

void check_win(char *word, char *guessed_letters, char *answer) {
    int len = strlen(word);
    int win = 1; //assumption: game is won
    for (int i = 0; i < len-1; i++) {
        if(word[i] != '*') {
            win = 0; //if there is any letter game is not won yet
            break;
        }
    }
    if(win) {
        printf("%s\n", answer);
        printf("You win!\n");
        free(guessed_letters);
        exit(0);
    }
}

void select_word(char *word) {
    FILE *f = fopen("words.txt", "r");
    if (f == NULL) {//check if file is ok
        printf("File not found\n");
        exit(0);
    }
    char buffer[20];
    int current_line = 1;
    int target_line = rand() % 100 + 1;//random line 1-100
    while(fgets(buffer, 20, f) != NULL) {
        if(current_line == target_line) {
            strcpy(word, buffer);
            break;
        }
        current_line++;
    }
    fclose(f);
}