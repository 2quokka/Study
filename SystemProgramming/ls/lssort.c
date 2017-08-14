#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main(void)
{
    struct dirent **direntp;
    int n, i;
    struct stat statbuf;

    n = scandir(".", &direntp, 0, alphasort);

    for(i =0; i< n; i++)
    {
        stat(direntp[i]->d_name, &statbuf);
        printf("%9d %s\n", statbuf.st_size, direntp[i]->d_name);
    }
    return 0;
}

