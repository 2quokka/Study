//ftp server

#include "ftp.h"

SHM_FRM fileframe; // shared memory frame
SHM_FRM *shm_fp;

MSG_BUF msg_buf;

int sem_id=0, shm_id=0, msg_id=0;

char *shm_ptr;
int size  =0;

void sigint_signalhandler(int);
void remove_ipcs();
int init_sem();
int init_shm();
//STATE state = 5; // enum 

int main(void){

    memset(&fileframe, 0x00, sizeof(SHM_FRM));
    strcpy(fileframe.status, "invalid");

    signal(SIGINT, sigint_signalhandler);
    signal(SIGQUIT, sigint_signalhandler);

    if ((key = ftok(KEY_PATH, 'a')) == -1) {
        perror("[SERVER] : ftok(): ");
        exit(1);
    }

    if ((msg_id = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("[SERVER] : msgget():");
        exit(2);
    }

    if( (shm_id = init_shm()) < 0 ) {
        perror(argv[0]);
        remove_ipcs();
        exit(3);
    }

    if( (sem_id = init_sem()) < 0 ){
        perror(argv[0]);
        remove_ipcs();
        exit(4);
    }

    shm_fp = (SHM_FRM *)shm_ptr;
    memcpy(shm_ptr, (char *)&fileframe, sizeof(SHM_FRM));

    while(1){
        if (( size = msgrcv(msg_id, &msg_buf, MAXSIZE, SERVER_TYPE, IPC_NOWAIT)) == -1) {
            perror("[SERVER] : msgrcv() : ");
            break;
        }

        if(size > 0){
            msg_buf.mtype = CLIENT_TYPE;
            sprintf(msg_buf.mdata, "%d %d", sem_id, shm_id);

            if ((size = msgsnd(msg_id, &msg_buf, MAXSIZE, IPC_NOWAIT)) == -1){
                perror("[SERVER] : msgsnd() : ");
                break;
        }
            size = 0;
        }

        if(!strcmp(shm_fp->status, "requested")){
            memcpy((char *)&fileframe, shm_ptr, sizeof(SHM_FRM));
            printf("[SERVER] %s : prosessed! \n ", fileframe.filename);
            strcpy(shm_fp->status,"processed");
        }
    }

    remove_ipcs();

    return 0;
}

void sigint_signalhandler(int){
    if (sig == SIGINT || sig == SIGQUIT)
        remove_ipcs();
        exit(1);
}

void remove_ipcs(){
    
    if( shm_id > 0 && (shm_ptr != NULL) ) {
        shmdt(shm_ptr);
        shmctl(shm_id, IPC_RMID, NULL);
    }

    if( sem_id > 0 )
        semctl(sem_id, 0, IPC_RMID, 0);

    if ( msg_id > 0)
        msgctl(msg_id, IPC_RMID, 0); //delete message queue
}

int init_sem(){
    if((sem_id= semget(IPC_PRIVATE, 1, IPC_CREAT | 0600)) == -1 ) {
        perror("semget : ");
        return -1;
    }
   
    if( semctl(sem_id, 0, SETVAL, 1) == -1 ) {
        perror("semctl: ");
        return -1;
    }

    return sem_id;
}

int init_shm(){
    if( (shm_id = shmget(IPC_PRIVATE, sizeof(SHM_FRM), IPC_CREAT | 0600 )) == -1) {
        perror("shmget : ");
        return -1;
    }

    if( (shm_ptr = (char *)shmat(shm_id, (char*)0, 0)) == NULL ) {
        perror("shmget : ");
        return -1;
    }

    return shm_id;
}
