#include "utils.h"

//create node and util function if (NULL passed for target create new list)
//order: 0 in front of target, 1 behind
//if pHead is passed as target with 0 then node will become new head
//returns NULL on error
Node* createNode(Node* target, int order, Record data) {

	Node* newNode = malloc(sizeof(Node));

	if (target == NULL) {
		if (newNode != NULL) {
			newNode->data = data;
			newNode->prev = NULL;
			newNode->next = NULL;
			return newNode;
		}
		else {
			printf("ERROR createNode; failed to allocate space for node");
		}
		
	}
	else if (newNode != NULL) {

		//copy data to new node
		newNode->data = data;

		//insert before
		if (order == 0) {

			//set newNode prev to target prev
			newNode->prev = target->prev;
			newNode->next = target;
			//set prev nodes next to new node
			if (target->prev != NULL) {
				target->prev->next = newNode;
			}
			target->prev = newNode;
			
			return newNode;
		}
		//insert after
		else if (order == 1) {
			newNode->next = target->next;
			newNode->prev = target;
			target->next = newNode;
			if (target->next != NULL) {
				target->next->prev = newNode;
			}

			return newNode;
		}
		else {
			printf("ERROR createNode; invalid order");
		}
	}
	else {
		printf("ERROR createNode; failed to allocate space for node");
	}

	return NULL;
}

////converts time string "0:00" to two integers
//void convertTimeST(char* timeS, int* minutes, int* seconds) {
//	char* buffer[20];
//	char* start = buffer;
//
//	strcpy(buffer, timeS);
//	strtok(buffer, ":");
//	*minutes = atoi(start);
//	start = strtok(NULL, ":");
//	*seconds = atoi(start);
//
//}

//enter title each option seperated by comma (limit 400 chars)
void pMenu(char* title, char* options, int numOptions) {
	int i;
	char buffer[400];
	strcpy(buffer, options);
	char* start = buffer;

	strtok(buffer, ",");
	
	printf("\n");
	printf("%s\n", title);
	printf("--------------------\n");

	for (i = 0; i < numOptions; i++) {
		printf("(%d)%s\n", (i + 1), start);
		start = strtok(NULL, ",");
	}
	printf("--------------------\n");
}

//run main menu
void menuMain() {
	pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);

	int choice = 0;
	char buffer[4];

	while (choice != 7) {
		//scanf("%d", &choice);
		if (fgets(buffer, 3, stdin) != NULL) {

			choice = atoi(buffer);

			switch (choice) {
			case 1:
				//load
				printf("loading");
				break;
			case 2:
				//store
				printf("store");
				break;
			case 3:
				//display
				printf("display");
				break;
			case 4:
				//edit
				printf("edit");
				break;
			case 5:
				//rate
				printf("rate");
			case 6:
				//play
				printf("play");
				break;
			case 7:
				//exit
				printf("exit");
				break;
			default:
				printf("please enter a valid choice");
			}

		}
		else {
			printf("please enter a valid choice");
			strcpy(buffer, "\0\0\0");
		}

		
	}
}