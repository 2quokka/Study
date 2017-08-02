#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAXARGS	128

#define IO_REDIRECT(d, r)	{close(d); dup(r); close(r);}

const char *path[3]={"/bin", "/usr/bin", NULL};
char *v[MAXARGS];

int make_vector(const char *cmd, char *op, char **nextp)
{
	int i, n, r, quoting;
	char arg[BUFSIZ];

	memset(arg, 0, sizeof(arg));
	for(r=0, i=0, n=0, quoting=0; cmd[i]; i++)
	{
		if(cmd[i]=='\'')
			quoting=(quoting)?0:1;
		else if(quoting	==0 && cmd[i]=='|')
			break;
		else if(quoting==0 && cmd[i]==' ')
		{
			if(n==0)
				continue;

			v[r++]=strndup(arg, n);
			memset(arg, 0, sizeof(arg));
			n=0;
		}
		else
			arg[n++]=cmd[i];
	}

	if(quoting!=0)
		return 0;

	if(n>0)
		v[r++]=strndup(arg, n);

	v[r]=NULL;

	*op=cmd[i];
	*nextp=(char*)cmd+i+1;

	return r;
}

pid_t make_cmd(const int ind, const int outd)
{
	pid_t pid=0;
	int i, notfound=1;
	char pname[BUFSIZ];

	memset(pname, 0, sizeof(pname));

	if( *(v[0])=='/' || *(v[0])=='.' )
	{
		if((notfound=access(v[0], F_OK))==0)
			strcpy(pname, v[0]);
	}
	else
	{
		for(i=0 ;path[i];i++)
		{
			memset(pname, 0, sizeof(pname));
			sprintf(pname, "%s/%s", path[i], v[0]);
			if((notfound=access(pname, F_OK))==0)
				break;
		}
	}

	if(notfound)
		goto cmd_exit;

	if((pid=fork())==0)
	{
		if(ind!=0)
			IO_REDIRECT(0, ind);

		if(outd!=1)
			IO_REDIRECT(1, outd);

		execv(pname, v);
		perror("execv()");
		exit(3);
	}

	if(ind!=0)
		close(ind);

	if(outd!=1)
		close(outd);

cmd_exit:

	for(i=0; v[i]; i++)
		free(v[i]);

	return pid;
}

void main()
{
	int pd[2], ind, outd, next_ind;
	ssize_t len;
	pid_t pid, w;
	char in[BUFSIZ], op, *cmd, *next_cmd;

	while(1)
	{
		write(1, "% ", 2);
		memset(in, 0, sizeof(in));
		if((len=read(0, in, sizeof(in)))==-1)
			perror("read()"), exit(1);

		if(len==0)
			write(1, "exit\n", 5), exit(0);

		if(in[len-1]=='\n')
		{
			if(--len==0)
				continue;
			in[len]='\0';
		}

		cmd=in, ind=0, outd=1, next_ind=0;
		while(make_vector(cmd, &op, &next_cmd)>0)
		{
			if(next_ind>0)
				ind=next_ind;

			switch(op)
			{
				case '|':
					if(pipe(pd)==-1)
					{
						perror("pipe()");
						exit(2);
					}

					outd=pd[1];
					next_ind=pd[0];
					break;

				case '\0': 
					outd=1;
					break;
			}

			if((pid=make_cmd(ind, outd))==0)
			{
				fprintf(stderr, "command not found.\n");
				break;;
			}
			cmd=next_cmd;
		}
		while((w=wait(NULL))!=pid && w!=-1);
	}
	/* UNREACHED */
}
