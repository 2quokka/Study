#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person{
	struct Person *next;
	struct Person *prev;
	char name[50];
	int age;
}Person;

void addNode(char *name, int age);
void changeName(char *name, int age);
int countNodes(int age);
void print();
void removeAll();

Person *head;

int main(void)
{
	addNode("kim", 20);
	addNode("park", 21);
	addNode("choi", 22);
	print();

	changeName("lee", 21);
	print();

	addNode("sun", 22);
	printf("the number of nodes = %d\n", countNodes(22));
	print();

	removeAll();

	print();

	return 0;
}


void addNode(char *name, int age){
	Person * ptr;
	Person * tmp = malloc(sizeof(Person));
	strcpy(tmp->name, name);
	tmp->age = age;
	tmp->next = 0;
	
	if(!head)
	{
		tmp->prev = 0;
		head= tmp;
	}
	else
	{
		for(ptr = head; ptr->next ; ptr = ptr->next);

		ptr ->next = tmp;
		tmp->prev = ptr;
	}
}
void changeName(char *name, int age){
	Person *ptr;/*{{{*/

	for(ptr = head; ptr; ptr = ptr->next)
	{
		if(ptr->age == age)
		{
			strcpy(ptr->name, name);
			break;
		}
	}/*}}}*/
}
int countNodes(int age){/*{{{*/

	Person *ptr;
	int count=0;

	for(ptr = head; ptr; ptr = ptr->next)
	{
		if(ptr->age == age)
			count++;
	}

	return count;
}/*}}}*/
void print()
{//{{{
	Person * ptr;
	int i=1;
	for(ptr = head; ptr; ptr = ptr->next)
	{
		printf("[%d] name : %s age : %d \n", i++, ptr->name, ptr->age);
	}
 }//}}}
void removeAll()
{//{{{
	Person *rmv, *ptr=head;

	while(ptr)
	{
		rmv=ptr;
		ptr = ptr->next;

		free(rmv);
	}

	head=NULL;
}//}}}
