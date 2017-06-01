#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct address{
	char name[40];
	struct address *next;
};

void store(struct address *item);
void display(struct address *top);
void delete(char *name);

struct address *head;

int main(){
	struct address *tmp;

	head= tmp=(struct address *) malloc(sizeof(struct address));
	strcpy (tmp->name, "Hong Gil Dong");
	store(tmp);

	tmp = (struct address *) malloc(sizeof (struct address));
	strcpy(tmp-> name, "Kim Chul Su");
	store(tmp);

	tmp = (struct address *) malloc(sizeof (struct address));
	strcpy(tmp-> name, "Kim Chul Su");
	store(tmp);
	
	display(head);

	delete("Kim Chul Su");

	display(head);
	return 0;
}

void store(struct address *item){
	static struct address *last = 0;

	if(last ==0)
		last = item;
	else
		last->next = item;

		item ->next =0;
		last = item;
}

void display(struct address *top)
{
	while(top){
		printf("%s\n", top-> name);
		top=top->next;
	}
}

void delete(char *name){
	struct address *current=head, *prev=0, *tmp;

	while(current)
	{
		if(!strcmp(current->name,name))
		{
			if(!prev)
				head = current->next;
			else
				prev->next=current->next;

			tmp = current;
			current = current ->next;
			free(tmp);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
