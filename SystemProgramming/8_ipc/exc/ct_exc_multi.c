#include "echo.h"

int main(void){
    int size = 0, msg_id = 0, pfd, i;
    key_t key;
    char pid[MAXSIZE], pname[MAXSIZE];
    char exc_file[MAXSIZE], line[MAXSIZE];

    MSG_BUF msg_buf;

    if((key = ftok(PATH_NAME, 'a')) == -1) {
        perror("ftok() : ");
        exit(1);
    }

    if((msg_id = msgget(key, 0)) == -1){
        perror("msgget() : ");
        exit(2);
    }

    sprintf(pid,"%d",getpid());
    sprintf(pname,"%s/%s", PATH_NAME, pid);

    while(1){
        if((size = read( 0, exc_file, MAXSIZE)) < 0 ){
            perror("read() : ");
            break;
        }

        if(strncmp(exc_file, "end", 3) == 0){
            msgsnd(msg_id, &msg_buf, strlen(msg_buf.mdata)+1, 0);
            break;
        }

        sprintf(msg_buf.mdata, "%s:%s", pid, exc_file);

        msg_buf.mtype = SERVER_TYPE;

        if(msgsnd(msg_id, &msg_buf, strlen(msg_buf.mdata)+1, 0) == -1) {
            perror("msgsnd () : ");
            break;
        }


        for(i = 0 ; i< NUMTRIES; i++){
            if( (pfd = open(pname, O_RDONLY)) == -1)
                sleep(1);
            else
                break;
        }

        while((size = read(pfd, line, MAXSIZE)) > 0)
            write(1, line, size);

        close(pfd);
    }

    return 0;
}
