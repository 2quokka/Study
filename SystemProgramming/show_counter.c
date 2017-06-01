#include <stdio.h>      // printf()
#include <unistd.h>     // sleep()
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define  KEY_NUM     9527
#define  MEM_SIZE    1024

int main( void)
{
   int   shm_id;
   void *shm_addr;

   if ( -1 == ( shm_id = shmget( (key_t)KEY_NUM, MEM_SIZE, IPC_CREAT|0666)))
   {
      printf( "공유 메모리 생성 실패\n");
      return -1;
   }

  if ( ( void *)-1 == ( shm_addr = shmat( shm_id, ( void *)0, 0)))
  {
     printf( "공유 메모리 첨부 실패\n");
     return -1;
  }
  else
  {
     printf( "공유 메모리 첨부 성공\n");
  }

   while( 1 )
   {
      printf( "%s\n", (char *)shm_addr);
      sleep( 1);
   }
/*
  if ( -1 == shmdt( shm_addr))
  {
     printf( "공유 메모리 분리 실패\n");
     return -1;
  }
  else
  {
     printf( "공유 메모리 분리 성공\n");
  }
*/

   return 0;
}
