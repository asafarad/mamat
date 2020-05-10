/*

  File: voter.c

  Abstract:

    Voter handling implementation

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "voter.h"
#include "party.h"


/*
 * Types
 */
typedef struct _Voter
{
    char* pName;
    char* pParty;
    int ID;

    struct _Voter* pNext;
} Voter;


/*
 * Statics
 */
static Voter* VoterList = NULL;


/*

  Function: AddVoter

  Abstract:

    Adds a new voter to the database

  Parameters:

    pName    - The voter's name
    pSurname - The voter's surname
    ID		 - The voter's ID (assumed to be unique)
    pParty   - The voter's vote (assumed NOT to be changed)

  Returns: --

*/
void AddVoter(char* pName, char* pSurname, int ID, char* pParty)
{
       
    Voter* NewVoter;
    NewVoter = (Voter*)malloc(sizeof(Voter));
    if (NewVoter == NULL) {
        FreeVoters();
        FreeParties();
        exit(-1);
    }
    char* buffName;
    int pNameLen = strlen(pName);
    int pSurnameLen = strlen(pSurname);
    int totLen = pNameLen + pSurnameLen + 1;
    buffName = (char*)malloc(totLen);
    if (buffName == NULL) {
        FreeVoters();
        FreeParties();
        exit(-1);
    }
    
    strcpy(buffName, pName);
    strcat(buffName, " ");
    strcat(buffName, pSurname);

    int i;
    for (i = 0; buffName[i]!= '\0'; i++) {
        buffName[i] = toupper(buffName[i]);
    }
    NewVoter->pName = buffName;
    NewVoter->ID = ID;
    NewVoter->pParty = pParty;

    Voter* pVoter = VoterList;
    Voter* pVoterPrev = NULL;
    while (pVoter != NULL && pVoter->ID < ID) {
        pVoterPrev = pVoter;
        pVoter = pVoter->pNext;
    }
    if (pVoter == VoterList) {
        NewVoter->pNext = VoterList;
        VoterList = NewVoter;
        return;
    }
    pVoterPrev->pNext = NewVoter;
    NewVoter->pNext = pVoter;
 }



/*

  Function: FreeVoters

  Abstract:

    Frees all memory in the voter data-base

*/
void FreeVoters()
{
    Voter* CurrVoter = NULL;

    while (VoterList != NULL) {
        CurrVoter = VoterList;
        VoterList = VoterList->pNext;
        free(CurrVoter->pName);
        free(CurrVoter);
    }
}


/*

  Function: PrintVoters

  Abstract:

    Prints all registered voters

*/
void PrintVoters()
{
    Voter* pVoter;

    printf("Registered Voters\n");
    printf("ID | Name | Vote\n");

    /*
     * Iterate the voter list and print the details of each voter
     */
    for (pVoter = VoterList; pVoter; pVoter = pVoter->pNext)
    {
        printf("%d %s %s\n", pVoter->ID, pVoter->pName, pVoter->pParty);
    }
    printf("\n");
}
