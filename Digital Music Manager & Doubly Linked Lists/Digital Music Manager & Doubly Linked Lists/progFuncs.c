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

Node* store(Node* pHead) {
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
		fclose(outFile);
		return pHead;
	}
	else {
		printf("ERROR save- couldn't open file");
		return NULL;
	}
}


int display(Node* pHead, char* artist, int abv, int pause) {
	Node* temp = pHead;
	int printed = 0;
	int choice = 0;

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
	if (pause == 1) {
		printf("Enter 1 to exit\n");
		while (choice == 0) {
			scanf("%d", &choice);
		}
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
	char buffer[100];

	if (choices != NULL) {
		numRecords = display(pHead, artist, 1, 0);

		while (choice != (numRecords + 1)) {
			system("cls");
			numRecords = display(pHead, artist, 1, 0);
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
				getSearchString(choices->result->data.Artist);
				//need to reset choices if artist name is changed
				choices = getResultList(pHead, artist);
				break;
			case 2:
				printf("Album Title: --\n");
				getSearchString(choices->result->data.Album_title);
				break;
			case 3:
				printf("Song title: --\n");
				getSearchString(choices->result->data.Song_title);
				break;
			case 4:
				printf("Genre: --\n");
				getSearchString(choices->result->data.Genre);
				break;
			case 5:
				printf("Genre: --\n");
				getSearchString(choices->result->data.Genre);
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
		numRecords = display(pHead, artist, 1, 0);

		while (choice != (numRecords + 1)) {
			system("cls");
			numRecords = display(pHead, artist, 1, 0);
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

void play(Node* pHead, char* artist, int abv) {
	int printed = 0;

	Node* temp = pHead;

	if (pHead != NULL) {
		if (artist != NULL) {
			while (temp != NULL) {
				if (strcmp(artist, temp->data.Artist) == 0) {

					while (temp != NULL) {
						system("cls");
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
						//delay here
						delay(5);
						printed += 1;
						temp = temp->next;
					}
					
				}
				if (temp != NULL) {
					temp = temp->next;
				}
				
			}
		}
		else {
			while (temp != NULL) {
				system("cls");
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
				//delay here
				delay(5);
				temp = temp->next;

				printed += 1;
			}
		}
	}
	else {
		printf("ERROR display- pHead is NULL\n");

	}
}

int delete(Node* pHead, char* title) {
	Node* curr = pHead;
	Node* prev = NULL;
	Node* next = NULL;
	int i = 0;

	if (curr != NULL) {
		while (curr != NULL) {
			next = curr->next;
			if (strcmp(curr->data.Song_title, title) == 0) {
				next->prev = prev;
				if (prev != NULL) {
					prev->next = next;
				}
				free(curr);
				curr = next;
				next = curr->next;
				i++;
			}
			prev = curr;
			curr = next;
		}
	}
	else {
		printf("ERROR delete- pHead is NULL\n");
	}
	return i;
}

//run main menu
void menuMain() {
	mainBanner();
	printf("Reading from: %s\n", INFILE);
	pMenu("Main Menu", "load,store,display,edit,rate,play,delete,exit", 8);

	Node* pHead = NULL;

	int choice = 0;
	int tempNum = 0;
	char buffer[4];
	char cBuffer[100];

	while (choice != 8) {
		//scanf("%d", &choice);
		if (fgets(buffer, 3, stdin) != NULL) {

			choice = atoi(buffer);

			switch (choice) {
			case 1:
				//load
				printf("loading");
				pHead = load(INFILE);
				if (pHead != NULL) {
					system("cls");
					mainBanner();
					pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);
					printf("Load Successful -> %s\n", INFILE);
				}
				else {
					system("cls");
					mainBanner();
					pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);
					printf("Problem loading file, check filename\n");
				}
				break;
			case 2:
				//store
				printf("Saving");
				if (store(pHead) != NULL) {
					system("cls");
					mainBanner();
					pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);
					printf("Save Successful -> %s\n", OUTFILE);

				}
				else {
					system("cls");
					mainBanner();
					pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);
					printf("Problem saving file, check filename\n");
				}
				break;
			case 3:
				//display
				if (pHead != NULL) {
					printf("Enter artist to diplay; Enter for all\n");
					display(pHead, getSearchString(cBuffer), 0, 1);
					system("cls");
					mainBanner();
					pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);
				}
				else {
					system("cls");
					mainBanner();
					pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);
					printf("No records to display. Did you load any data?\n");
				}
				break;
			case 4:
				//edit
				if (pHead != NULL) {
					printf("Enter artist to edit records for; Enter for all\n");
					edit(pHead, getSearchString(cBuffer));
					system("cls");
					mainBanner();
					pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);
				}
				else {
					system("cls");
					mainBanner();
					pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);
					printf("No records to edit. Did you load any data?\n");
				}
				
				break;
			case 5:
				//rate
				if (pHead != NULL) {
					printf("Enter artist to rate; Enter for all\n");
					rate(pHead, getSearchString(cBuffer));
					system("cls");
					mainBanner();
					pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);
				}
				else {
					system("cls");
					mainBanner();
					pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);
					printf("No records to rate. Did you load any data?\n");
				}
				break;
				
			case 6:
				//play
				if (pHead != NULL) {
					printf("Enter artist to start playback from; Enter for begining\n");
					play(pHead, getSearchString(cBuffer), 0);
					system("cls");
					mainBanner();
					pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);
				}
				else {
					system("cls");
					mainBanner();
					pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);
					printf("No records to play. Did you load any data?\n");
				}
				break;
			case 7:
				//delete
				if (pHead != NULL) {
					printf("Enter song title to remove\n");
					tempNum = delete(pHead, getSearchString(cBuffer));
					system("cls");
					mainBanner();
					pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);
					if (tempNum != 0) {
						printf("%d Records removed.\n", tempNum);
					}
					else {
						printf("No matching records found.\n");
					}
					
				}
				else {
					system("cls");
					mainBanner();
					pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);
					printf("No records to delete. Did you load any data?\n");
				}
				break;
				
			case 8:
				//exit
				if (pHead != NULL) {
					printf("saving....");
					if (store(pHead) != NULL) {
						printf("Save Successful -> %s", OUTFILE);

					}
					else {
						printf("Problem saving file, check filename");
					}
					delay(3);
				}
				else {
					printf("No record data loaded.\n ");
					printf("No data will be saved\n ");
					delay(3);
				}
				break;
			default:
				printf("please enter a valid choice\n");
				
			}

		}
		else {
			printf("please enter a valid choice\n");
			strcpy(buffer, "\0\0\0");
		}


	}
}