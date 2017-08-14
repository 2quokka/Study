/* myls.h */

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

#define BLK_SIZ 1024    // ls -l blocks unit size
#define BLK_CNT(a)      ( a / (BLK_SIZ/512) )// stat _ blocks unit size 512
#define MAX 256

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
#define OP_s 4
#define OP_r 8

int make_opt(int argc, char **argv); // return option
char* make_path(int argc, char **argv);
void str_sort(char *str[], int num);
int f_run(int opt, char **list, int n); // file
int d_run(int opt, char **list, int n); // directory

/* l option relation */
char type(mode_t m); // file type
void perm_print(mode_t m);
const char* get_uname(uid_t u);
const char* get_gname(gid_t g);
void mtime_print(time_t mt);
