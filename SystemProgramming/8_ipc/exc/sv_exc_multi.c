#include "echo.h"
#include <sys/wait.h>
//#define DEBUG

int main(void){

    int msg_id, c_pid, pfd, size=0;
    key_t key;
    MSG_BUF msg_buf;
    char client_pid[MAXSIZE], exc_file[MAXSIZE], data[MAXSIZE];
    char pname[MAXSIZE];

    if ((key = ftok(PATH_NAME, 'a')) == -1) {
        perror("[SERVER] : ftok(): ");
        exit(1);
    }

    if ((msg_id = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("[SERVER] : msgget():");
        exit(2);
    }
    printf("msg id = %d \n", msg_id);

    while(1){

        if ((size = msgrcv(msg_id, &msg_buf, MAXSIZE, SERVER_TYPE, 0)) == -1) {
            perror("[SERVER] : msgrcv(): ");
            break;
        }
        else if(size == 0)
            continue;

        strcpy(data, msg_buf.mdata);
        strcpy(client_pid, strtok( data, ":"));
        strcpy(exc_file, strtok( (char *)NULL, ":"));

        if(strncmp(exc_file, "ends", 4) == 0)
            break;
        

#ifdef DEBUG
        printf("rcv data : %s \n", data); 
        printf("tok pid : %s \n", client_pid); 
        printf("tok exc_file : %s \n", exc_file); 
#endif

        sprintf(pname,"%s/%s",PATH_NAME, client_pid);
        printf("pname : %s \n", pname);
        mknod(pname, S_IFIFO|0666, 0);
    //fork
        if((c_pid = fork()) == -1){
            perror("fork() : ");
            break;
        }
        else if(c_pid == 0){

            if ((pfd = open(pname, O_WRONLY)) == -1) {
                perror("[SERVER]open() : ");
                break;
            }

            close(1); //stdout close
            dup(pfd);
            system(exc_file);
            exit(0);
        }
        //unlink
        wait(0);
        close(pfd);
        unlink(pname);
    }
    msgctl(msg_id, IPC_RMID, 0); //delete message queue
    return 0;
}
