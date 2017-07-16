#include "ftp.h"

SHM_FRM *frmp; // share memory frame pointer
key_t key;
int sem_id=0, shm_id=0, fd;
char data_buf[DATA_SIZE];

static struct sembuf lock = {0, -1, SEM_UNDO};
static struct sembuf unlock = {0, 1, SEM_UNDO};

void remove_ipcs();
int init_sem();
int init_shm();
int semaphore_down();
int semaphore_up();
void signalhandler(int);

int main(void){

    signal(SIGINT, signalhandler);
    signal(SIGQUIT, signalhandler);

    if ( (key = ftok(KEY_PATH, 'a')) == -1 ) {
        perror("ftok : ");
        exit(2);
    }

    if( (shm_id = init_shm()) < 0 ) {
        perror("init shn : ");
        remove_ipcs();
        exit(3);
    }
    if( (sem_id = init_sem()) < 0 ){
        perror("init sem : ");
        remove_ipcs();
        exit(4);
    }

    frmp->status = INVALID;

    while(1){
        printf("[SERVER] monitoring..! \n");
        if(semaphore_down(sem_id)<0)
        {
            perror("semaphore_down :");
            break;
        }

        if(frmp->status == REQUESTED){
            printf("request !\n");
            printf("filename : %s \n", frmp->filename);

            memset(data_buf, 0x00, DATA_SIZE);

            if( (fd = open(frmp->filename, O_RDONLY)) == -1 ){
                perror("open() : ");
                strcpy(data_buf, "invalid file name !\n");
            }
            else{
                if( read(fd, data_buf, DATA_SIZE) < 0 )
                {
                    perror("read(): ");
                    exit(2);
                }
            }
                memcpy(frmp->data, data_buf, DATA_SIZE);

                frmp->status = PROCESSED;
        }

		if(semaphore_up(sem_id) < 0 )
		{
			perror("semaphore_up : ");
			break;
		}

        sleep(1);
    }

    remove_ipcs();

    return 0;
}
void signalhandler(int sig){
    if(sig == SIGINT || sig == SIGQUIT){
        remove_ipcs();
        exit(0);
    }
}

int init_sem(){
    if((sem_id= semget(key, 1, IPC_CREAT | 0600)) == -1 ) {
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
    if( (shm_id = shmget(key, sizeof(SHM_FRM), IPC_CREAT | 0600 )) == -1) {
        perror("shmget : ");
        return -1;
    }

    if( (frmp = (SHM_FRM *)shmat(shm_id, (char*)0, 0)) == NULL ) {
        perror("shmget : ");
        return -1;
    }

    memset(frmp, 0x00, sizeof(SHM_FRM));

    return shm_id;
}
void remove_ipcs(){
    
    if( shm_id > 0 && (frmp != NULL) ) {
        shmdt(frmp);
        shmctl(shm_id, IPC_RMID, NULL);
    }

    if( sem_id > 0 )
        semctl(sem_id, 0, IPC_RMID, 0);
}
int semaphore_down()
{
	if(semop(sem_id,&lock,1)==-1)
	{
		perror("semop :");
		return -1;
	}
	return 0;
}

int semaphore_up()
{
	if(semop(sem_id,&unlock,1)==-1)
	{
		perror("semop :");
		return -1;
	}
	return 0;
}
