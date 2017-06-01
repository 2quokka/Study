#include <stdio.h>
#include <string.h>

#define MAX 50
#define NAME_SIZE 64
#define PHONE_SIZE 30

enum MENU{ADD, DELETE, FIND, PRINT, QUIT};

typedef struct Phone
{
	char name[NAME_SIZE];
	char phone[PHONE_SIZE];
}Phone;

void add(Phone *);
void delete(char *);
int find(char *);
int choice_function(char *);
void print();

int phone_size=0;
Phone phone[MAX]; //배열선언

int main()
{
	int ch;
	char choice[10];
	char find_name[NAME_SIZE];
	int find_index;

	while(1)
	{
		printf("add, delete, find, print, quit ? ");
		fgets(choice,10,stdin);
		ch = choice_function(choice);
		
		if(ch == -1)
		{
			printf("sorry.. rechoice please! \n");
			continue;
		}

		switch(ch)
		{
			case ADD:
				add(phone);
				break;
			case DELETE:
				printf("name : ");
				fgets(find_name,NAME_SIZE, stdin);
				delete(find_name);
				break;
			case FIND:
				printf("name : ");
				fgets(find_name,NAME_SIZE, stdin);
				find_index=find(find_name);
				if(find_index == -1)
				{
					printf("not found\n");
				}
				else
				{
					printf("------------find !!---------\n");
					printf("name : %s \n", phone[find_index].name);
					printf("phone number  : %s \n", phone[find_index].phone);
				}
				
				break;
			case PRINT:
				print();
				break;
			case QUIT:
				return 0;
		}
	}
	return 0;
}

int choice_function(char *choice)
{
	int result;
	
	if(!strcmp("add\n",choice))
		result=0;
	else if(!strcmp("delete\n", choice))
		result=1;
	else if(!strcmp("find\n", choice))
		result=2;
	else if(!strcmp("print\n", choice))
		result=3;
	else if(!strcmp("quit\n", choice))
		result=4;
	else
		result=-1;

	return result;
}

void add(Phone *ptr) //phone size 는 등록된것보다 +1
{
	char reply;
	char name[NAME_SIZE];
	char phone[PHONE_SIZE];

	if(phone_size > MAX)
	{
		printf("sorry.. full!!  \n");
		return;
	}

	while(phone_size < MAX)  //phone_size 증가 
	{
		printf("name : ");
		fgets(name,NAME_SIZE,stdin);
		printf("phone : ");
		fgets(phone,PHONE_SIZE,stdin);

		strcpy((ptr+phone_size)->name, name);
		strcpy((ptr+phone_size)->phone, phone);

		printf("add complete ! \n");
		phone_size++; //폰 사이즈 증가

		printf("[%d/%d]add continue? (y/n) ",phone_size, MAX);
		reply=getchar();
		getchar();
		
		if((reply != 'y'))
			break;
	}

}

void delete(char* name)
{
	int i;

	int delete_index = find(name);

	if(delete_index != -1)
	{
		for(i=delete_index ; i<phone_size; i++)
			phone[i] = phone[i+1];
		phone_size--;
		printf("delete complete !!\n");
	}
	else
		printf("fail not found !! \n");

	return;
}

int find(char *name)  //-1 반환시 못찾음
{
	int i;
	int index = -1;

	for(i=0; i<phone_size; i++)
	{
		if(!strcmp(phone[i].name, name))
		{
		
			index=i;
		}
	}

	return index;  // override name ->  find last index
}

void print()
{
	int i;
	for(i=0; i<phone_size; i++)
	{
			printf("------------[%d]--------------\n", i+1);
			printf("name : %s \n", phone[i].name);
			printf("phone number  : %s \n", phone[i].phone);
	}
}
