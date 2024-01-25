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