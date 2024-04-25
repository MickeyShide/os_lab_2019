#include <stdlib.h>
#include <stdio.h>

int main() {
    pid_t child_pid;
    child_pid = fork();
    if (child_pid > 0) {
        // родительский процесс - делаем паузу
        sleep(5);
    }
    else {
        // дочерний процесс - сразу выходим
        exit(0);
    }
    return 0;
}