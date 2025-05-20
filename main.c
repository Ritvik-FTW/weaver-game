#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORDS 10000
#define WORD_LENGTH 20

char dictionary[MAX_WORDS][WORD_LENGTH];
int totalWords = 0;

// Load dictionary from file
void loadDictionary(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Dictionary file error");
        exit(EXIT_FAILURE);
    }

    while (fscanf(fp, "%s", dictionary[totalWords]) == 1) {
        totalWords++;
    }

    fclose(fp);
}

// Check if word is in dictionary
int isWordValid(const char *word) {
    for (int i = 0; i < totalWords; i++) {
        if (strcmp(dictionary[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

// Check if words differ by exactly one letter
int isOneLetterDifference(const char *word1, const char *word2) {
    if (strlen(word1) != strlen(word2)) return 0;

    int diffCount = 0;
    for (int i = 0; word1[i] && word2[i]; i++) {
        if (tolower(word1[i]) != tolower(word2[i])) {
            diffCount++;
        }
    }
    return (diffCount == 1);
}

// Display UI header
void printBanner() {
    printf("======================================\n");
    printf("        WELCOME TO WEAVER GAME        \n");
    printf("======================================\n");
    printf("Change one letter at a time to reach\n");
    printf("the target word. Every word must be\n");
    printf("valid! Type 'exit' to quit early.\n\n");
}

// Start game loop
void playGame(const char *start, const char *target) {
    char current[WORD_LENGTH], next[WORD_LENGTH];
    int steps = 0;

    strcpy(current, start);

    printf("Starting word: %s\nTarget word: %s\n", start, target);

    while (1) {
        printf("\nStep %d - Current word: %s\nEnter next word: ", steps + 1, current);
        scanf("%s", next);

        if (strcmp(next, "exit") == 0) {
            printf("Game exited. Total steps: %d\n", steps);
            break;
        }

        if (!isWordValid(next)) {
            printf("❌ Invalid word. Must be in dictionary.\n");
            continue;
        }

        if (!isOneLetterDifference(current, next)) {
            printf("❌ Must change exactly one letter.\n");
            continue;
        }

        strcpy(current, next);
        steps++;

        if (strcmp(current, target) == 0) {
            printf("🎉 Success! You reached the target in %d steps.\n", steps);
            break;
        }
    }
}

// Main function
int main() {
    char start[WORD_LENGTH], target[WORD_LENGTH];

    loadDictionary("words.txt");
    printBanner();

    printf("Enter START word: ");
    scanf("%s", start);
    if (!isWordValid(start)) {
        printf("❌ '%s' is not in dictionary.\n", start);
        return 1;
    }

    printf("Enter TARGET word: ");
    scanf("%s", target);
    if (!isWordValid(target)) {
        printf("❌ '%s' is not in dictionary.\n", target);
        return 1;
    }

    if (strlen(start) != strlen(target)) {
        printf("❌ Words must be of the same length.\n");
        return 1;
    }

    playGame(start, target);

    return 0;
}
