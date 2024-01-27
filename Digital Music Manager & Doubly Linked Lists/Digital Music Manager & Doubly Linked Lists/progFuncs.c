#include "progFuncs.h"

/*
typedef struct record {
	char Artist[30];
	char Album_title[30];
	char Song_title[30];
	char Genre[30];
	Duration Song_length;
	int Rating;
}Record;

typedef struct duration {
	int Minutes;
	int Seconds;
}Duration;
*/

//load csv file to linked list
//returns head of list created/ null if error or no input
Node* load(char* fileName) {
	FILE* infile = fopen(fileName, "r");

	char buffer[200] = "\0";
	char* start = buffer;

	Node* target = NULL;
	
	Duration tempD;
	Record tempR;

	if (infile != NULL) {
		while (fgets(buffer, 200, infile) != NULL) {
			int i = 0;

			start = buffer;

			//copy artist
			if (*start == '\"') {
				start = strtok(buffer, "\"");
				strcpy(tempR.Artist, start);
				start = strtok(NULL, "\"");
				start++;
				strtok(start, ",");
			}
			else {
				strtok(buffer, ",");
				strcpy(tempR.Artist, start);
				start = strtok(NULL, ",");
			}

			//copy album
			strcpy(tempR.Album_title, start);
			start = strtok(NULL, ",");
			//copy song title
			strcpy(tempR.Song_title, start);
			start = strtok(NULL, ",");
			//copy Genre
			strcpy(tempR.Genre, start);
			start = strtok(NULL, ",");
			//copy duration
			sscanf(start, "%d:%d", &tempD.Minutes, &tempD.Seconds);
			tempR.Song_length = tempD;
			start = strtok(NULL, ",");
			//copy plays
			tempR.Plays = atoi(start);
			start = strtok(NULL, ",");
			//copy rating
			tempR.Rating = atoi(start);

			target = createNode(target, 1, tempR);
			//printf("%d\n", target->prev);
		}

		//return front of list created
		if (target != NULL) {
			while (target->prev != NULL) {
				target = target->prev;
			}
		}
		
		return target;

		fclose(infile);
	}
	else {
		printf("ERROR load- couldn't open file");
	}

	return NULL;
}

void store(Node* pHead) {
	FILE* outFile = fopen(OUTFILE, "w");

	Node* temp = pHead;

	if (outFile != NULL) {
		while (temp != NULL) {
			fprintf(outFile, "\"");
			fputs(temp->data.Artist,outFile);
			fprintf(outFile, "\",");
			fputs(temp->data.Album_title, outFile);
			fprintf(outFile, ",");
			fputs(temp->data.Song_title, outFile);
			fprintf(outFile, ",");
			fputs(temp->data.Genre, outFile);
			fprintf(outFile, ",");
			fprintf(outFile, "%d:%d",temp->data.Song_length.Minutes, temp->data.Song_length.Seconds);
			fprintf(outFile, ",");
			fprintf(outFile, "%d",temp->data.Plays);
			fprintf(outFile, ",");
			fprintf(outFile, "%d\n",temp->data.Rating);
			temp = temp->next;
		}
	}
	else {
		printf("ERROR save- couldn't open file");
	}
}


int display(Node* pHead, char* artist, int abv) {
	Node* temp = pHead;
	int printed = 0;

	if (pHead != NULL) {
		if (artist != NULL) {
			while (temp != NULL) {
				if (strcmp(artist, temp->data.Artist) == 0) {
					if (abv == 1) {
						printf("----%d-----\n", (printed + 1));
						printf("Artist: %s\n", temp->data.Artist);
						printf("Song: %s\n", temp->data.Song_title);
						printf("\n");
					}
					else {
						printf("----------\n");
						printf("Artist: %s\n", temp->data.Artist);
						printf("Album: %s\n", temp->data.Album_title);
						printf("Song: %s\n", temp->data.Song_title);
						printf("Genre: %s\n", temp->data.Genre);
						printf("Length: %d:%d\n", temp->data.Song_length.Minutes, temp->data.Song_length.Seconds);
						printf("Plays: %d\n", temp->data.Plays);
						printf("Rating: %d\n", temp->data.Rating);
						printf("\n");
					}
					

					printed += 1;
				}
				temp = temp->next;
			}
		}
		else {
			while (temp != NULL) {
				if (abv == 1) {
					printf("----%d-----\n", (printed + 1));
					printf("Artist: %s\n", temp->data.Artist);
					printf("Song: %s\n", temp->data.Song_title);
					printf("\n");
				}
				else {
					printf("----------\n");
					printf("Artist: %s\n", temp->data.Artist);
					printf("Album: %s\n", temp->data.Album_title);
					printf("Song: %s\n", temp->data.Song_title);
					printf("Genre: %s\n", temp->data.Genre);
					printf("Length: %d:%d\n", temp->data.Song_length.Minutes, temp->data.Song_length.Seconds);
					printf("Plays: %d\n", temp->data.Plays);
					printf("Rating: %d\n", temp->data.Rating);
					printf("\n");
				}
				temp = temp->next;

				printed += 1;
			}
		}
	}
	else {
		printf("ERROR display- pHead is NULL\n");
		
	}
	return printed;
}

ResultNode* getResultList(Node* pHead, char* artist) {

	//list to track choices
	ResultNode* choices = NULL;
	
	//main list
	Node* temp = pHead;

	if (pHead != NULL) {
		if (artist != NULL) {
			while (temp != NULL) {
				if (strcmp(artist, temp->data.Artist) == 0) {

					//create node for result
					choices = createResultNode(choices, 1, temp);
				}
				temp = temp->next;
			}
		}
		else {
			while (temp != NULL) {

				//create node for result
				choices = createResultNode(choices, 1, temp);

				temp = temp->next;
			}
		}

		//return front of result list created
		if (choices != NULL) {
			while (choices->prev != NULL) {
				choices = choices->prev;
			}
		}
		
	}
	else {
		printf("ERROR getEditList- pHead NULL\n");
	}

	return choices;

}

ResultNode* getEdit(ResultNode* choices, int numRecords) {
	ResultNode* result = choices;

	int choice = 0;
	char buffer[4];
	int i;

	while (choice == 0) {
		//scanf("%d", &choice);
		if (fgets(buffer, 3, stdin) != NULL) {

			choice = atoi(buffer);

			if (choice < numRecords && choice != 0) {
				for (i = 1; i < choice; i++) {
					result = result->next;
				}
				return result;
			}
			else {
				choice = 0;
				printf("please enter a valid choice");
				strcpy(buffer, "\0\0\0");
			}

		}
		else {
			choice = 0;
			printf("please enter a valid choice");
			strcpy(buffer, "\0\0\0");
		}
	}
	return NULL;
}

void edit(Node* pHead, char* artist) {
	ResultNode* choices = getResultList(pHead, artist);
	ResultNode* choice = NULL;
	int numRecords = 0;

	if (choices != NULL) {

		while (choices != NULL) {
			printf("----%d-----\n", (numRecords + 1));
			printf("Artist: %s\n", choices->result->data.Artist);
			printf("Song: %s\n", choices->result->data.Song_title);
			printf("\n");

			numRecords++;

			choices = choices->next;
		}
		if (choices != NULL) {
			while (choices->prev != NULL) {
				choices = choices->prev;
			}
		}
		printf("Enter record number to edit(1-%d)\n", numRecords);
		choice = getEdit(choices, numRecords);
		printf("----EDIT-----\n");
		printf("Artist: %s\n", choice->result->data.Artist);
		printf("Song: %s\n", choice->result->data.Song_title);
		printf("\n");
	}
	else {
		printf("No Records matching artist found.\n");
	}
}