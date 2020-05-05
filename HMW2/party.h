/*

  File: party.h

  Abstract:

    Party handling interface

*/


#ifndef _PARTY_H_
#define _PARTY_H_
typedef enum {false, true} bool;

char* AddVote(char* pPartyName);
void FreeParties();
void PrintResult();
void PrintError(char* pPartyName);

#endif /* _PARTY_H_ */
