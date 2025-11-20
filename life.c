#include <stdio.h>
#define MAXSIZE 48

int read_size(void) {
    int size;
    printf("Read the boundary size: ");
    if (scanf("%d", &size) != 1) {
        printf("Invalid input.\n");
        return -1;
    }

    getchar(); // consume leftover newline from scanf

    if (size < 1 || size > MAXSIZE) {
        printf("Size must be between 1 and %d.\n", MAXSIZE);
        return -1;
    }
    return size;
}


void read_soc(int soc[][MAXSIZE], int size) {
    printf("Build the society.\n", size);

    for (int r = 0; r < size; r++) {
        char line[256];
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("Error reading line.\n");
        }

        int c_index = 0;
        for (int i = 0; line[i] != '\0' && c_index < size; i++) {
            if (line[i] == '*') {
                soc[r][c_index++] = 1;
            } else if (line[i] == '-') {
                soc[r][c_index++] = 0;
            } else {
                // ignore other characters
            }
        }

        if (c_index < size) {
            printf("Row too short. Filling remaining cells as dead.\n");
            while (c_index < size) {
                soc[r][c_index++] = 0;
            }
        }
    }
}

void prt_soc(int soc[][MAXSIZE], int size) {
    printf("New life:\n");
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            putchar(soc[r][c] ? '*' : '-');
        }
        putchar('\n');
    }

}

int main(void) {
    int size = read_size();
    if (size == -1) {
        return 1;
    }

    int grid[MAXSIZE][MAXSIZE] = {0};

    read_soc(grid, size);

    prt_soc(grid, size);

    return 0;
}