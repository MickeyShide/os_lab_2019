#include <stdlib.h>

int main(int argc, char **argv) {
    printf("Running sequential_min_max\n");
    int pid = fork();
    if (pid == 0) {
        execv("./sequential_min_max", argv);
    } else {
        wait(NULL);
        printf("sequential_min_max has finished running.\n");
    }
    return 0;
}