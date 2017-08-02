#include <dirent.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define OP_CK(a, b)     ( ((a)&(b)) == (b) ) ? 1 : 0

#define BLK_SIZ 1024
#define BLK_CNT(a)      ( a / (BLK_SIZ/512) )

#define _IRUSR(m) ( m & S_IRUSR ? 'r' : '-' )
#define _IWUSR(m) ( m & S_IWUSR ? 'w' : '-' )
#define _IXUSR(m) ( m & S_IXUSR ? 'x' : '-' )
#define _IRGRP(m) ( m & S_IRGRP ? 'r' : '-' )
#define _IWGRP(m) ( m & S_IWGRP ? 'w' : '-' )
#define _IXGRP(m) ( m & S_IXGRP ? 'x' : '-' )
#define _IROTH(m) ( m & S_IROTH ? 'r' : '-' )
#define _IWOTH(m) ( m & S_IWOTH ? 'w' : '-' )
#define _IXOTH(m) ( m & S_IXOTH ? 'x' : '-' )

#define OP_N 0
#define OP_l 1
#define OP_a 2

/*
 ls -l .. -a
*/
char type(mode_t m)
{
    char r = '-';

    if(S_ISREG(m))
        r = '-';
    else if(S_ISDIR(m))
        r = 'd';
    else if(S_ISCHR(m))
        r = 'c';
    else if(S_ISBLK(m))
        r = 'b';
    else if(S_ISFIFO(m))
        r = 'p';
    else if(S_ISLNK(m))
        r = 'l';
    else if(S_ISSOCK(m))
        r = 'S';

    return  r;
}

void perm_print(mode_t m)
{
    char buf;

    buf = type(m);
    write(1, &buf, 1);
    buf = _IRUSR(m);
    write(1, &buf, 1);
    buf = _IWUSR(m);
    write(1, &buf, 1);
    buf = _IXUSR(m);
    write(1, &buf, 1);
    buf = _IRGRP(m);
    write(1, &buf, 1);
    buf = _IWGRP(m);
    write(1, &buf, 1);
    buf = _IXGRP(m);
    write(1, &buf, 1);
    buf = _IROTH(m);
    write(1, &buf, 1);
    buf = _IWOTH(m);
    write(1, &buf, 1);
    buf = _IXOTH(m);
    write(1, &buf, 1);
}

const char* get_uname(uid_t u)
{
    struct passwd *pw = getpwuid(u);
    return pw->pw_name;
}

const char* get_gname(gid_t g)
{
    struct group *gw = getgrgid(g);
    return gw->gr_name;
}

void mtime_print(time_t mt)
{
    struct tm *t = localtime(&mt);

    printf("%3d%3d%3d:%02d ", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min);
}

int run(int opt, char *path);

int main(int argc, char *argv[])
{
  char path[256]; // malloc path
  char *p;
  int opt=0, i;

  strcpy(path, ".");

  for(i=1;i<argc;i++)
  {
      p = argv[i];
      if(*p== '-')
      {
          while(*++p)
          {
              switch(*p)
              {
                  case 'a':
                    opt |= OP_a;
                    break;

                  case 'l':
                    opt |= OP_l;
                    break;

                  default:
                    exit(-1);
                
              }
          }
      }
      else
          strcpy(path, p);
  }

  return run(opt, path);
}

int run(int opt, char *path)
{
    DIR *d;
    struct dirent *dir;
    struct stat buf;
    char abpn[256]; //absolute path name


    printf("path: %s \n", path);
    d = opendir(path); //fail return NULL
    if(d) 
    {
        if( OP_CK(opt,OP_l) ) // option -l for total print
        {
            if(lstat(path, &buf) < 0)
            {
                perror("lstat ");
                return -1;
            }
           // printf("total : %ld \n", buf.st_blocks);
        }

        while ((dir = readdir(d)) != NULL)
        {
            if( (!OP_CK(opt, OP_a)) && (*(dir->d_name)) == '.')
                continue;

            sprintf( abpn,"%s/%s", path, dir->d_name);

            //printf("abpn : %s \n", abpn);

            if ( OP_CK(opt, OP_l) )// option -l
            {
                if(lstat(abpn, &buf) < 0)
                {
                    perror("stat : ");
                    return -1;
                }
                perm_print(buf.st_mode); //permission
                printf("%2ld ", buf.st_nlink); //link 
                printf("%-8s", get_uname(buf.st_uid)); //owner name
                printf("%-8s", get_gname(buf.st_gid)); //group name
                printf("%8ld", buf.st_size); //size
                mtime_print(buf.st_mtime);
            }
            puts(dir->d_name);
        }
        closedir(d);

        return 0;
    }
    else
        return -1;
}
