//client

#include "ftp.h"

SHM_FRM *frmp;
char fn[NAME_SIZE];
int sem_id=0, shm_id=0, req_flag=0;
key_t key;
static struct sembuf lock = {0, -1, SEM_UNDO};
static struct sembuf unlock = {0, 1, SEM_UNDO};

void remove_ipcs();
int init_sem();
int init_shm();
int semaphore_down();
int semaphore_up();

int main(int argc, char *argv[]){

    if ( (key = ftok(KEY_PATH, 'a')) == -1 ) {
        perror("ftok : ");
        exit(2);
    }

    if( (shm_id = init_shm()) < 0 ) {
        perror("init shm() : ");
        exit(3);
    }

    if( (sem_id = init_sem()) < 0 ){
        perror("init sem() : ");
        exit(4);
    }

///////////////////////////request///////////////////////////////
    while(1){
        if(!req_flag){
            memset(fn, 0x00, NAME_SIZE);
            read(0, fn, NAME_SIZE-1);
            fn[strlen(fn)-1] = '\0';
        }
        if(semaphore_down(sem_id) < 0) // critical section start
        {
            perror("semaphore_down :");
            exit(3);
        }

        if( (!req_flag) && (frmp->status == INVALID) ){

            printf("%s\n", fn);
            memcpy(frmp->filename, fn, NAME_SIZE);
            printf("[CLIENT] shm write ! \n");
            req_flag = 1;
            frmp->status = REQUESTED;
        }
        else if( req_flag && (frmp->status == PROCESSED) ){
            write(1, frmp->data, DATA_SIZE);
            memset(frmp, 0x00, sizeof(SHM_FRM));
            req_flag = 0;
            frmp->status = INVALID;
        }

        if(semaphore_up(sem_id) < 0 )
        {
            perror("semaphore_up : ");
            exit(3);
        }
    }

    shmdt(frmp);
    return 0;
}

int init_sem(){
    if((sem_id= semget(key, 1, 0)) == -1 ) {
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
    if( (shm_id = shmget(key, sizeof(SHM_FRM), 0)) == -1) {
        perror("shmget : ");
        return -1;
    }

    if( ( frmp = (SHM_FRM *)shmat(shm_id, (char*)0, 0)) == NULL ) {
        perror("shmget : ");
        return -1;
    }

    return shm_id;
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
