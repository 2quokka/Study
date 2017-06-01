#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct mystr {
	struct mystr *next, *prev;
	int age;
	char name[64];
	char *message;
};

struct mystr *head;

void add(int age, char *name, char* message);
void delete(char *name);
void print();
void reverseLink();

int main(void)
{
	int choice, age;
	char name[30], message[100];

	while(1)
	{
		fputs("?",stdout);
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
				printf("name : ");
				scanf("%s", name);
				getchar();
				printf("age : ");
				scanf("%d",&age);
				getchar();
				printf("message : ");
				scanf("%s", message);

				add(age, name, message);

				break;
			case 2:
				printf("name : ");
				scanf("%s", name);
				getchar();
				
				delete(name);

				break;
			case 3:
				print();
				break;
			case 4:
				reverseLink();
				break;
		}
	}

	return 0;
}

void add(int age, char *name, char* message)
{
	struct mystr *tmp = malloc(sizeof(struct mystr));
	struct mystr *last;

	tmp->age= age;
	strcpy(tmp->name, name);
	tmp->message = malloc(strlen(message)+1);
	strcpy(tmp->message, message);

	if(!head)
		head = tmp;
	else
	{
		for(last=head;last->next;last=last->next);

		last->next=tmp;
		tmp->prev=last;

		last=tmp;
	}

}
void delete(char *name)
{
	struct mystr *ptr;

	for(ptr=head;ptr;ptr=ptr->next)
	{
		if(!strcmp(ptr->name, name))
		{
			if(ptr->prev == 0){
				head= ptr->next;
				if(head)
					head->prev = 0;
			}
			else
			{
				ptr->prev->next= ptr->next;

				if(ptr->next)
					ptr->next->prev=ptr->prev;
			}

			free(ptr->message);
			free(ptr);
		}
	}
}

void print(){
	struct mystr * ptr;
	int i;
	for(i=1, ptr=head;ptr;i++, ptr=ptr->next)
		printf("---[%d]---\nname: %s \nage : %d \nmessage:%s\n",i,ptr->name,ptr->age,ptr->message);
}

void reverseLink(){
	struct mystr * ptr, *ptr_n, *tmp;

	for(ptr = head ; ptr ; ptr = ptr_n)
	{
		ptr_n = ptr->next;

		tmp=ptr->next;
		ptr->next = ptr->prev;
		ptr->prev = tmp;
	}

	while(head->prev)
		head= head->prev;
}
