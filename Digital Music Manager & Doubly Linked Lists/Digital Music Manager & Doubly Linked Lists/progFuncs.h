#ifndef PROGFUNCS_H
#define PROGFUNCS_H

#include"utils.h"

//load csv file to linked list
//returns head of list created/ null if error or no input
Node* load(char* fileName);

//prints records. Needs pointer to head of list. TODO: accepts a search term for artist
void display(Node* pHead, char* artist);





#endif // !PROGFUNCS_H

