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

Node* insert(Node* pHead, Record newData) {
	Node* insert = createNode(pHead, 0, newData);
	if (insert == NULL) {
		printf("ERROR insert create node failed");
	}

	return insert;
}

Node* menuInsert(Node* pHead) {
	Node* newHead;
	Record tempRecord;
	char cBuffer[100];

	system("cls");
	printf("Please enter details for new record:\n");
	printf("Artist Name:\n");
	strcpy(tempRecord.Artist, getSearchString(cBuffer));
	printf("Album Title:\n");
	strcpy(tempRecord.Album_title, getSearchString(cBuffer));
	printf("Song Title:\n");
	strcpy(tempRecord.Song_title, getSearchString(cBuffer));
	printf("Genre:\n");
	strcpy(tempRecord.Genre, getSearchString(cBuffer));
	printf("Song length, Minutes:\n");
	tempRecord.Song_length.Minutes = atoi(getSearchString(cBuffer));
	printf("Song length, seconds:\n");
	tempRecord.Song_length.Seconds = atoi(getSearchString(cBuffer));
	printf("Number of plays\n");
	tempRecord.Plays = getNumericChoice(999);
	printf("Rating\n");
	tempRecord.Rating = getNumericChoice(5);

	newHead = insert(pHead, tempRecord);
	if (newHead != NULL) {
		printf("---------------");
		printf("created new Record");
		printf("---------------");
		delay(3);
		return newHead;
	}
	else {
		printf("failed to create new record");
		delay(3);
		return pHead;
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
				/// <summary>
				/// NULL ACCESS VIOLATION
				/// </summary>
				if (next != NULL) {
					next->prev = prev;
				}
				if (prev != NULL) {
					prev->next = next;
				}
				if (curr != NULL) {
					next = curr->next;
				}
				free(curr);
				curr = NULL;
				curr = next;
				
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

//method = 1 artist, 2 album, 3 rating, 4 playtime
void sort(Node* pHead, int method) {
	Node* curr = pHead;
	Node* loopPos = pHead;
	Node* smallest = pHead;
	Record tempData;

	switch (method) {
	case 1:
		//artist
		while (loopPos != NULL) {

			curr = loopPos;
			smallest = loopPos;

			while (curr != NULL) {
				if (strcmp(curr->data.Artist, smallest->data.Artist) < 0) {
					smallest = curr;
				}
				curr = curr->next;
			}

			tempData = loopPos->data;
			loopPos->data = smallest->data;
			smallest->data = tempData;

			//advance loop
			loopPos = loopPos->next;
		}
		break;
	case 2:
		//album title
		while (loopPos != NULL) {

			curr = loopPos;
			smallest = loopPos;

			while (curr != NULL) {
				if (strcmp(curr->data.Album_title,smallest->data.Album_title) < 0) {
					smallest = curr;
				}
				curr = curr->next;
			}

			tempData = loopPos->data;
			loopPos->data = smallest->data;
			smallest->data = tempData;

			//advance loop
			loopPos = loopPos->next;
		}
		break;
	case 3:
		//rating
		while (loopPos != NULL) {

			curr = loopPos;
			smallest = loopPos;

			while (curr != NULL) {
				if (curr->data.Rating < smallest->data.Rating) {
					smallest = curr;
				}
				curr = curr->next;
			}

			tempData = loopPos->data;
			loopPos->data = smallest->data;
			smallest->data = tempData;

			//advance loop
			loopPos = loopPos->next;
		}
		break;
	case 4:
		//plays
		while (loopPos != NULL) {

			curr = loopPos;
			smallest = loopPos;

			while (curr != NULL) {
				if (curr->data.Plays < smallest->data.Plays) {
					smallest = curr;
				}
				curr = curr->next;
			}

			tempData = loopPos->data;
			loopPos->data = smallest->data;
			smallest->data = tempData;

			//advance loop
			loopPos = loopPos->next;
		}
		break;
	default:
		//artist
		while (loopPos != NULL) {

			curr = loopPos;
			smallest = loopPos;

			while (curr != NULL) {
				if (strcmp(curr->data.Artist, smallest->data.Artist) > 0) {
					smallest = curr;
				}
				curr = curr->next;
			}

			tempData = loopPos->data;
			loopPos->data = smallest->data;
			smallest->data = tempData;

			//advance loop
			loopPos = loopPos->next;
		}
		break;
	}
}

// prompt user for sorting method
void menuSort(Node* pHead) {
	int choice = 0;
	char buffer[2];
	system("cls");
	pMenu("Sort by:", " Artist Name, Album Title, Rating, Number of Plays, Display Records, Exit", 6);

	while (choice != 6) {
		if (fgets(buffer, 2, stdin) != NULL) {
			choice = atoi(buffer);

			switch (choice) {
			case 1:
				sort(pHead, 1);
				system("cls");
				pMenu("Sort by:", " Artist Name, Album Title, Rating, Number of Plays, Display Records, Exit", 6);
				printf("Sorted by Artist name");
				break;
			case 2:
				sort(pHead, 2);
				system("cls");
				pMenu("Sort by:", " Artist Name, Album Title, Rating, Number of Plays, Display Records, Exit", 6);
				printf("Sorted by Album Title");
				break;
			case 3:
				sort(pHead, 3);
				system("cls");
				pMenu("Sort by:", " Artist Name, Album Title, Rating, Number of Plays, Display Records, Exit", 6);
				printf("Sorted by Rating");
				break;
			case 4:
				sort(pHead, 4);
				system("cls");
				pMenu("Sort by:", " Artist Name, Album Title, Rating, Number of Plays, Display Records, Exit", 6);
				printf("Sorted by Number of plays");
				break;
			case 5:
				system("cls");
				display(pHead, NULL, 0, 1);
				system("cls");
				pMenu("Sort by:", " Artist Name, Album Title, Rating, Number of Plays, Display Records, Exit", 6);
				break;
			default:
				buffer[0] = '\0';
				buffer[1] = '\0';
			}
			
		}
	}
}

//shuffle
ResultNode* shuffle(Node* pHead, int* test, int testSize) {

	int size = 0;
	int i, j, k;
	Node* temp = pHead;
	ResultNode* resultHead = NULL;


	if (test == NULL) {
		//regular operation
		//get size of list
		while (temp != NULL) {
			size++;
			temp = temp->next;
		}

		//make random order from size and create result node
		while (size > 0) {
			i = rand() % size;

			for (j = 1; j < i; j++) {
				if (temp != NULL) {
					temp = temp->next;
				}
			}

			resultHead = createResultNode(resultHead, 1, temp);

			size -= 1;
			temp = pHead;

		}

	}
	else {
		//use test order
		for (i = 0; i < testSize; i++) {
			j = test[i];

			for (k = 1; k < j; k++) {
				if (temp != NULL) {
					temp = temp->next;
				}
			}

			resultHead = createResultNode(resultHead, 1, temp);
			temp = pHead;
		}
	}

	//return front 
	if (resultHead != NULL) {
		while (resultHead->prev != NULL) {
			resultHead = resultHead->prev;
		}
	}
	

	return resultHead;

}

void shufflePlay(ResultNode* pHead, int abv) {
	int printed = 0;

	ResultNode* temp = pHead;

	if (temp != NULL) {
		while (temp != NULL) {
			system("cls");
			if (abv == 1) {
				printf("----%d-----\n", (printed + 1));
				printf("Artist: %s\n", temp->result->data.Artist);
				printf("Song: %s\n", temp->result->data.Song_title);
				printf("\n");
			}
			else {
				printf("----------\n");
				printf("Artist: %s\n", temp->result->data.Artist);
				printf("Album: %s\n", temp->result->data.Album_title);
				printf("Song: %s\n", temp->result->data.Song_title);
				printf("Genre: %s\n", temp->result->data.Genre);
				printf("Length: %d:%d\n", temp->result->data.Song_length.Minutes, temp->result->data.Song_length.Seconds);
				printf("Plays: %d\n", temp->result->data.Plays);
				printf("Rating: %d\n", temp->result->data.Rating);
				printf("\n");
			}
			//delay here
			delay(3);
			temp = temp->next;

			printed += 1;
		}
	}
	else {
		printf("ERROR shufflePlay- pHead is NULL\n");

	}
}

//run main menu
void menuMain() {
	mainBanner();
	printf("Reading from: %s\n", INFILE);
	pMenu("Main Menu", "load,store,display,edit,rate,play,delete,sort,insert,exit", 10);

	Node* pHead = NULL;

	int choice = 0;
	int tempNum = 0;
	char buffer[4];
	char cBuffer[100];

	while (choice != 10) {
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
				//sort
				if (pHead != NULL) {
					menuSort(pHead);
					system("cls");
					mainBanner();
					pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);
				}
				else {
					system("cls");
					mainBanner();
					pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);
					printf("No records to sort. Did you load any data?\n");
				}
				break;
			case 9:
				//insert
				pHead = menuInsert(pHead);
				system("cls");
				mainBanner();
				pMenu("Main Menu", "load,store,display,edit,rate,play,exit", 7);
				break;
				
			case 10:
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
				printf("please enter a choice\n");
				
			}

		}
		else {
			printf("please enter a valid choice\n");
			strcpy(buffer, "\0\0\0");
		}


	}
}