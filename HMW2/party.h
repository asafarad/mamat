/*

  File: party.h

  Abstract:

    Party handling interface

*/


#ifndef _PARTY_H_
#define _PARTY_H_

typedef enum { FALSE, TRUE } bool;
typedef struct _Party Party;

char* AddVote(char* pPartyName);
void FreeParties();
void PrintResult();

#endif /* _PARTY_H_ */
