#include "namedPipe.h"

void main(int argc, char *argv)
{
	int fdpub, fdpriv, fd;
	struct message msg;
	int n, i;
	char line[LINESIZE];

	mknod(PUBLIC, S_IFIFO|0666, 0);

	while(1)
	{
		if((fdpub=open(PUBLIC, O_RDONLY))==-1)
		{
			perror(PUBLIC);
			exit(1);
		}
		while(read(fdpub,(char *)&msg, sizeof(msg))>0)
		{
			if((fd=open(msg.filename, O_RDONLY))==-1)
			{
				perror(msg.filename);
				break;
			}
			for(i=0; i<NUMTRIES; i++)
			{
				if((fdpriv=open(msg.privfifo, O_WRONLY|O_NDELAY))==-1)
					sleep(1);
				else{
                    printf("[server] : %s named pipe open! \n", msg.privfifo);
					break;
                }
			}

			if(fdpriv==-1)
			{
				perror(msg.privfifo);
				break;
			}

            printf("[server] privfifo :  %s \n ", msg.privfifo );
            printf("[server] filename :  %s \n ", msg.filename );

			while((n=read(fd,line,LINESIZE))>0)
				write(fdpriv, line, n);

			close(fd);
			close(fdpriv);
		}
		close(fdpub);
	}
	
}

