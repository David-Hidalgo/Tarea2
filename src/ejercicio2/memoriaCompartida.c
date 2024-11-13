#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    // Clave única para identificar la región de memoria compartida
    key_t key = ftok("shmfile", 65);

    // Tamaño de la región de memoria
    int shmsize = 1024;



    // Crear la región de memoria compartida
    int shmid = shmget(key, shmsize, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

	pid_t pid = fork();

	if (pid<0)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
		/* code */
	}else if(pid==0){
		// Conectar a la región de memoria compartida
		char *str = (char*)shmat(shmid, NULL, 0);
		if (str == (char *) -1) {
			perror("shmat");
			exit(1);
		}
		// Escribir en la memoria compartida
		strcpy(str, "Hola desde el proceso 1");
		shmdt(str);
	}else{
		// Conectar a la región de memoria compartida
		char *str = (char*)shmat(shmid, NULL, 0);
		if (str == (char *) -1) {
			perror("shmat");
			exit(1);
		}
		wait(NULL);
		printf("Proceso padre recibió: %s\n", str);
		shmdt(str);
		// Eliminar la región de memoria compartida
		shmctl(shmid, IPC_RMID, NULL);
	}
	

/*     // Conectar a la región de memoria compartida
    char *str = (char*)shmat(shmid, NULL, 0);
    if (str == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Escribir en la memoria compartida
    strcpy(str, "Hola desde el proceso 1");

    // Desconectar la memoria compartida
    shmdt(str);

 */
    // Eliminar la región de memoria compartida
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}