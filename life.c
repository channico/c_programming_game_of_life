#include <stdio.h>
#define MAXSIZE 48

int read_soc(void) {
    int size;
    printf("Read the boundary size: ");
    if (scanf("%d", &size) != 1) {
        printf("Invalid input.\n");
        return -1;
    }
    if (size < 1 || size > MAXSIZE) {
        printf("Size must be between 1 and %d.\n", MAXSIZE);
        return -1;
    }
    return size;
}

int main(void) {
    return 0;
}