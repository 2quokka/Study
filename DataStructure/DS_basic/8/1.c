#include <stdio.h>
#include <string.h>

#define PERSON 3

typedef struct Student{
	char name[128];
	int num;
	int kor;
	int eng;
	double avg;
}Student;

void readData(Student *);
void calAverage(Student *);
void printData(Student * );

int main()
{
	Student student[PERSON];

	readData(student);
	calAverage(student);
	printData(student);

	return 0;
}

void readData(Student *ptr) // 입력시 예외처리
{
	int i;
	char name[128];
	int num,kor,eng;

	for(i=0; i<PERSON; i++)
	{
		printf("-------------[  %d  ]------------\n", i+1);
		printf("name: ");
		fgets(name, sizeof(ptr[i].name), stdin);
		printf("num : ");
		scanf("%d", &num);
		while(1)
		{
			printf("kor : ");
			scanf("%d", &kor);
			if(kor <= 100 && kor >= 0)
				break;
			else
				printf("incorrected score! \n");
		}
		while(1)
		{
			printf("eng : ");
			scanf("%d", &eng);
			if(eng <= 100 && eng >= 0)
				break;
			else
				printf("incorrected score! \n");
		}

		getchar();


		ptr[i].avg=.0;
	}

	for(i=0; i<PERSON; i++)
	{
		strcpy((ptr+i)->name, name);
		(ptr+i)->num = num;
		(ptr+i)->kor = kor;
		(ptr+i)->eng = eng;
	}
}

void calAverage(Student *ptr)
{
	int i;
	for(i=0; i<PERSON; i++)
	{
		ptr[i].avg = (double)(ptr[i].kor + ptr[i].eng) / 2;
	}
}

void printData(Student * ptr)
{
	int i;

	printf("*/*/*/*/*/*/*/*/*/*/print */*/*/*/*/*/*/*/*/*/\n");
	for(i=0; i<PERSON; i++)
	{
		printf("-------------[  %d  ]------------\n", i+1);
		printf("name : %s \n", ptr[i].name);
		printf("number: %d \n", ptr[i].num);
		printf("kor-score : %d \n", ptr[i].kor);
		printf("eng-score : %d \n", ptr[i].eng);
		printf("average : %g \n", ptr[i].avg);
	}
}
