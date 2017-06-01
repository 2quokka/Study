#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

enum CHOICE{ADD,DELETE,PRINT,QUIT};

struct mystr{
	struct mystr *next;
	int age;
	char name[64];
	char *message;
};

void add(int age, char *name, char *msg);
void delete(char *name);
void print(void);
void menu(void);

struct mystr * head =0;

int main()
{
	int age;
	char name[64];
	char message[1024];
	int choice;

while(1)
{
	menu();
	scanf("%d", &choice);
	getchar();
	switch(choice)
	{
		case ADD:
			printf("insert age : ");
			scanf("%d", &age);
			getchar();
			printf("insert name :");
			fgets(name,sizeof(name),stdin);
			printf("insert message :");
			fgets(message,sizeof(message), stdin);
			
			add(age, name, message);

			break;
		case DELETE:
			printf("insert name :");
			fgets(name,sizeof(name), stdin);
			delete(name);

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

void add(int age, char *name, char *msg)
{
	struct mystr *last=head;
	struct mystr *p=0;
	p = (struct mystr *)malloc(sizeof(struct mystr));
	p->next=0;
	p->age=age;
	strcpy(p->name, name);

	// msg 
	p->message = (char *)malloc(strlen(msg) +1);
	strcpy(p->message, msg);

	if(!head)
		head=p;
	else
	{
		while(last->next)
			last = last->next;

		last->next=p;
	}
}
	
void delete(char *name)
{
	struct mystr *prev=0, *p=head;

	if(head==0)
		return;
	
	while(p->next)
	{
		if(!strcmp(p->name,name))
		{
			if(p==head)
			{
				if(p->next == 0)
					head=0;
				else
					head=p->next;
			}
			else
				prev->next = p->next;

			break;
		}

		prev= p;
		p= p->next;
	}

	free(p->message);
	free(p);
}

void print(void)
{
	struct mystr *p= head;
	while(p)
	{
		printf("---------------------------\n");
		printf("age = %d \n", p->age);
		printf("name = %s \n", p->name);
		printf("message : %s \n", p->message);
		printf("---------------------------\n");
		p = p->next;
	}
}

void menu(void)
{
	printf("0:ADD\n");
	printf("1:DELETE\n");
	printf("2:PRINT\n");
	printf("3:QUIT\n");
	printf("? ");
}
