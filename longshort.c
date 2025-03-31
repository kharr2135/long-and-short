#include <stdio.h>

#define MAX_LINE_LENGTH 256

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input file> <short file> <long file>\n", argv[0]);
        return 1;
    }
    //pointers and use of fopen to work with the files
    FILE *inputFile = fopen(argv[1], "r");
    FILE *shortFile = fopen(argv[2], "w");
    FILE *longFile = fopen(argv[3], "w");

    if (!inputFile || !shortFile || !longFile) {
        printf("Error opening files.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int shortCount = 0, longCount = 0;

    while (fgets(line, sizeof(line), inputFile)) {
        int len = 0;
        while (line[len] != '\0' && line[len] != '\n') {
            len++;
        }

        if (line[len] == '\n') {
            line[len] = '\0';
        }

        if (len < 20) {
            for (int i = 0; i < len; i++) {
                if (line[i] >= 'a' && line[i] <= 'z') {
                    line[i] -= 32;
                }
            }
            fprintf(shortFile, "%s\n", line);
            shortCount++;
        } else {
            for (int i = 0; i < len; i++) {
                if (line[i] >= 'A' && line[i] <= 'Z') {
                    line[i] += 32;
                }
            }
            fprintf(longFile, "%s\n", line);
            longCount++;
        }
    }//fclose functions
    fclose(inputFile);
    fclose(shortFile);
    fclose(longFile);

    printf("%d lines written to %s\n", shortCount, argv[2]);
    printf("%d lines written to %s\n", longCount, argv[3]);
}
