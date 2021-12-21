/*
	As an exception,this file is in public domain.
	Do what you want.
*/

// Because of the usage of this file,many asserts will be used.
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

/*	Constant values		*/
#define CONF_ID_LENGTH 16
#define CONF_NAME_LENGTH 32
#define CONF_COL 6

/*	Type definitions	*/

typedef struct {
	char id[CONF_ID_LENGTH];
	char name[CONF_NAME_LENGTH];
	int *grade;
	long int total;
}Student;

/*	Global variables	*/

struct {
	Student *list;
	int examNum;
	int studentNum;
	int *gradesPool;
}gStatus;

/*	function prototypes	*/
void init(void);
void destroy(void);
int get_input(const char *msg);
void print_msg(const char *msg);

int get_input(const char *msg)
{
	printf("%s: ",msg);
	int retVal = 0;
	scanf("%d",&retVal);
	return retVal;
}

void print_msg(const char *msg)
{
	puts(msg);
	return;
}

void init(void)
{
	gStatus.examNum	   = get_input("Enter the number of examinations");
	gStatus.studentNum = get_input("Enter the number of the students");

	gStatus.list	  = malloc(sizeof(Student) *
				   gStatus.studentNum);
	gStatus.gradesPool = malloc(sizeof(int) *
			   	    gStatus.studentNum *
				    gStatus.examNum);
	assert(gStatus.list);
	assert(gStatus.gradesPool);
	for (int i = 0;i < gStatus.studentNum;i++)
		gStatus.list[i].grade = gStatus.gradesPool +
				        gStatus.examNum * i;

	print_msg("Then type the infomation in this format:");
	print_msg("StudentName ID Grade1 Grade2 ....");

	for (int count = 0;count < gStatus.studentNum;count++) {
		scanf("%s %s",gStatus.list[count].name,gStatus.list[count].id);
		gStatus.list[count].total = 0;
		for (int i = 0;i < gStatus.examNum;i++) {
			scanf("%d",gStatus.list[count].grade + i);
			gStatus.list[count].total += gStatus.list[count].grade[i];
		}
	}

	print_msg("Well done");

	return;
}

void max_and_min(void)
{
	int maxIdx = 0;
	int minIdx = 0;
	for (int i = 1;i < gStatus.studentNum;i++) {
		if (gStatus.list[maxIdx].total < gStatus.list[i].total) {
			maxIdx = i;
		} else if (gStatus.list[minIdx].total > gStatus.list[i].total) {
			minIdx = i;
		}
	}

	printf("The best one:\nName: %s\t ID: %s\t Grade: %ld\n",gStatus.list[maxIdx].name,
	       gStatus.list[maxIdx].id,gStatus.list[maxIdx].total);
	printf("The worst one:\nName: %s\t ID: %s\t Grade: %ld\n",gStatus.list[minIdx].name,
	       gStatus.list[minIdx].id,gStatus.list[minIdx].total);

	return;
}

static void print_table_part(int start)
{
	printf("Exam\\Student\t");

	for (int i = start;i < start + CONF_COL && i < gStatus.studentNum;i++)
		printf("%s\t",gStatus.list[i].name);
	putchar('\n');

	int *data = gStatus.list[start].grade;
	for (int count = 0;count < gStatus.examNum;count++) {
		printf("%d\t\t",count + 1);
		int *grade = data + count;
		for (int i = start;i < start + CONF_COL && i < gStatus.studentNum;i++) {
			printf("%d\t",*grade);
			grade += CONF_COL;
		}
		putchar('\n');
	}
	return;
}

void print_table(void)
{
	for (int i = 0;i < gStatus.studentNum;i += CONF_COL)
		print_table_part(i);
	return;
}

void find_grade(void)
{
	printf("Type the student's ID: ");
	char id[CONF_ID_LENGTH] = {0};
	scanf("%s",id);
	id[strlen(id)] = '\0';

	int i = 0;
	for (;i < gStatus.studentNum;i++) {
		if (!strcmp(gStatus.list[i].id,id))
			break;
	}

	if (i == gStatus.studentNum) {
		printf("Student with ID %s does not exist",id);
	} else {
		Student *s = gStatus.list + i;
		for (int i = 0;i < gStatus.examNum;i++)
			printf("%d\n",s->grade[i]);
	}
	return;
}

void destroy(void)
{
	free(gStatus.list);
	free(gStatus.gradesPool);
	return;
}

int main(void)
{
	init();

	int choice = 0;
	while (choice != 6) {
		puts("Student Grade Manager");
		puts("1. Find the best and worst ones");
		puts("2. Print Grade Table");
		puts("3. Look for One's Grades");
		puts("6. Exit");
		choice = get_input("Enter your choice");

		if (choice == 1) {
			max_and_min();
		} else if (choice == 2) {
			print_table();
		} else if (choice == 3) {
			find_grade();
		}
	}

	destroy();
	return 0;
}
