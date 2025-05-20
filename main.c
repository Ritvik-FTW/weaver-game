#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_LEN 5
#define MAX_WORDS 1000

char dictionary[MAX_WORDS][WORD_LEN];
int wordCount = 0;

// Load dictionary from file
void loadDictionary(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening dictionary file");
        exit(1);
    }

    while (fscanf(file, "%s", dictionary[wordCount]) != EOF) {
        wordCount++;
    }
    fclose(file);
}

// Check if word is in dictionary
int isValidWord(const char *word) {
    for (int i = 0; i < wordCount; i++) {
        if (strcmp(dictionary[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

// Check if exactly one letter is different
int isOneLetterDiff(const char *word1, const char *word2) {
    int diff = 0;
    for (int i = 0; i < WORD_LEN - 1; i++) {
        if (word1[i] != word2[i]) {
            diff++;
        }
    }
    return diff == 1;
}

int main() {
    char start[WORD_LEN], target[WORD_LEN], input[WORD_LEN], current[WORD_LEN];

    loadDictionary("words.txt");

    printf("Enter the start word: ");
    scanf("%s", start);
    printf("Enter the target word: ");
    scanf("%s", target);

    if (!isValidWord(start) || !isValidWord(target)) {
        printf("Start or target word is not in the dictionary.\n");
        return 1;
    }

    strcpy(current, start);

    while (1) {
        printf("Current word: %s\n", current);
        printf("Enter next word: ");
        scanf("%s", input);

        if (!isValidWord(input)) {
            printf("Invalid word. Game over.\n");
            break;
        }

        if (!isOneLetterDiff(current, input)) {
            printf("Word must differ by exactly one letter. Game over.\n");
            break;
        }

        strcpy(current, input);

        if (strcmp(current, target) == 0) {
            printf("Congratulations! You reached the target word: %s\n", target);
            break;
        }
    }

    return 0;
}
