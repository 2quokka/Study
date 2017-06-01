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

//function
int run(char *command);
int accessCheck(char **command_path, char* filename);
int setpath(char **path, char **cToken);
int initPath(char **path);
int tokenize(char *command, char **cToken, char delim);

char *dir_path[MAX_PATH];

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
    char file_path[128];
    char *cToken[MAX_TOKEN];

    if( tokenize(command, cToken, ' ') == 0 ) //return token count
        return -1;


    strcpy(file_path, cToken[0]); //cToken[0] : filename -> file_path

    if(!strcmp("setpath",cToken[0])) {

        setpath(dir_path, cToken);
        return 0;
    }

    else if(!strcmp("exit",cToken[0]))
        exit(-1);


    if(accessCheck(dir_path, file_path) == 0){ // file exist
    // child process create
        if( (pid = fork()) < 0) {
            perror ("fork() : ");
            exit(-2);
        }

        if( pid == 0) {
#ifdef DEBUG
            printf("child process running.. [pid = %d ]\n", getpid());
#endif
            execv(file_path, cToken);
            perror("execv(): ");

            exit(0);
        }
        else if( pid > 0 ) // parent
        {
#ifdef DEBUG
            printf("parent process running..[pid = %d ]\n", getpid());
#endif
            // wait status ...exceptin handling..!!
            wait((int*)0);
            
            return 0;
        }
    }
    else
    {
        fprintf(stderr,"command not found\n");
        return -1;
    }

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

int setpath(char **path, char **cToken){ //{{{ cToken[0] == setpath 

    while(*++cToken){
        while(*path){path++;} //path null
        *path = malloc(strlen(*cToken)+2); // 2 => slash  require free!!!
        strcpy(*path, *cToken);

        //add slash
        if( *( (*path) + strlen(*path)-1 ) != '/')
            strcat(*path,"/");
#ifdef DEBUG
            printf("[setpath] : %s \n", *path);
#endif
    }

    return 0;
}//}}}

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

int tokenize(char *command, char **cToken, char delim){///{{{
    int t_idx = 0;
    int com_idx = 0;
    int delim_flag = 1;
#ifdef DEBUG
    int i = 0;
#endif

    while ( command[com_idx] && ( t_idx <= MAX_TOKEN ) ){
        
        if ( ( command[com_idx] != delim ) && delim_flag ){
            cToken[t_idx++] = (command + com_idx);

            delim_flag = 0;
        }
        else if( command[com_idx] == delim){
            delim_flag = 1;
            command[com_idx] = '\0';
        }
        
        com_idx++;
    }

    cToken[t_idx] = NULL;
#ifdef DEBUG
    while(*(cToken+i))
        printf("[tokenize] cToken[%d] : %s \n", i, *(cToken + i++));
#endif 

    return t_idx;
}///}}}
