/*

  File: party.c

  Abstract:

    Party handling implementation

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "party.h"
#include "voter.h"

#define MAX_PARTY_NAME      20


/*
 * Types
 */
typedef struct _Party
{
    char Party[MAX_PARTY_NAME];
    int NumVoters;

    struct _Party* pNext;
} Party;


/*
 * Prototypes
 */
void PrintError(char* pPartyName);


/*
 * Statics
 */
static Party* PartyList = NULL;


/*

  Function: AddVote

  Abstract:

    Records the chosen party of a voter

  Parameters:

    pPartyName - The party that received the vote

  Returns: A pointer to the party name that is guaranteed to stay constant until 'FreeParties'
           is called. If the party name is illegal, we fail the operation and return NULL.

*/


char* AddVote(char* pPartyName)
{
    bool IsExist = FALSE;
    Party* currParty = NULL;
    Party* pParty = NULL;
    for (pParty = PartyList; pParty; pParty = pParty->pNext) {
        if (!strcmp(pPartyName, pParty->Party)) {
            IsExist = TRUE;
            currParty = pParty;
        }
    }
    if (!IsExist) {
        char* makaf;
        char* tmpParty = pPartyName;
        while ((makaf = strchr(tmpParty, '-')) != NULL) {
            if (makaf) {
                char letterAfterMakaf = *(makaf + sizeof(char));
                if ((letterAfterMakaf < 'A') || (letterAfterMakaf > 'Z')) {
                    PrintError(pPartyName);
                    return NULL;
                }
            }
            tmpParty = makaf + sizeof(char);
        }
        

        Party* newParty;
        newParty = (Party*)malloc(sizeof(Party));
        if (newParty == NULL) {
            FreeVoters();
            FreeParties();
            exit (-1);
        }
        strcpy(newParty->Party, pPartyName);
        newParty->NumVoters = 1;
        newParty->pNext = PartyList;
        PartyList = newParty;
        return newParty->Party;
    }
    else {
        currParty->NumVoters++;
        return currParty->Party;
    }
    printf("\n");
}


/*

  Function: FreeParties

  Abstract:

    Frees all memory in the party database

*/
void FreeParties()
{
    Party* CurrParty = NULL;

    while (PartyList != NULL) {
        CurrParty = PartyList;
        PartyList = PartyList->pNext;
        free(CurrParty);
    }
}


/*

  Function: PrintResult

  Abstract:

    Reports the election result so far

*/
void PrintResult()
{
    Party* pParty;

    printf("Election Results\n");
    printf("Party | Num. of Voters\n");

    /*
     * Iterate the party list and print the current number of voters for each party
     */
    for (pParty = PartyList; pParty; pParty = pParty->pNext)
        printf("%s %d\n", pParty->Party, pParty->NumVoters);
    printf("\n");
}


void PrintError(char* pPartyName)
{
    printf("ERROR: '%s' is invalid\n", pPartyName);
}
