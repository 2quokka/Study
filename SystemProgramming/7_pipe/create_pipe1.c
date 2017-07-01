#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_SIZE 50

void main()
{
	int send_fd[2], rcv_fd[2], pid=0, size=0;
	char send_buf[MAX_SIZE], rcv_buf[MAX_SIZE];

	memset(send_buf, 0x00, MAX_SIZE);
	memset(rcv_buf, 0x00, MAX_SIZE);

	if( pipe(send_fd) == -1)
	{
		perror("pipe() : ");
		exit(1);
	}

	if(pipe(rcv_fd)==-1)
	{
		perror("pipe() : "); 
		exit(2);
	}

	if( (pid=fork()) ==0 )
	{
		close(send_fd[1]); //close send write
		close(rcv_fd[0]);  //close receive read 
		size = read(send_fd[0], rcv_buf, MAX_SIZE);
		printf("\t[Child] : Receive Message : %s\n", rcv_buf);
		write(rcv_fd[1], rcv_buf, size);
		printf("\t[Child] : Send Message : %s\n", rcv_buf);
		exit(0);
	}
	else if( pid > 0 )
	{
		close(send_fd[0]); //close send read
		close(rcv_fd[1]);  //close receive write
		size = read(0,send_buf,MAX_SIZE);
		write(send_fd[1], send_buf, size);
		printf("[Parent] : Send Message : %s\n",send_buf);
		read(rcv_fd[0], rcv_buf, MAX_SIZE);
		printf("[Parent] : Receive Message : %s\n",rcv_buf);
	}

	exit(0);
}
						
