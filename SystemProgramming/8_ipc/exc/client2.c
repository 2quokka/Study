#include "echo.h"

void main()
{
    int size =0, msg_id=0;
    key_t key;
    MSG_BUF msg_buf;
    char line[MAXSIZE];

    if((key = ftok(".", 'a')) == -1){
        perror("[Server]ftok() : ");
        exit(1);
    }

    if((msg_id = msgget(key, 0)) == -1){
        perror("[Client]:msgget():");
        exit(2);
    }
    else
        printf("[Client] msgid : %d \n ", msg_id);

    while(1){
        memset(&msg_buf, 0x00, sizeof(MSG_BUF));
        if((size=read(0,msg_buf.mdata, MAXSIZE)) < 0 ){
            perror("[Client] : read : ");
            exit(2);
        }

        if( msg_buf.mdata[0] == 'e' && msg_buf.mdata[1] == 'n' && msg_buf.mdata[2] == 'd'){
            exit(0);
        }
        
        msg_buf.mtype = SERVER_TYPE;

        if(msgsnd(msg_id, &msg_buf, strlen(msg_buf.mdata)+1, 0) == -1){
            perror("[Client] : msgsnd : ");
            exit(2);
        }

        msg_buf.mtype = CLIENT_TYPE;

        sleep(1);
        while(1){
            if(msgrcv(msg_id, &msg_buf, MAXSIZE+1, CLIENT_TYPE, IPC_NOWAIT) == -1){
            break;
            }

            fputs(msg_buf.mdata, stdout);
        }

        printf("\n complete \n");
    }
    msg_buf.mtype = SERVER_TYPE;
    if( msgsnd(msg_id, &msg_buf, 0, 0)==-1)
        perror("[Client] : msgsnd : ");

        exit(0);
}

