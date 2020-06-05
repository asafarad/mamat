/*

  File: student.h

  Abstract:

    Student handling interface

*/
#ifndef _STUDENT_H_
#define _STUDENT_H_

/*Types*/
typedef struct Student_ Student, *PStudent;

/*Interface functions*/
PStudent StudentCreate(char* name, int age, int ID, char* faculty);

/*User functions*/
void printStudent(PElem Student);
PElem cloneStudent(PElem Student);
void destroyStudent(PElem Student);
BOOL compareStudents(PElem Student1, PElem Student2);

#endif
