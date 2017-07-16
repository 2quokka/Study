#include "ftp.h"

SHM_FRMfileframe;
SHM_FRM *shm_fp;

MSG_BUF msg_buf;

int sem_id =0, shm_id =0, msg_id=0;

char *shm_ptr;
int size =0;

int main(int argc, char *argv[]){
    
    



