#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signal) {
    if (signal == SIGHUP) {
        printf("Recibida señal SIGHUP\n");
        exit(0);
    } else if (signal == SIGTERM) {
        printf("Recibida señal SIGTERM\n");
        exit(0);
    }
}

int main() {
    // Registrar los manejadores de señales
    signal(SIGHUP, signal_handler);
    signal(SIGTERM, signal_handler);

    // Mantener el programa en ejecución para recibir señales
    while (1) {
        pause();
    }

    return 0;
}