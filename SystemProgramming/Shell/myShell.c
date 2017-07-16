// header file
#include <stdio.h>
#include <string.h> // strlen ..
#include <sys/types.h> //fork ...
#include <unistd.h>  // fork.. exec.. 
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h> //wait..
#include <signal.h>

#define DEBUG
#define COMMAND_BUFFER 1024
#define MAX_PATH 256
#define MAX_TOKEN 256

//type
#define BG 1
#define RD_R 2
#define RD_L 4

//function
int run(char *command);
int accessCheck(char **command_path, char* filename);
int setpath(char **path, char **cTok);
int initPath(char **path);
int tokenize(char *command, char *cToken[MAX_TOKEN][MAX_TOKEN]);
int specialCommand(char **cTok);

char *dir_path[MAX_PATH];
char *cToken[MAX_TOKEN][MAX_TOKEN];//3 matrix 
unsigned char state[MAX_TOKEN];

int main(int argc, char **argv){
    char command[COMMAND_BUFFER];

    initPath(dir_path);

    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);

    while(1){
        fputs("% ",stdout); //% print
        fgets(command, COMMAND_BUFFER -1, stdin); // input command for user
        command[strlen(command)-1] = '\0'; // delete \n

#ifdef DEBUG
        printf("command : %s \n", command);
#endif
        
        run(command); //run return value handle!!!!
    }

    return 0;
}

int run(char *command){//{{{
    int pid;
    int cmd_count, n;
    char *cToken[MAX_TOKEN][MAX_TOKEN];
    char file_path[128];

    memset((char *)cToken, 0x00, sizeof(char *) * MAX_TOKEN * MAX_TOKEN);
    memset( state, 0x00, MAX_TOKEN);

    if( ( cmd_count = tokenize(command, cToken) ) == 0 ) //return token count
        return -1;

    for(n = 0; n < cmd_count ; n++){
        strcpy(file_path, cToken[n][0]); //cToken[0] : filename -> file_path

        if( specialCommand(cToken[n]) == -1 ) // setpath.. cd... exit
            exit(-1);

        if(accessCheck(dir_path, file_path) == 0){ // file exit
        // child process create
            if( (pid = fork()) < 0) {
                perror ("fork() : ");
                exit(-2);
            }

            if( pid == 0) {
                execv(file_path, cToken[n]);
                perror("execv(): ");

                exit(0);
            }
            else if( pid > 0 ) // parent
            {
                if ( state[n] != BG )
                    wait((int*)0);
            }
        }
        else
            fprintf(stderr,"command not found\n");
    }
    return 0;
}//}}} 

int accessCheck(char **dir_path, char *file_path){ //{{{ filename -> file path
    char filename[256];

    strcpy(filename, file_path); // filename copy

    while(*dir_path)
    {
        strcpy(file_path, *dir_path++);
        strcat(file_path, filename);

        if(access(file_path, 0) == 0){ // access return value 0
#ifdef DEBUG
            printf("[accessCheck] : %s file exists !! \n", file_path);
#endif
            return 0;
        }
    }
#ifdef DEBUG
            printf("[accessCheck] : file not found !!\n");
#endif
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

int tokenize(char *command, char *cToken[MAX_TOKEN][MAX_TOKEN]){///{{{
    int t_idx = 0;
    int com_idx = 0;
    int delim_flag = 1;
    int cmd_count = 0;
#ifdef DEBUG
    int i = 0, j;
#endif

    while ( command[com_idx] && ( t_idx < MAX_TOKEN ) ){
        if(command[com_idx] == ';'){
            cToken[cmd_count++][t_idx] = NULL;
            t_idx = 0;
            delim_flag = 1;
            command[com_idx] = '\0';
        }
        else if(command[com_idx] == '&'){
            state[cmd_count] = BG;
            cToken[cmd_count++][t_idx] = NULL;
            t_idx = 0;
            delim_flag = 1;
            command[com_idx] = '\0';
        }
        else{
            if ( ( command[com_idx] != ' ' ) && delim_flag ){
                cToken[cmd_count][t_idx++] = (command + com_idx);
                delim_flag = 0;
            }
            else if( command[com_idx] == ' '){
                delim_flag = 1;
                command[com_idx] = '\0';
            }
        }
        com_idx++;
    }

    if( cToken[cmd_count][0] == NULL )
        cmd_count--;

#ifdef DEBUG
    for(j = 0 ; j < cmd_count+1 ; j++){
        i = 0;
        while( cToken[j][i] )
            printf("[tokenize] cToken[%d][%d] : %s \n", j, i, cToken[j][i++]);

    }
    printf("cmd_count = %d \n",cmd_count +1);
#endif 

    return cmd_count+1 ;
}///}}}

int specialCommand(char **cTok){///{{{
        if(!strcmp("setpath", *cTok)) {
            setpath(dir_path, cTok);
            return 0;
        }

        else if(!strcmp("exit",*cTok))
            return -1;

        else if(!strcmp("cd",*cTok)){
            if( chdir(*(cTok + 1)) == -1)
                perror(*(cTok + 1));
            return 0;
        }
}///}}}
