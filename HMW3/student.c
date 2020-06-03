#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student_* PStudent;

typedef struct Student_ {
	char* name;
	int age, ID;
	char* faculty;
} Student;

PStudent StudentCreate(char* name, int age, int ID, char* faculty) {
	if (name == NULL || faculty == NULL) //missing input check for age and ID
		return NULL;
	PStudent NewStudent;
	NewStudent = (PStudent)malloc(sizeof(Student));
	if (NewStudent == NULL)
		return NULL;
	strcpy(NewStudent->name, name);
	NewStudent->age = age;
	NewStudent->ID = ID;
	strcpy(NewStudent->faculty, faculty);

	return NewStudent;
}
void printStudent(PStudent Student) {
	if (Student == NULL)
		return;
	printf("Name: %s, Age: %d, ID: %d, faculty %s\n", Student->name, Student->age, Student->ID, Student->faculty);
}

PStudent cloneStudent(PStudent Student) {
	if (Student == NULL)
		return NULL;
	PStudent NewStudent;
	NewStudent = (PStudent)malloc(sizeof(Student));
	if (NewStudent == NULL)
		return NULL;
	strcpy(NewStudent->name, Student->name);
	NewStudent->age = Student->age;
	NewStudent->ID = Student->ID;
	strcpy(NewStudent->faculty, Student->faculty);
	
	return NewStudent;
}

void destroyStudent(PStudent Student) {
	if (Student == NULL)
		return;
	free(Student);
}

BOOL compareStudents(PStudent Student1, PStudent Student2) {

	if (Student1 == NULL && Student2 == NULL)
		return TRUE; 
	else if (Student1 == NULL)
		return FALSE;
	else if (Student2== NULL)
		return FALSE;

	if (Student1->name != Student2->name)
		return FALSE;
	if (Student1->age != Student2->age)
		return FALSE;
	if (Student1->ID != Student2->ID)
		return FALSE;
	if (Student1->faculty != Student2->faculty)
		return FALSE;

	return TRUE;
}

