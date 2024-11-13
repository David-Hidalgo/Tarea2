#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MSG_SIZE 100

struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    key_t key;
    int msgid;
    pid_t pid;

    // Crear una clave única
    key = ftok("progfile", 65);

    // Crear una cola de mensajes
	// 1leer
	// 2escribir
	// 3ejecutar
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }else

    if (pid == 0) { // Proceso hijo
        struct msg_buffer message;
        // Recibir el mensaje
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        printf("Proceso hijo recibió: %s\n", message.msg_text);
    } else { // Proceso padre
        struct msg_buffer message;
        message.msg_type = 1;
        strcpy(message.msg_text, "Hola desde el proceso padre");
        // Enviar el mensaje
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
		wait(NULL); //esperar a que el hijo termine
        // Eliminar la cola de mensajes
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}