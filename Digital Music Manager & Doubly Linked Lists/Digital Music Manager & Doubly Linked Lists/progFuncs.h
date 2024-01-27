#ifndef PROGFUNCS_H
#define PROGFUNCS_H

#include"utils.h"

//load csv file path at INFILE to linked list
//returns head of list created/ null if error or no input
Node* load(char* fileName);

//stores linked list to csv at OUTFILE. Will write from pHead given. overwrites previous data.
void store(Node* pHead);

// If NUll is passed for artist prints all records from head pHead passed
//If artist passed will print all exact matches from pHead passed
// if abv == 0 full record printed. if abv == 1 abreviated record with number printed
//returns number of records printed
int display(Node* pHead, char* artist, int abv);

//creates a list of nodes that match artist string, or returns all results if NULL passed
//returns head of reults list, Null if no reults found TODO:deallocate search list
ResultNode* getResultList(Node* pHead, char* artist);

//edit displays all records that match artist string then prompts which one to edit
//if null passed for artist will list all records
void edit(Node* pHead, char* artist);

//edit but only for rate
void rate(Node* pHead, char* artist);







#endif // !PROGFUNCS_H

