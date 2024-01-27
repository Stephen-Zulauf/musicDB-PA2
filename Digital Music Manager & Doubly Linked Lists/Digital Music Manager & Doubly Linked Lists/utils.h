#ifndef UTILS_H
#define UTILS_H

#define _CRT_SECURE_NO_WARNINGS

#define INFILE "test.csv"
#define OUTFILE "test.csv"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct duration {
	int Minutes;
	int Seconds;
}Duration;

typedef struct record {
	char Artist[30];
	char Album_title[30];
	char Song_title[30];
	char Genre[30];
	Duration Song_length;
	int Plays;
	int Rating;
}Record;

typedef struct node {
	Record data;
	struct node* next;
	struct node* prev;
}Node;

typedef struct resultNode {
	struct node* result;
	struct resultNode* next;
	struct resultNode* prev;
}ResultNode;

//create node and util function if (NULL passed for target create new list)
//order: 0 in front of target, 1 behind
//if pHead is passed as target with 0 then returned node will become new head
//returns address of created node NULL on error
Node* createNode(Node* target, int order, Record data);

//result node identical to create node but points to a result
ResultNode* createResultNode(ResultNode* target, int order, Node* result);

//enter title and options seperated by comma (limit 400 chars for options)
void pMenu(char* title, char* options, int numOptions);

//run main menu
void menuMain();







#endif // !UTILS_H

