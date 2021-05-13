#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include "fila.h"
#define EVER ;;

typedef struct msgbuf
{
	long mtype;
	int msg;
} message_buf;

int main(void)
{
	int msqid, d, pid, pid_pai = get_pid(), *num_elem, *cont;
	int segmento, segmento2;
	key_t key;
	int msgflg = IPC_CREAT | 0666;
	message_buf rbuf, sbuf;
	size_t buf_length;

	segmento = shmget(7005, sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IROTH);
	segmento2 = shmget(7006, sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IROTH);
	cont = (int *)shmat(segmento, 0, 0);
	cont = (int *)shmat(segmento2, 0, 0);
	*cont = 0;
	*num_elem = 0;
	key = 2234;

	for (d = 0; d < 3; d++)
	{
		if ((pid = fork()) != 0)
		{

		}
	}

	if (pid == 0)
	{
		while(*cont <= 128)
		{
			// sender
			if (get_pid() == pid_pai + 1 && num_elem <= 32)
			{
				(void)fprintf(stderr, "\nmsgget: Calling msgget(%#1x,\%#o)\n", key, msgflg);

				if ((msqid = msgget(key, msgflg)) < 0)
				{
					perror("msgget");
					exit(1);
				}
				else
					(void)fprintf(stderr, "msgget: msgget succeeded: msgqid = %d\n", msqid);

				// We'll send message type 1
				sbuf.mtype = 1;
				(void)fprintf(stderr, "msggeet: msgget succeeded: msqid = %d\n", msqid);
				//(void)strcpy(sbuf.msg, "Did you get this?");
				sbuf.msg = 1;
				(void)fprintf(stderr, "msgget: msgget succeeded: msqid = %d\n", msqid);

				//buf_length = strlen(sbuf.msg) + 1;

				// Send a message.
				if ((msgsnd(msqid, &sbuf, sizeof(int), IPC_NOWAIT)) < 0)
				{
					printf("%d, %d, %d, %d\n", msqid, sbuf.mtype, sbuf.msg, buf_length);
					perror("msgsnd");
					exit(1);
				}
				else
					printf("Message: \"%d\" Sent\n", sbuf.msg);

				(*num_elem) ++;
			} //receiver
			else
			{
				if ((msqid = msgget(key, 0666)) < 0)
				{
					perror("msgget");
					exit(1);
				}
				// Receive an answer of message type 1.
				if (msgrcv(msqid, &rbuf, sizeof(int), 1, 0) < 0)
				{
					perror("msgrcv");
					exit(1);
				}

				printf("^%d\n", rbuf.msg);
				(*cont) ++;
				(*num_elem) --;
				if(get_pid() == pid_pai + 2)
					sleep(2);
			}
			sleep(1);
		}
	}

	shmdt(cont);
	shmdt(num_elem);
	shmctl(segmento,IPC_RMID,0);
	shmctl(segmento2,IPC_RMID,0);
	return 0;
}