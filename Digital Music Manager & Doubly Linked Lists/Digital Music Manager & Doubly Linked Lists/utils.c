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
			/*if (target->next != NULL) {
				target->next->prev = newNode;
			}*/

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

ResultNode* createResultNode(ResultNode* target, int order, Node* result) {
	ResultNode* newNode = malloc(sizeof(ResultNode));

	if (target == NULL) {
		if (newNode != NULL) {
			newNode->result = result;
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
		newNode->result = result;

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
			/*if (target->next != NULL) {
				target->next->prev = newNode;
			}*/

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

void delay(int number_of_seconds)
{
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;

	// Storing start time
	clock_t start_time = clock();

	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds)
		;
}

int getNumericChoice(int numChoices) {

	int choice = 0;
	char buffer[4];

	while (choice == 0) {
		//scanf("%d", &choice);
		if (fgets(buffer, 3, stdin) != NULL) {

			choice = atoi(buffer);

			if (choice <= numChoices) {
				if (choice < 0) {
					choice = 0;
				}
				return choice;
			}
			else {
				choice = 0;
				printf("please enter a valid choice\n");
				strcpy(buffer, "\0\0\0");
			}

		}
		else {
			choice = 0;
			printf("please enter a valid choice\n");
			strcpy(buffer, "\0\0\0");
		}
	}
	
}

//todo: return null on empty input
char * getSearchString(char* buffer) {
	char temp[99];
	char* loc;
	if (fgets(temp, 98, stdin) != NULL) {
		printf("intput %s", temp);
		loc = strchr(temp, '\n');
		*loc = '\0';

		strcpy(buffer, temp);

	}
	else {
		printf("please enter a valid choice");
		strcpy(temp, "\0\0\0");
	}

	//check for empty
	if (*buffer == '\0') {
		return NULL;
	}
	else {
		return buffer;
	}
}

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

