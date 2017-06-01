#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum CHOICE{PRINT=1, FIND, INSERT, QUIT};

struct Person{
	char name[40];
	char phone[100];
	struct Person *next;
};


int choice(char *reply);
void print(struct Person *top); // 모든 사람의 이름과 번호를 출력
int find(char *name);//노드 찾고 이름번호 출력
void insert(char *name, char *number); // 링크 가장 뒤에 삽입기능

struct Person *head=0;

int main(){
	char name[40];
	char phone[100];
	char reply[20];

	while(1)
	{
		puts("command(print, find, insert, quit)?");
		fgets(reply,20,stdin);
		reply[strlen(reply)-1] = '\0';

		switch(choice(reply))
		{
			case PRINT:
				print(head);
				break;
			case FIND:
				puts("name ?");
				fgets(name,40,stdin);
				name[strlen(name)-1] = '\0';
				if(!find(name))
					printf("not found name !\n");
				
				break;

			case INSERT:
				puts("name ?");
				fgets(name,40,stdin);
				name[strlen(name)-1] = '\0';

				puts("number ?");
				fgets(phone,100,stdin);
				phone[strlen(phone)-1] = '\0';
				
				insert(name, phone);

				break;
			case QUIT:
				return 0;

			default :
				printf("incorrect !\n");
		}
	}

	return 0;
}

void insert(char *name, char *number)
{
	static struct Person * last=0;
	struct Person *tmp =(struct Person *)malloc(sizeof(struct Person));
	strcpy(tmp->name, name);
	strcpy(tmp->phone, number);
	tmp->next = 0;

	if(!head)
	{

		head= tmp;
		last= tmp;
	}
	else
		last->next = tmp;

	last = tmp;
}

int find(char *name)
{
	struct Person *tmp=head;
	int count =0;

	while(tmp)
	{
		if(!strcmp(tmp->name, name))
		{
			printf("%s: %s \n",tmp->name, tmp->phone);
			count++;
		}
		tmp= tmp->next;
	}

	return count;     //몇번째 노드인지 리턴
}

void print(struct Person *top)
{
	int i=1;
	while(top){
		printf("[%d] %s: %s \n", i++, top->name, top->phone);
		top=top->next;
	}
}

int choice(char *reply)
{
	if(!strcmp(reply,"print"))
		return 1;
	else if(!strcmp(reply,"find"))
		return 2;
	else if(!strcmp(reply,"insert"))
		return 3;
	else if(!strcmp(reply,"quit"))
		return 4;
	else 
		return 0;
}


