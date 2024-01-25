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
			strtok(buffer, ",");

			//copy artist //TODO BROKEN
			if (*start == '"') {
				strcpy(tempR.Artist, start);
				start = strtok(NULL, ",");
				strcpy(tempR.Artist, start);
				start = strtok(NULL, ",");
			}
			else {
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
			//copy rating
			tempR.Rating = atoi(start);

			target = createNode(target, 0, tempR);
		}
		//// get head of list to return
		//while (target->prev != NULL) {
		//	target = target->prev;
		//}

		return target;

		fclose(infile);
	}
	else {
		printf("ERROR load- couldn't open file");
	}

	return NULL;
}


void display(Node* pHead, char* artist) {
	Node* temp = pHead;

	if (pHead != NULL) {
		if (artist != NULL) {
			while (temp != NULL) {
				if (strcmp(artist, temp->data.Artist) == 0) {
					printf("----------\n");
					printf("Artist: %s\n", temp->data.Artist);
					printf("Album: %s\n", temp->data.Album_title);
					printf("Song: %s\n", temp->data.Song_title);
					printf("Genre: %s\n", temp->data.Genre);
					printf("Length: %d:%d\n", temp->data.Song_length.Minutes, temp->data.Song_length.Seconds);
					printf("Rating: %d\n", temp->data.Rating);
					printf("----------\n");
					temp = temp->next;
				}
			}
		}
		else {
			while (temp != NULL) {
				printf("----------\n");
				printf("Artist: %s\n", temp->data.Artist);
				printf("Album: %s\n", temp->data.Album_title);
				printf("Song: %s\n", temp->data.Song_title);
				printf("Genre: %s\n", temp->data.Genre);
				printf("Length: %d:%d\n", temp->data.Song_length.Minutes, temp->data.Song_length.Seconds);
				printf("Rating: %d\n", temp->data.Rating);
				printf("----------\n");
				temp = temp->next;
			}
		}
	}
	else {
		printf("ERROR display- pHead is NULL\n");
	}
}