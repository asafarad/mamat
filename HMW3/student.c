/*

  File: student.c

  Abstract:

	Student handling implementation

*/
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Type definitions:
typedef struct Student_* PStudent;

typedef struct Student_ {
	char* name;
	int age, ID;
	char* faculty;
} Student;

//Interface functions:

/*
  Function Name	:	StudentCreate
  Description	:	Create an object of type Student
  Parameters	:	Student's name, age, ID and what facutly s/he studies at
  Return Value	:	A pointer to the newly created object
  */

PStudent StudentCreate(char* name, int age, int ID, char* faculty) {
	if (name == NULL || faculty == NULL) //missing input check for age and ID
		return NULL;
	PStudent NewStudent;
	NewStudent = (PStudent)malloc(sizeof(Student));
	if (NewStudent == NULL)
		return NULL;
	NewStudent->name = (char*)malloc(1+strlen(name));
	if (NewStudent->name == NULL) {
		free(NewStudent);
		return NULL;
	}
	strcpy(NewStudent->name, name);
	NewStudent->age = age;
	NewStudent->ID = ID;
	NewStudent->faculty = (char*)malloc(1+strlen(faculty));
	if (NewStudent->faculty == NULL) {
		free(NewStudent->name);
		free(NewStudent);
		return NULL;
	}
	strcpy(NewStudent->faculty, faculty);

	return NewStudent;
}

//User fuctions:

/*
  Function Name	:	printStudent
  Description	:	prints a student's details
  Parameters	:	a pointer to a specific element (which represents a student)
  Return Value	:	-
  */

void printStudent(PElem pStudent) {
	//Input check:
	if (pStudent == NULL)
		return;

	//Casting the input to type PStudent:
	PStudent ThisStudent = (PStudent)pStudent;

	printf("Name: %s, Age: %d, ID: %d, Faculty: %s\n", ThisStudent->name, ThisStudent->age, ThisStudent->ID, ThisStudent->faculty);
}

/*
  Function Name	:	cloneStudent
  Description	:	duplicate a student object to a new student
  Parameters	:	a pointer to a specific element (which represents a student)
  Return Value	:	a pointer to the new student
  */


PElem cloneStudent(PElem pStudent) {
	if (pStudent == NULL)
		return NULL;
	PStudent OldStudent = (PStudent)pStudent;
	PStudent NewStudent;
	NewStudent = (PStudent)malloc(sizeof(Student));
	if (NewStudent == NULL)
		return NULL;
	NewStudent->name = (char*)malloc(1+strlen(OldStudent->name));
	if (NewStudent->name == NULL) {
		free(NewStudent);
		return NULL;
	}
	strcpy(NewStudent->name, OldStudent->name);
	NewStudent->age = OldStudent->age;
	NewStudent->ID = OldStudent->ID;
	NewStudent->faculty = (char*)malloc(1+strlen(OldStudent->faculty));
	if (NewStudent->faculty == NULL) {
		free(NewStudent->name);
		free(NewStudent);
		return NULL;
	}
	strcpy(NewStudent->faculty, OldStudent->faculty);
	
	return (PElem)NewStudent;
}

/*
  Function Name	:	destroyStudent
  Description	:	deletes a student
  Parameters	:	a pointer to a specific element (which represents a student)
  Return Value	:	-
  */


void destroyStudent(PElem pStudent) {

	//Iput check:
	if (pStudent == NULL) 
		return;
	PStudent Student = (PStudent)pStudent;
	free(Student->name);
	free(Student->faculty);
	free(Student);
}

/*
  Function Name	:	CompareStudent
  Description	:	states whether two students are the same one, based on their ID
  Parameters	:	a pointer to two specific elements (that represent students)
  Return Value	:	TRUE if it's the same student, otherwise FALSE
  */

BOOL compareStudents(PElem pStudent1, PElem pStudent2) {
 
	//Input check:
	if (pStudent1 == NULL || pStudent2 == NULL)
		return FALSE;

	PStudent Student1 = (PStudent)pStudent1;
	PStudent Student2 = (PStudent)pStudent2;
	if (Student1->ID != Student2->ID)
		return FALSE;

	return TRUE;
}

