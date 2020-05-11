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
    // create new node for the linked list of voters
    Voter* NewVoter;
    NewVoter = (Voter*)malloc(sizeof(Voter));
    if (NewVoter == NULL) { // if allocation failed- free all data
        FreeVoters();
        FreeParties();
        exit(-1);
    }
    // create a buffer for the voter's name
    char* buffName;
    int pNameLen = strlen(pName); // length of name
    int pSurnameLen = strlen(pSurname); // length of surname
    int totLen = pNameLen + pSurnameLen + 1; // total name length, with space
    buffName = (char*)malloc(totLen);
    if (buffName == NULL) { // if allocation failed- free all data
        FreeVoters();
        FreeParties();
        exit(-1);
    }
    // cat name+space+surname 
    strcpy(buffName, pName);
    strcat(buffName, " ");
    strcat(buffName, pSurname);

    //change each char to uppaer case according to the demands
    int i;
    for (i = 0; buffName[i]!= '\0'; i++) {
        buffName[i] = toupper(buffName[i]);
    }
    // updating the fields of struct
    NewVoter->pName = buffName;
    NewVoter->ID = ID;
    NewVoter->pParty = pParty;

    // find the place of the new voter in the linked list by the ID sorting
    Voter* pVoter = VoterList; // tmp pointer to run over the linked list
    Voter* pVoterPrev = NULL; // tmp pointer for the previous node in the linked list
    while (pVoter != NULL && pVoter->ID < ID) {
        // if the list node isn't empty and ID is smaller than the new ID- increment the pointers
        pVoterPrev = pVoter; 
        pVoter = pVoter->pNext;
    }
    if (pVoter == VoterList) {
        // if pVoter stopped at the head of the list(list is empty or new ID is the smallest), need to update the head pointer
        NewVoter->pNext = VoterList;
        VoterList = NewVoter;
        return;
    }
    // if pVoter stopped inside the list- insert new voter to its right location
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
        // while pointer doesn't point to the tail of list
        CurrVoter = VoterList; // save pointer to current node
        VoterList = VoterList->pNext; // update to the next node
        free(CurrVoter->pName); // first, free name buffer of the current node
        free(CurrVoter); // then, free the node itself
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
