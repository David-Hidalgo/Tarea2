#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1
#define N 2 /* number of processes */

const int MSG_SIZE = 100;

int main()
{
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Error creando pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        // Error al crear el proceso hijo
        perror("Error al crear el proceso hijo");
        return 1;
    } else if (pid == 0) {
        // Proceso hijo
        close(pipefd[0]); // Cierra el extremo de lectura
        write(pipefd[1], "\nHola desde el hijo!\n", 22);
        close(pipefd[1]);
    } else {
        // Proceso padre
        close(pipefd[1]); // Cierra el extremo de escritura
        char buffer[MSG_SIZE];
        read(pipefd[0], buffer, MSG_SIZE);
        printf(" \n El hijo dijo: \n");
        printf(buffer);
        close(pipefd[0]);
    }

    return 0;
}
