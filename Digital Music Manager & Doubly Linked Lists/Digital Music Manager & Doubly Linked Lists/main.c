#include "utils.h"
#include "progFuncs.h"

int main() {

	/*TEST*/
	Duration dur1 = {
		3,35
	};

	Record t1 = {
		"Swift, Taylor",
		"1989",
		"Shake it Off",
		"Pop",
		dur1,
		12,
		5
	};

	Duration dur2 = {
		5,44
	};

	Record t2 = {
		"Rancid",
		"Rancid",
		"salvation",
		"Punk",
		dur2,
		50,
		5
	};

	Duration dur3 = {
		5,44
	};

	Record t3 = {
		"the Goons",
		"Gooners paradise",
		"Goonin around",
		"Gay",
		dur3,
		100,
		1
	};

	Node* pHead = createNode(NULL, 0, t3);
	createNode(pHead, 1, t1);
	createNode(pHead, 1, t2);
	createNode(pHead, 1, t3);
	pHead = createNode(pHead, 0, t1);
	
	display(pHead, NULL);

	//menuMain();

	return 0;
}