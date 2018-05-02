#include "myShell.h"
//#define DEBUG

int main(int argc, char **argv){
    char command[COMMAND_BUFFER];

    initPath(dir_path);

//    signal(SIGINT, SIG_IGN);
//    signal(SIGQUIT, SIG_IGN);

    while(1){
        write(1, "% ", 2);
        memset(command, 0, COMMAND_BUFFER);
        read(0, command, COMMAND_BUFFER-1);
        command[strlen(command)-1] = '\0'; // delete \n

#ifdef DEBUG
        printf("command : %s \n", command);
#endif
        memset(cmdList, 0x00, sizeof(COMMAND) * MAX_COMMAND);
        run(command); //run return value handle!!!!
        
    }

    return 0;
}

int run(char *command)//{{{
{
    int cmd_count, n, pid, pd[2], rpd[2];
    int in, out, next_in;

    if( ( cmd_count = tokenize(command, cmdList) ) == 0 )//return token count
        return 0;

    in = 0, out = 1, next_in = 0;
    for(n = 0; n < cmd_count; n++)
    {
        if(cmdList[n].tok[0] == NULL)
        {
            fprintf(stdout, "syntax error ! \n");
            continue;
        }

        if( specialCommand(cmdList[n].tok) == -1 )
        {  // setpath.. cd... exit
            perror("specialCommand: ");
            return -1;
        }

        if(next_in > 0)
        {
            in = next_in;

            if(cmdList[n-1].type == RD_R)
            {
                pipeTofile(in, cmdList[n].tok[0]);

                if (cmdList[n].type == RD_R)
                {
                    pipe(pd);
                    next_in = pd[0];
                    out = pd[1];

                    fileTopipe(cmdList[n].tok[0], out);
                }
                continue;
            }
        }
        else
            in = 0;

        switch(cmdList[n].type) 
        {
            case RD_L:
                continue;
            case RD_R:
            case PP :
                pipe(pd);
                next_in = pd[0];
                out = pd[1];
                break;

            default :
                out = 1;
                break;
        }

        if(cmdList[n-1].type == RD_L)
        {
            pipe(rpd);
            fileTopipe(cmdList[n].tok[0], rpd[1]);
            execute(&cmdList[n-1], rpd[0], out);
            continue;
        }
        
#ifdef DEBUG
        printf("******************************************************\n\n");
#endif
        execute(&cmdList[n], in, out);
    }

    return 0;
}//}}} 

int accessCheck(char *file_path){ //{{{ filename -> file path
    char filename[256];
    char **dir = dir_path;

    strcpy(filename, file_path); // filename copy

    while(*dir)
    {
        strcpy(file_path, *dir++);
        strcat(file_path, filename);

        if(access(file_path, 0) == 0) // access return value 0
            return 0;
    }

    return -1;
}//}}}

int setpath(char **path, char **cTok){ // {{{ cToken[0] == setpath 

    while(*++cTok){
        while(*path){path++;} //path null
        *path = malloc(strlen(*cTok)+2); // 2 => slash  require free!!!
        strcpy(*path, *cTok);

        //add slash
        if( *( (*path) + strlen(*path)-1 ) != '/')
            strcat(*path,"/");
#ifdef DEBUG
            printf("[setpath] : %s \n", *path);
#endif
    }

    return 0;
} //}}}

int initPath(char **path){//{{{
    char initFile[256], tmp[256];
    int tmpLen;
    FILE *fp;

    strcpy(initFile, getenv("HOME"));
    strcat(initFile, "/.myShellRc");

#ifdef DEBUG
    printf("[initPath] initFile : %s \n", initFile);
#endif

    if( (fp = fopen(initFile, "r"))  == NULL){
        fprintf(stderr, "init file open fail ! \n");
        return 1;
    }

    while( fgets(tmp, 256, fp) != NULL){
        tmpLen = strlen(tmp);
        
        tmp[ tmpLen - 1 ] = '\0';

        if(tmp[ tmpLen - 2 ] != '/')
            strcat(tmp, "/");

#ifdef DEBUG
        printf("[initPath] : %s \n", tmp);
#endif
        while(*path){path++;} //path null

        *path = malloc(tmpLen); 
        strcpy(*path, tmp);
    }

    return 0;
}//}}}

int tokenize(char *command, struct COMMAND_ *cmdList){///{{{
    int t_idx = 0, com_idx =0, delim_flag =1, cmd_count =0, tp_set=0, mark=0;

#ifdef DEBUG
    int i = 0, j;
#endif

    while( command[com_idx] && ( t_idx < MAX_TOKEN ) ){

        if(command[com_idx] == '\''){
            if(!mark)
                command[com_idx] = '\0'; 

            mark= mark ? 0 : 1;
        }

        if(!mark){
            switch(command[com_idx]){
                case '\'':
                    cmdList[cmd_count].tok[t_idx++] = &command[com_idx-1];
                    command[com_idx] = '\0';
                    delim_flag =0;
                    break;

                case '&':
                    cmdList[cmd_count].type = BG;
                    tp_set = 1;
                    break;

                case '|':
                    cmdList[cmd_count].type = PP;
                    tp_set = 1;
                    break;

                case '>':
                    cmdList[cmd_count].type =RD_R;
                    tp_set = 1;
                    break;

                case '<':
                    cmdList[cmd_count].type =RD_L;
                    tp_set =1;
                    break;

                case ';':
                    cmdList[cmd_count].type = NL;
                    tp_set = 1;
                    break;

                case ' ': 
                    delim_flag = 1;
                    command[com_idx] = '\0';
                    break;
                    
                default :
                    if (delim_flag){
                        cmdList[cmd_count].tok[t_idx++] = (command + com_idx);
                        delim_flag = 0;
                    }
                    break;
            }
        }

        if(tp_set)
        {
            cmdList[cmd_count++].tok[t_idx] = NULL;
            t_idx = 0;
            delim_flag = 1;
            command[com_idx] = '\0';
            tp_set=0;
        }
        com_idx++;
    }

    while( cmdList[cmd_count].tok[0] == NULL )
        cmd_count--;

#ifdef DEBUG
    int k=0;

    for(j = 0 ; j < cmd_count+1 ; i=0, j++){
        while( cmdList[j].tok[i] ){
            printf("[tokenize] cmd[%d][%d] : %s \t type : %d ASCII : %d \n", j, i, cmdList[j].tok[i++], cmdList[j].type, *cmdList[j].tok[i]);
        }
    }
    printf("cmd_count = %d \n\n",cmd_count +1);
#endif 

    return cmd_count+1 ;
}///}}}

int specialCommand(char **cTok){///{{{
        if(!strcmp("setpath", *cTok)) {
            setpath(dir_path, cTok);
            return 0;
        }

        else if(!strcmp("exit",*cTok))
            exit(-1);

        else if(!strcmp("cd",*cTok)){
            if( chdir(*(cTok + 1)) == -1)
                perror(*(cTok + 1));
            return 0;
        }
}///}}}

int execute(const struct COMMAND_ *cmd, int in, int out)///{{{
{
    int pid, status, n=1;
    char file_path[MAX_PATH];

    strcpy(file_path, cmd->tok[0]); //cToken[0] : filename -> file_path

    if( accessCheck(file_path) != 0)
    {
        fprintf(stdout, "not found! \n");
        return -1;
    }

    // execute
    if(( pid = fork())==0)
    {
        if(in != 0)
        {
            close(0);
            dup(in);
            close(in);
        }

        if(out != 1)
        {
            close(1);
            dup(out);
            close(out);
        }

        execv(file_path, cmd->tok);
        perror("execv : ");
        exit(127);
    }
    else
    {
        if( in != 0)
            close(in);

        if( out != 1)
            close(out);

        if( cmd->type != BG)
        {
            while(pid != waitpid(-1, &status, 0))
            {
                fprintf(stderr,"[complete] +%d\n",n++);
            }
        }
        else // background
            fprintf(stderr, "[%d] %d\n", n, pid);
    }
    return 0;
}
///}}}

int pipeTofile(int pd, const char *fn)
{
    int fd;
    char buf;

    if((fd =open(fn, O_CREAT|O_WRONLY, 0666))==-1) {
        perror("open : ");
        return -1;
    }

    while(read(pd, &buf, 1) > 0)
        write(fd, &buf, 1);

    close(pd); close(fd);

    return 0;
}

int fileTopipe(const char *fn, int pd)
{
    int fd;
    char buf;

    if((fd =open(fn, O_RDONLY))==-1) {
        perror("open : ");
        return -1;

    }

    while(read(fd, &buf, 1) > 0)
        write(pd, &buf, 1);

    close(fd); close(pd);

    return 0;
}
