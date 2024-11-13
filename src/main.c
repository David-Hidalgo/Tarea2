#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1
#define N 2													/* number of processes */
int turn;													/* whose turn is it? */
int interested[N];											/* all values initially O(FALSE) */

void enter_region(int process)								/* process is 0 or 1 */
{
int other;													/* number of the Other process */
other = (1 - process);										/* the opposite of process */
interested[process] = TRUE;									/* show that you are interested */
turn = process;												/* set flag */
	while (turn == process && interested[other] == TRUE);	/* null statement */
};
void leave_region(int process)								/* indicate departure from critical region */
{
	interested[process] = FALSE;							/* process: who is leaving */
}

int main(int argc, char const *argv[])
{
	int arr[5]= {1, 2, 3, 4, 5};					// mi recurso "compartido"
	pid_t pid = fork();								// creo un proceso hijo
	if (pid < 0)
	{
		printf("Fork Failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		enter_region(1);
		for (int i = 0; i < 5; i++)
		{
			printf("Child Process: %d\n", arr[i]);
		}
		leave_region(1);
	}
	else
	{
		enter_region(0);
		for (int i = 0; i < 5; i++)
		{
			printf("Parent Process: %d\n", arr[i]);
		}
		leave_region(0);
	}
	return 0;
}
