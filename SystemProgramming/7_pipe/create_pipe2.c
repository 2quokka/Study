#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define MAX_SIZE 50

void main(int argc, char *argv[])
{
	int fd[2], pid=0, size=0;
	int status=0;
	char buf[MAX_SIZE];

	memset(buf,0x00,MAX_SIZE);
	if(pipe(fd) == -1)
	{
		perror("pipe() : ");
		exit(1);
	}
	
	if( (pid = fork()) == -1 )
	{
		perror("fork() 1 : ");
		exit(2);
	}
	else if(pid==0)
	{
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		size = read(0, buf, MAX_SIZE);
		execlp(buf,buf,(char *)NULL);
		printf("[Child_1] Receive Message : %s\n", buf);
		perror("execlp() : ");
		exit(3);
	}

	if( (pid = fork()) == -1)
	{
		perror("fork() 2 : ");
		exit(4);
	}
	else if( pid==0)
	{
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		printf("%s", argv[1]);
		fflush(stderr);
		exit(0);
	}

	close(fd[0]);
	close(fd[1]);
	while( wait(&status) != -1 )
		;
	exit(0);
}
