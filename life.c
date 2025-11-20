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

int read_evolutions(void) {
    int gen;
    printf("Enter number of evolutions: ");
    if (scanf("%d", &gen) != 1 || gen < 1) {
        printf("Invalid number of evolutions.\n");
        return 1;
    }

    getchar(); // consume leftover newline from scanf
    return gen;
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

    // Top border
    putchar('/');
    for (int c = 0; c < size; c++) {
        putchar('o');
        putchar('o');
    }
    putchar('o');
    putchar('\\');
    putchar('\n');

    // Middle with side borders
    for (int r = 0; r < size; r++) {
        putchar('|');
        putchar(' ');
        for (int c = 0; c < size; c++) {
            putchar(soc[r][c] ? '*' : '-');
            putchar(' ');
        }
        putchar('|');
        putchar('\n');
    }

    // Bottom border
    putchar('\\');
    for (int c = 0; c < size; c++) {
        putchar('o');
        putchar('o');
    }
    putchar('o');
    putchar('/');
    putchar('\n');
}


int population(int soc[][MAXSIZE], int size) {
    int count = 0;
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (soc[r][c] == 1) {
                count++;
            }
        }
    }
    printf("The number of inhabitants is: %d.\n", count);
    return count;
}

int destiny(int soc[][MAXSIZE], int row, int col) {
    int neighbors = 0;

    // Count live neighbors
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;

            int rr = row + dr;
            int cc = col + dc;

            if (rr >= 0 && rr < MAXSIZE && cc >= 0 && cc < MAXSIZE) {
                neighbors += soc[rr][cc];
            }
        }
    }

    // Apply Game of Life rules
    if (soc[row][col] == 1) {
        if (neighbors == 2 || neighbors == 3) return 1;
        else return 0;
    } else {
        if (neighbors == 3) return 1;
        else return 0;
    }
}

int evolve_soc(int soc[][MAXSIZE], int size) {
    int next[MAXSIZE][MAXSIZE] = {0};
    int changed = 0;

    // Compute next generation
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            next[r][c] = destiny(soc, r, c);
            if (next[r][c] != soc[r][c]) {
                changed = 1;
            }
        }
    }

    // Copy back into soc
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            soc[r][c] = next[r][c];
        }
    }

    return changed;
}

void generate(int soc[][MAXSIZE], int size, int gen) {
    int i;
    int changed = 0;
    for (i = 0; i < gen; i++) {
        changed = evolve_soc(soc, size);
        if (!changed) {
            break;
        }
    }
    prt_soc(soc, size);
    population(soc, size);
    if (changed)
        printf("Evolution continues after %d evolutions.\n", gen);
    else
        printf("The society stabilises at evolution %d.\n", i);
}

int main(void) {
    int size = read_size();
    if (size == -1) {
        return 1;
    }

    int grid[MAXSIZE][MAXSIZE] = {0};

    read_soc(grid, size);

    prt_soc(grid, size);
    population(grid, size);

    printf("\nAfter One Evolution:\n");
    evolve_soc(grid, size);
    prt_soc(grid, size);
    population(grid, size);

    int gen = read_evolutions();

    generate(grid, size, gen);

    return 0;
}