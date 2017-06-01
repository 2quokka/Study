#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 40
#define PHONE_SIZE 100

#define BUBBLE_SORT
//#define SELECT_SORT
//#define INSERT_SORT
//#define QUICK_SORT

enum FLAG{OFF,ON};
enum CHOICE{PRINT=1, FIND, INSERT, DELETE, SAVE, INIT, SORT, QUIT};

struct Person{
	char name[NAME_SIZE];
	char phone[PHONE_SIZE];
	struct Person *next;
	struct Person *prev;
};


int choice(char *reply);
void print(struct Person *top);
int find(char *name);
void insert(char *number, char *name);
void sort();
void delete(char *name);
int save(char *fileName);
int initialize(char *fileName);

char *get_phone(char *phone);
char *get_name(char *name);

struct Person *head = NULL;
struct Person *last = NULL;


int main(int argc, char *argv[])
{//{{{
	char name[NAME_SIZE];
	char phone[PHONE_SIZE];
	char reply[20];

	while(1)
	{
		puts("command(print, find, insert, delete, save, init, sort, quit)?");
		fgets(reply,20,stdin);
		reply[strlen(reply)-1] = '\0';

		switch(choice(reply))
		{
			case PRINT:
				print(head);
				break;

			case FIND:
				find(get_name(name));
				break;

			case INSERT:
				insert(get_phone(phone),get_name(name));
				break;

			case DELETE:
				delete(get_name(name));
				break;
			
			case SAVE:
				save(argv[1]);
				break;
			
			case INIT:
				initialize(argv[1]);
				break;
			case SORT:
				sort();
				printf("sort complete !! \n");
				break;

			case QUIT:
				return 0;

			default :
				printf("incorrect !\n");
		}
	}

	return 0;
}//}}}

char *get_name(char *name)
{//{{{
	puts("name ?");
	fgets(name,NAME_SIZE,stdin);
	name[strlen(name)-1] = '\0';

	return name;
}//}}}

char *get_phone(char *phone)
{//{{{
	puts("number ?");
	fgets(phone,PHONE_SIZE,stdin);
	phone[strlen(phone)-1] = '\0';

	return phone;
}//}}}

void insert(char *number, char *name)
{//{{{
	struct Person *tmp =(struct Person *)malloc(sizeof(struct Person));
	strcpy(tmp->name, name);
	strcpy(tmp->phone, number);
	tmp->next = 0;
	tmp->prev = 0;

	if(head ==0)
	{
		head= tmp;
		last= tmp;

	}
	else
	{
		tmp->prev = last;
		last->next = tmp;
	}

	last = tmp;
}//}}}

int find(char *name)
{//{{{
	struct Person *tmp=head;
	int find_count =0;
	while(tmp)
	{
		if(!strcmp(tmp->name, name))
		{
			printf("%s: %s \n",tmp->name, tmp->phone);
			find_count++;
		}
		tmp= tmp->next;
	}

	return find_count;
}//}}}

void print(struct Person *top)
{//{{{
	int i=1;

	if(head && last)
		printf("head name : %s lastname : %s  \n", head->name, last->name);
	while(top){
		printf("[%d] %s: %s \n", i++, top->name, top->phone);
		top=top->next;
	}
}//}}}

int choice(char *reply)
{//{{{
	if(!strcmp(reply,"print"))
		return 1;
	else if(!strcmp(reply,"find"))
		return 2;
	else if(!strcmp(reply,"insert"))
		return 3;
	else if(!strcmp(reply,"delete"))
		return 4;
	else if(!strcmp(reply,"save"))
		return 5;
	else if(!strcmp(reply,"init"))
		return 6;
	else if(!strcmp(reply,"sort"))
		return 7;
	else if(!strcmp(reply,"quit"))
		return 8;
	else 
		return 0;
} //}}}

void delete(char *name)
{//{{{
	struct Person *tmp=head, *tmp_next;  //tmp_next is dp name,number for delete all
	char phone[PHONE_SIZE];
	enum FLAG dpflag= OFF;

	if(find(name)> 1)  //duplication name resolved by requiring number.
	{
				puts("number ?");
				fgets(phone,PHONE_SIZE,stdin);
				phone[strlen(phone)-1] = '\0';
				dpflag = ON;  //flag on
	}

	while(tmp)
	{
		tmp_next=tmp->next;
		if(( (!dpflag && !strcmp(tmp->name, name)) || (dpflag && !strcmp(tmp->name, name) && !strcmp(tmp->phone, phone)) )){
			if(tmp==head)
			{
				head=tmp->next;
				if(head)
					head->prev=0;
			}
			else
			{
				tmp->prev->next = tmp->next;
				if(tmp->next)
					tmp->next->prev = tmp->prev;
				else  // tmp == last
					last = tmp->prev;
			}
			free(tmp);
			puts("delete complete!\n");
		}
		tmp=tmp_next;
	}
}//}}} 

int save(char *fileName)
{//{{{
	struct Person * node = head;
	FILE *fp;
	if((fp=fopen(fileName,"w"))==NULL)
	{
		fprintf(stderr, "save file open fail ...\n");
		return -1;
	}

	while(node)
	{
		fprintf(fp, "%s %s \n",node->name, node->phone);
		node=node->next;
	}
	fclose(fp);

	return 0;
}//}}} 

int initialize(char *fileName)
{//{{{ {
	struct Person * node = head;
	FILE *fp;
	char name[NAME_SIZE], phone[PHONE_SIZE];

	//delete
	while(node)
	{
		delete(node->name);
		node=node->next;
	}

	if((fp = fopen(fileName,"r"))==NULL)
	{
		fprintf(stderr, "read file open fail...\n");
		return -1;
	}

	while(fscanf(fp,"%s %s", name, phone)>=2)
	{
		insert(phone, name);	
	}

	return 0;

	fclose(fp);
}//}}}
#ifdef BUBBLE_SORT
void sort()
{//{{{
	struct Person *before, *after, *current;
	int i, j, count;

	for(current = head, count=0; current; current = current->next, count++);

	for(i=0; i<count; i++)
	{
		current = head;
		for(j=0;j<count-1-i;j++)
		{
			before = current->prev;
			after = current->next;

			if(strcmp(current->name, after->name) > 0)
			{
				 if(!before) // current is head
					 head=after;
				 else
					 before->next = after;

				 if(after->next) // after is last
					 after->next->prev = current;
					 

				 current->next = after->next;
			     current->prev = after;

				 after->next=current;
				 after->prev=before;

				 current =after;
			}	
			current = current -> next;
		}
	}

	for(current=head; current->next;current= current->next);

	last= current;
 }//}}} 
#endif

#ifdef INSERT_SORT
void sort()
{
	struct Person *ptr;
	int i, count;
	for(ptr =head, count =0; ptr; ptr=ptr->next, count ++);

	ptr = head;
	for(i=0; i<count; i++)
	{
		for(j=0;j<count-1-i,j++)
			if(strcmp(ptr->name, ptr->next->name))
	}
}
#endif
