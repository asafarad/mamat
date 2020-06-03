#ifndef _STUDENT_H_
#define _STUDENT_H_

typedef struct Student_ Student, *PStudent;

/*Interface functions*/
PStudent StudentCreate(char* name, int age, int ID, char* faculty);
void printStudent(PStudent Student);
PStudent cloneStudent(PStudent Student);
void destroyStudent(PStudent Student);
BOOL compareStudents(PStudent Student1, PStudent Student2);


#endif
