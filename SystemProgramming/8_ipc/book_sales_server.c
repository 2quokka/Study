#include "book_sales.h"

#define CHILD_NUM 5

int sem_id=0, shm_id=0;
char *shm_ptr;
BOOK_SALES book;

void remove_ipcs();
void wait_client();
void sales_start();
int init_sem();
int init_shm();

int main(int argc, char *argv[]) {
    if( argc < 2 ) {
        fprintf(stderr, "Usage : %s book_name\n", argv[0]);
    }

    memset(&book, 0x00, sizeof(BOOK_SALES));
    memcpy(book.bookname, argv[1], strlen(argv[1]));
    book.bookname[ strlen(argv[1]) ] = 0;
    book.left_stock = 20;

    if( (shm_id = init_shm(shm_ptr)) < 0 ) {
        perror(argv[0]);
        remove_ipcs();
        exit(3);
    }

    if( (sem_id = init_sem()) < 0 ){
        perror(argv[0]);
        remove_ipcs();
        exit(4);
    }

    sales_start();
    remove_ipcs(shm_id, sem_id, shm_ptr);
    printf("%s's sales is complished \n", argv[0]);

    return 0;
}

void remove_ipcs(){
    
    if( shm_id > 0 && (shm_ptr != NULL) ) {
        shmdt(shm_ptr);
        shmctl(shm_id, IPC_RMID, NULL);
    }

    if( sem_id > 0 )
        semctl(sem_id, 0, IPC_RMID, 0);
}

void wait_client(){
    int status = 0;

    while( wait(&status) != -1 )

    printf("wait_client end \n ");
}

void sales_start(){
    int i=0, pid=0;
    char sem_buf[10], shm_buf[10];
    char child_name[10];

    memcpy(shm_ptr, (char *)&book, sizeof(BOOK_SALES));
    sprintf(sem_buf, "%d", sem_id);
    sprintf(sem_buf, "%d", shm_id);

    for( i=0; i<CHILD_NUM; i++ ) {
        if ( (pid = fork()) == -1 ) {
            perror("fork : ");
            return;
        }
        else if(pid == 0){
            sprintf(child_name, "bookstore_%d", i+1);
            execl("./book_sales_client", child_name, shm_buf, sem_buf, (char *)NULL);
            perror("execl : ");
            exit(1);
        }
    }
    wait_client();
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
    if( (shm_id = shmget(IPC_PRIVATE, sizeof(BOOK_SALES), IPC_CREAT | 0600 )) == -1) {
        perror("shmget : ");
        return -1;
    }

    if( (shm_ptr = (char *)shmat(shm_id, (char*)0, 0)) == NULL ) {
        perror("shmget : ");
        return -1;
    }

    return shm_id;
}
