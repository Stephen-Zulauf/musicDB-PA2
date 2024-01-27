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

//TODO:modification of song length
void edit(Node* pHead, char* artist) {
	ResultNode* choices = getResultList(pHead, artist);
	int numRecords = 0;
	int choice = 0;
	int fChoice = 0;
	int i;
	char buffer[30];

	if (choices != NULL) {
		numRecords = display(pHead, artist, 1);

		while (choice != (numRecords + 1)) {
			system("cls");
			numRecords = display(pHead, artist, 1);
			printf("Enter record number to edit(1-%d), %d to exit\n", numRecords, (numRecords + 1));
			choice = getNumericChoice(numRecords + 1);
			if (choice == (numRecords + 1)) {
				break;
			}
			for (i = 1; i < choice; i++) {
				choices = choices->next;
			}
			system("cls");
			printf("----EDIT-----\n");
			printf("Artist: %s\n", choices->result->data.Artist);
			printf("Album: %s\n", choices->result->data.Album_title);
			printf("Song: %s\n", choices->result->data.Song_title);
			printf("Genre: %s\n", choices->result->data.Genre);
			printf("Length: %d:%d\n", choices->result->data.Song_length.Minutes, choices->result->data.Song_length.Seconds);
			printf("Plays: %d\n", choices->result->data.Plays);
			printf("Rating: %d\n", choices->result->data.Rating);
			pMenu("Edit which field?", "Artist,Album,Song,Genre,Length,Plays,Rating", 7);
			fChoice = getNumericChoice(7);

			switch (fChoice) {
			case 1:
				printf("Artist: --\n");
				fgets(choices->result->data.Artist, 29, stdin);
				//need to reset choices if artist name is changed
				choices = getResultList(pHead, artist);
				break;
			case 2:
				printf("Album Title: --\n");
				fgets(choices->result->data.Album_title, 29, stdin);
				break;
			case 3:
				printf("Song title: --\n");
				fgets(choices->result->data.Song_title, 29, stdin);
				break;
			case 4:
				printf("Genre: --\n");
				fgets(choices->result->data.Genre, 29, stdin);
				break;
			case 5:
				printf("Genre: --\n");
				fgets(choices->result->data.Genre, 29, stdin);
				break;
			case 6:
				printf("Plays: --\n");
				fgets(buffer, 29, stdin);
				choices->result->data.Plays = atoi(buffer);
				break;
			case 7:
				printf("Rating: --\n");
				fgets(buffer, 29, stdin);
				choices->result->data.Rating = atoi(buffer);
				break;
			}

			if (choices != NULL) {
				while (choices->prev != NULL) {
					choices = choices->prev;
				}
			}

			choice = 0;
			fChoice = 0;
		}

	}
	else {
		printf("No Records matching artist found.\n");
	}
}

void rate(Node* pHead, char* artist) {
	ResultNode* choices = getResultList(pHead, artist);
	int numRecords = 0;
	int choice = 0;
	int i;
	char buffer[30];

	if (choices != NULL) {
		numRecords = display(pHead, artist, 1);

		while (choice != (numRecords + 1)) {
			system("cls");
			numRecords = display(pHead, artist, 1);
			printf("Enter record number to rate(1-%d), %d to exit\n", numRecords, (numRecords + 1));
			choice = getNumericChoice(numRecords + 1);
			if (choice == (numRecords + 1)) {
				break;
			}
			for (i = 1; i < choice; i++) {
				choices = choices->next;
			}
			system("cls");
			printf("----RATE-----\n");
			printf("Artist: %s\n", choices->result->data.Artist);
			printf("Album: %s\n", choices->result->data.Album_title);
			printf("Song: %s\n", choices->result->data.Song_title);
			printf("Genre: %s\n", choices->result->data.Genre);
			printf("Length: %d:%d\n", choices->result->data.Song_length.Minutes, choices->result->data.Song_length.Seconds);
			printf("Plays: %d\n", choices->result->data.Plays);
			printf("Rating: %d\n", choices->result->data.Rating);
			printf("\n");
			printf("Enter a rating 1-5;\n");
			fgets(buffer, 2, stdin);
			choices->result->data.Rating = atoi(buffer);

			if (choices != NULL) {
				while (choices->prev != NULL) {
					choices = choices->prev;
				}
			}

			choice = 0;
		}

	}
	else {
		printf("No Records matching artist found.\n");
	}
}