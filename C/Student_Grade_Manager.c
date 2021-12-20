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

/*	Type definitions	*/

typedef struct {
	char id[CONF_ID_LENGTH];
	char name[CONF_NAME_LENGTH];
	int *grade;
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

	gStatus.student = assert(malloc(sizeof(Student) *
					gStatus.studentNum));
	gStatus.gradePool = assert(malloc(sizeof(int) *
				   	  gStatus.studentNum *
					  gStatus.examNum));
	for (int i = 0;i < gStatus.studentNum;i++)
		gStatus.list[i].grade = gStatus.gradePool +
				        gStatus.examNum * i;

	print_msg("Then type the infomation in this format:");
	print_msg("StudentName ID Grade1 Grade2 ....");

	for (int count = 0;count < gStatus.studentNum;count++) {
		scanf("%s %s",gStatus.list.name,gStatus.list.id);
		for (int i = 0;i < gStatus.examNum;i++)
			scanf("%d",gStatus.list[i].grade + i);
	}

	print_msg("Well done");

	return;
}

void destroy(void)
{
	free(gStatus.student);
	free(gStatus.gradePool);
	return;
}

int main(void)
{
	init();
	getchar();
	destroy();
	return 0;
}
