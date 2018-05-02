#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
    int fd, flags;
    int i, n;
    char line[BUFSIZ];
/*
    if((fd=open("/dev/tty", O_RDONLY | O_NDELAY))==-1){
        perror("/dev/tty");
        exit(2);
    }
*/
    if((fd = dup(0)) < 0){
        perror("dup");
        exit(2);
    }

//    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NDELAY);

    printf("Enter your PIN within five seconds:\n");
    sleep(5);

    if(read(fd, line, BUFSIZ)<=0){
        printf("\n======> Sorry. \n");
        exit(1);
    }

    printf("%s\n", line);
    flags = fcntl(fd, F_GETFL, 0);
    flags &= ~O_NDELAY;
    fcntl(fd, F_SETFL, flags);

    printf("Enter your bank account number:\n");
  
    i = read(fd,line, BUFSIZ);
    line[i] = '\0';
    printf("%s\n", line);
    return 0;
}

