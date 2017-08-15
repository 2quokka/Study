/* myls.c  */
#include "myls.h"

void str_sort(char *str[], int num)
{   
	int i, j, k, flag;
    char *temp;
    for (i = 0; i < num - 1; i++) {
        for (j = 0; j < num - 1; j++) {
            flag=0;
            for (k = 0; str[j][k] != '\0' && str[j + 1][k] != '\0'; k++) {
                if (str[j][k] > str[j + 1][k]) {
                    temp = str[j];
                    str[j] = str[j + 1];
                    str[j + 1] = temp;
                    flag=1;
                    break;
                }
            }
            if(!flag)
            {
                if(str[j][k] != '\0')
                {
                    temp = str[j];
                    str[j] = str[j + 1];
                    str[j + 1] = temp;
                    flag=0;
                }
            }
        }
    }
}

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
    printf("%c", type(m));
    printf("%c", _IRUSR(m));
    printf("%c", _IWUSR(m));
    printf("%c", _IXUSR(m));
    printf("%c", _IRGRP(m));
    printf("%c", _IWGRP(m));
    printf("%c", _IXGRP(m));
    printf("%c", _IROTH(m));
    printf("%c", _IWOTH(m));
    printf("%c", _IXOTH(m));
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
    struct tm *t;
    time_t timer = time(NULL);
    int year = localtime(&timer)->tm_year;

    t=localtime(&mt);

    printf("%3d", t->tm_mon+1);
    printf("%3d", t->tm_mday);
    if(year != t->tm_year)
        printf("%6d ", t->tm_year + 1900);
    else
        printf(" %02d:%02d ", t->tm_hour, t->tm_min);
}

int make_opt(int argc, char **argv)
{
    int opt =0, i;
    char *p;

    for(i=1; i<argc; i++)
    {
        p=argv[i];

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

                  case 's':
                    opt |= OP_s;
                    break;

                  case 'r':
                    opt |= OP_r;
                    break;

                  default:
                    printf("ls: invalid option -- '%c'\n", *p);
                    return -1;
              }
          }
        }
    }
    return opt;
}

char* make_path(int argc, char **argv)
{
    static int AG_IDX = 0;
    
    while(++AG_IDX < argc)
    {
        if( *argv[AG_IDX] == '-' )
            continue;

        return argv[AG_IDX];
    }

    return NULL;
}

unsigned int P_COUNT; //path count

int main(int argc, char *argv[])
{
    char *p, **d_list, **f_list;
    int opt=0, d_idx=0, f_idx=0;
    struct stat buf;

    str_sort(argv+1, argc-1);

    if( (opt = make_opt(argc, argv)) == -1)
      return -1;

    f_list = malloc(sizeof(char *) * argc);
    d_list = malloc(sizeof(char *) * argc);

    while(p = make_path(argc, argv))
    {
        memset(&buf, 0, sizeof(struct stat));
        if(lstat(p, &buf)== -1)
        {
            fprintf(stderr,"ls: cannot access '%s': No such file or directory\n", p);
            continue;
        }

        if(S_ISDIR(buf.st_mode)) //dir
            d_list[d_idx++] = p;
        else //file
            f_list[f_idx++] = p;

        P_COUNT++;
    }

    if(!P_COUNT) //nothing   ... d_idx =0 && f_idx =0
    {
        d_list[d_idx] = ".";
        d_run(opt, d_list, 1);
        return 0;
    }

    f_run(opt, f_list, f_idx);
    d_run(opt, d_list, d_idx);

    free(f_list);
    free(d_list);

    return 0;
}

int f_run(int opt, char **list, int n)
{
    int i;
    struct stat buf;
    char ln_buf[MAX];

    if(OP_CK(opt, OP_r))
        i = n;
    else
        i = 0;

    while ( (i>=0) && (i<n) )
    {
        memset(&buf, 0, sizeof(struct stat));
        lstat(list[i], &buf);

        if(OP_CK(opt, OP_s))
            printf("%2ld ", BLK_CNT(buf.st_blocks));

        if(OP_CK(opt, OP_l))
        {
            perm_print(buf.st_mode); //permission
            printf("%4ld ", buf.st_nlink); //link 
            printf("%-8s", get_uname(buf.st_uid)); //owner name
            printf("%-8s", get_gname(buf.st_gid)); //group name
            printf("%8ld", buf.st_size); //size
            mtime_print(buf.st_mtime);
            if(S_ISLNK(buf.st_mode))
            {
                readlink(list[i], ln_buf, MAX);
                printf("%s -> %s\n", list[i], ln_buf);
            }
            else
                printf("%s\n", list[i]);

        }
        else
            printf("%s\n", list[i]);

        if(OP_CK(opt, OP_r))
            i--;
        else
            i++;
    }

    return 0;
}

int d_run(int opt, char **list, int n)
{
    struct dirent **dent;
    struct stat buf;
    int ent_n, i, j;
    unsigned long total;
    char p_buf[MAX], ln_buf[MAX];

    for(i=0; i<n; i++)
    {
        if(P_COUNT>1)
            printf("\n%s:\n",list[i]);

        ent_n = scandir(list[i], &dent, NULL, alphasort);
        
        if(OP_CK(opt, OP_l) || OP_CK(opt, OP_s))
        {
            for(total =0,j=0;j<ent_n;j++)
            {
                sprintf(p_buf, "%s/%s", list[i], dent[j]->d_name);
                lstat(p_buf, &buf);
                
                if( (!OP_CK(opt, OP_a)) && (*(dent[j]->d_name) == '.') )
                    continue;
                    
                total += BLK_CNT(buf.st_blocks);
            }
            printf("total %ld\n", total);
        }

        if(OP_CK(opt, OP_r)) // reverse
            j = ent_n-1;
        else
            j=0;
        
        while( (j>=0) && (j<ent_n) )
        {
            if(!OP_CK(opt, OP_a))
            {
                if(*(dent[j]->d_name) == '.')
                {
                    if(OP_CK(opt, OP_r))
                        j--;
                    else
                        j++;

                    continue;
                }
            }

            sprintf(p_buf, "%s/%s", list[i], dent[j]->d_name);
            lstat(p_buf, &buf);

            if(OP_CK(opt, OP_s))
                printf("%2ld ", BLK_CNT(buf.st_blocks));
            
            if( OP_CK(opt, OP_l))
            {
                perm_print(buf.st_mode); //permission
                printf("%4ld ", buf.st_nlink); //link 
                printf("%-8s", get_uname(buf.st_uid)); //owner name
                printf("%-8s", get_gname(buf.st_gid)); //group name
                printf("%8ld", buf.st_size); //size
                mtime_print(buf.st_mtime);

                if(S_ISLNK(buf.st_mode))
                {
                    readlink(p_buf, ln_buf, MAX);
                    printf("%s -> %s\n", dent[j]->d_name, ln_buf);
                }
                else
                    printf("%s\n", dent[j]->d_name);
            }
            else
                printf("%s\n", dent[j]->d_name);

            if(OP_CK(opt, OP_r))
                j--;
            else
                j++;
        }
    }

    return 0;
}
