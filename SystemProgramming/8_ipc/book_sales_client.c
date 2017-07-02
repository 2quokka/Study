#include "book_sales.h"

char p_name[20];
struct sembuf lock = {0, -1, SEM_UNDO};
struct sembuf unlock = {0, 1, SEM_UNDO};

int shm_id, sem_id;
char *shm_ptr;
BOOK_SALES *book;

int init_shm();
void sales_book(char *);
int semaphore_down();
int semaphore_up();
void remove_ipcs();

void main(int argc, char *argv[])
{
	if(argc < 3)
	{
		fprintf(stderr,"Usage %s shm_id sem_id\n",argv[0]);
		exit(1);
	}

	memcpy(p_name, argv[0], strlen(argv[0]));
	p_name[strlen(argv[0])]=0;

	sscanf(argv[1],"%d", &shm_id);
	sscanf(argv[2],"%d", &sem_id);

	if(init_shm() < 0)
	{
		perror(argv[0]);
		exit(2);
	}

	sales_book(p_name);

	remove_ipcs(shm_ptr);

	exit(0);
}

int init_shm() 
{
	if(shm_id > 0)
	{
		if( (shm_ptr=shmat(shm_id, (char *)0, 0)) == (char *)-1)
		{
			perror("shmat:");
			return -1;
		}
		return 0;
	}
	return -1;
}

void sales_book(char *store_name)
{
	int empty=0;
	char sales_date[13];
	struct timeval t_val;
	struct tm *tm_ptr;

	book = (BOOK_SALES*)shm_ptr;

	srand((unsigned)getpid());
	while(!empty)
	{
		if(semaphore_down(sem_id)<0)
		{
			perror("semaphore_down :");
			break;
		}

		if(!book->left_stock)
		{
			printf("[%s] : no book left\n",store_name);
			empty++;
		}
		else
		{
			gettimeofday(&t_val, NULL);
			tm_ptr = (struct tm *)localtime(&t_val.tv_sec);
			strftime(sales_date, 20, "%Y/%m/%d/%H:%M",tm_ptr);
			memcpy(book->sale_date, sales_date, strlen(sales_date));
			book->left_stock--;
			printf("[%s]%s : book stock : %d EA\n",store_name,book->sale_date, book->left_stock);
		}

		if(semaphore_up(sem_id) < 0 )
		{
			perror("semaphore_up : ");
			break;
		}
		sleep(((unsigned)rand() % 10) + 1);
	} // end of while
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
					
void remove_ipcs()
{
	if(shm_ptr != NULL)
		shmdt(shm_ptr);
}

