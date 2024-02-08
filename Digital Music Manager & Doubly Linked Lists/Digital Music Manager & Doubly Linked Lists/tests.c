#include "tests.h"

void testInsert() {
	Node* testHead = NULL;
	Record test;
	strcpy(test.Artist, "Perry, Katy");
	strcpy(test.Album_title, "Witness");
	strcpy(test.Song_title, "Chained to the Rhythm");
	strcpy(test.Genre, "pop");
	test.Song_length.Minutes = 4;
	test.Song_length.Seconds = 36;
	//getNumeric choice function will return 0 for any value less than 0
	test.Plays = 0;
	//getNUmeric choice function has a ceiling passed as perameter
	//if ceiling is 5 it will return 5 for any input greater than 5
	test.Rating = 5;

	testHead = insert(testHead, test);

	printf("------TEST INSERT OUTPUT----------\n");
	display(testHead, NULL, 0, 0);
	printf("-----------END TEST-----------\n");
}

void testDelete() {
	Node* testHead = NULL;
	Record test;
	int i;

	strcpy(test.Artist, "Perry, Katy");
	strcpy(test.Album_title, "Witness");
	strcpy(test.Song_title, "Chained to the Rhythm");
	strcpy(test.Genre, "pop");
	test.Song_length.Minutes = 4;
	test.Song_length.Seconds = 36;
	//getNumeric choice function will return 0 for any value less than 0
	test.Plays = 3;
	//getNUmeric choice function has a ceiling passed as perameter
	//if ceiling is 5 it will return 5 for any input greater than 5
	test.Rating = 5;

	testHead = insert(testHead, test);

	printf("------TEST INSERT OUTPUT----------\n");
	display(testHead, NULL, 0, 0);
	printf("-----------END TEST-----------\n");

	i = delete(testHead, "Chained to the Rhythm");

	printf("------TEST DELETE OUTPUT----------\n");
	printf("NUM DELETED = %d\n", i);
	if (testHead == NULL) {
		printf("LIST SET TO NULL");
	}
	else {
		printf("HEAD IS NOT NULL\n");
		printf("address at head %p\n", testHead);
		printf("value: %s\n", testHead->data.Artist);
	}
	printf("-----------END TEST-----------\n");
}

void testShuffle() {
	Node* testHead = NULL;
	ResultNode* testRand = NULL;
	Record test;

	strcpy(test.Artist, "Perry, Katy");
	strcpy(test.Album_title, "Witness");
	strcpy(test.Song_title, "Chained to the Rhythm");
	strcpy(test.Genre, "pop");
	test.Song_length.Minutes = 4;
	test.Song_length.Seconds = 36;
	//getNumeric choice function will return 0 for any value less than 0
	test.Plays = 3;
	//getNUmeric choice function has a ceiling passed as perameter
	//if ceiling is 5 it will return 5 for any input greater than 5
	test.Rating = 5;

	testHead = insert(testHead, test);

	strcpy(test.Artist, "The Goons");
	strcpy(test.Album_title, "Gooning Around");
	strcpy(test.Song_title, "What I like to do");
	strcpy(test.Genre, "Butt-Rock");
	test.Song_length.Minutes = 4;
	test.Song_length.Seconds = 36;
	//getNumeric choice function will return 0 for any value less than 0
	test.Plays = 3;
	//getNUmeric choice function has a ceiling passed as perameter
	//if ceiling is 5 it will return 5 for any input greater than 5
	test.Rating = 5;

	testHead = insert(testHead, test);

	strcpy(test.Artist, "H3H3");
	strcpy(test.Album_title, "Live Selections");
	strcpy(test.Song_title, "Grimace Shake in Fortnight");
	strcpy(test.Genre, "Country");
	test.Song_length.Minutes = 4;
	test.Song_length.Seconds = 36;
	//getNumeric choice function will return 0 for any value less than 0
	test.Plays = 3;
	//getNUmeric choice function has a ceiling passed as perameter
	//if ceiling is 5 it will return 5 for any input greater than 5
	test.Rating = 5;

	testHead = insert(testHead, test);

	printf("------TEST INSERT OUTPUT----------\n");
	display(testHead, NULL, 1, 0);
	printf("-----------END TEST-----------\n");
	int testSet[] = { 3,1,2 };
	testRand = shuffle(testHead, testSet, 3);
	printf("------TEST SHUFFLE OUTPUT----------\n");
	printf("SHUFFLE ORDER: %d,%d,%d\n", testSet[0], testSet[1], testSet[2]);
	//printf("1. %s\n", testRand->result->prev->prev->prev->data.Artist);
	printf("1. %s\n", testRand->result->data.Artist);
	printf("2. %s\n", testRand->next->result->data.Artist);
	printf("3. %s\n", testRand->next->next->result->data.Artist);
	
	printf("-----------END TEST-----------\n");

	
}