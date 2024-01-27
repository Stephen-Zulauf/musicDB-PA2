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
void display(Node* pHead, char* artist);









#endif // !PROGFUNCS_H

