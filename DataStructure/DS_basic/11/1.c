#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum CHOICE{PRINT=1, FIND, INSERT, DELETE, SAVE, INIT, QUIT};

struct Person{
	char name[40];
	char phone[100];
	struct Person *next;
};


int choice(char *reply);
void print(struct Person *top);
int find(char *name);
void insert(char *name, char *number);

//update function
void delete(char *name);
int save(char *fileName);
int initialize(char *fileName);

struct Person *head=0;

int main(int argc, char *argv[])
{
	char name[40];
	char phone[100];
	char reply[20];

	while(1)
	{
		puts("command(print, find, insert, delete, save, init, quit)?");
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

			case DELETE:
				puts("name ?");
				fgets(name,40,stdin);
				name[strlen(name)-1] = '\0';
				delete(name);
				break;
			
			case SAVE:
				save(argv[1]);
				break;
			
			case INIT:
				initialize(argv[1]);
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

	if(head ==0)
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

	return count;
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
	else if(!strcmp(reply,"delete"))
		return 4;
	else if(!strcmp(reply,"save"))
		return 5;
	else if(!strcmp(reply,"init"))
		return 6;
	else if(!strcmp(reply,"quit"))
		return 7;
	else 
		return 0;
} 

void delete(char *name)
{
	struct Person * tmp=head;
	struct Person * prev=0;

	while(tmp)
	{
		if(!strcmp(tmp->name, name))
		{
			if(tmp==head)
				head=tmp->next;
			else
				prev->next = tmp->next;	

			free(tmp);
			puts("delete complete!\n");
			break;       // 첫번째 발견한 노드만 삭제
		}
		prev = tmp;
		tmp=tmp->next;
	}
}

int save(char *fileName)
{
	struct Person * node = head;
	FILE *fp;
	if((fp=fopen(fileName,"w"))==NULL)
	{
		fprintf(stderr, "save file open fail ...\n");
		return -1;
	}

	while(node)
	{
		fprintf(fp, "%s %s\n",node->name, node->phone);
		node=node->next;
	}
	fclose(fp);

	return 0;
}

int initialize(char *fileName)
{
	struct Person * node = head;
	struct Person * nodeNext = 0;
	FILE *fp;
	char name[40], phone[100];

	//delete
	while(node)  //모든 노드 삭제
	{
		free(node);
		node=nodeNext;
		if(node)   // 삭제 할 노드가 남았을 경우
			nodeNext=node->next;
	}

	if((fp = fopen(fileName,"r"))==NULL) 
	{
		fprintf(stderr, "read file open fail...\n");
		return -1;
	}

	while(fscanf(fp,"%s %s", name, phone)==2) //fscanf 반환값은 읽어들인 필드의 개수
	{
		insert(name, phone);	
	}

	return 0;

	fclose(fp);
}


