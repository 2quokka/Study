#include "namedPipe.h"
#include <string.h>

void main(int argc, char *argv[])
{
	struct message msg;
	int n;
	int fdpub, fdpriv;
	char line[LINESIZE];

	sprintf(msg.privfifo, "Fifo%d", getpid());
	if(mknod(msg.privfifo, S_IFIFO|0666, 0)==-1)
	{
		perror(msg.privfifo);
		exit(1);
	}
	
	if((fdpub=open(PUBLIC, O_WRONLY))==-1)
	{
		perror(PUBLIC);
		exit(2);
	}

	strcpy(msg.filename, argv[1]);

    printf("[client] msg privfifo : %s \n ", msg.privfifo);
    printf("[client] msg filename : %s \n ", msg.filename);

	write(fdpub, (char *)&msg, sizeof(msg));

	if((fdpriv=open(msg.privfifo, O_RDONLY))==-1)
	{
		perror(msg.privfifo);
		exit(3);
	}

	while((n=read(fdpriv, line, LINESIZE))>0)
		write(1, line, n);

	close(fdpriv);
	unlink(msg.privfifo);
	exit(0);
}

