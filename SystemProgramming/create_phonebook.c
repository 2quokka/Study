#include "phonebook.h"

int main(int argc, char **argv){
    int fd = 0;
    int size = 0;

    PHONEBOOK phonebook;
     if( argc < 2 ) {
         fprintf(stderr, "Usage : %s filename\n", argv[0]);
         exit(-1);
     }

     if((fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0 ) {
         perror(argv[1]);
         exit(-2);
     }

     while(1) {
         memset(&phonebook, 0x00, sizeof(PHONEBOOK));
         fprintf(stderr, "Insert Customer Name : ");
         fflush(stderr);

         if((size = read(0, phonebook.name, sizeof(phonebook.name))) < 0 )
             break;

         phonebook.name[size-1] = 0;

         printf("debug -- \n");
         printf(" name [0] = %c \n", phonebook.name[0]);

         if( (phonebook.name[0] == ' ') || (phonebook.name[0] == '.'))
             break;

         fprintf(stderr, "Insert Customer Phone Number : ");
         fflush(stderr);

         if( (size = read(0, phonebook.phonenumber, sizeof(phonebook.phonenumber))) < 0 ) 
             break;
         phonebook.phonenumber[size-1] = 0;

         write(fd, (char *)&phonebook, sizeof(PHONEBOOK));
     }
     close(fd);
     exit(0);

     return 0;
}
