#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

	/*We need exactly 3 arguments int exp mod*/
	if(argc != 4) {
		printf("Usage: %s int exp mod\n", argv[0]);
		return 1;
	}

	int intBits = sizeof(int) * 8;

	/*Get command line args*/
	int myInt = atoi(argv[1]);
	int exp = atoi(argv[2]);
	int mod = atoi(argv[3]);


	/*Check command line args*/
	if(myInt < 1 || exp < 1 || mod < 1) {
		printf("Please only use positive integers as input\n");
		return 1;
	}


	/*Generate square and multiply token*/
	int usedBits = intBits - __builtin_clz(exp); //clz count leading zeros

	//the intermediate (and eventually final) result
	int intermed = 1;

	for(int i = 1; i <= usedBits; i++) {
		//check if leading bit is 0 or 1
		int tmpExp = exp >> (usedBits - i);
		if((tmpExp & 1) == 1) {

			intermed = intermed * intermed % mod;
			intermed = intermed * myInt % mod;

		} else {
			intermed = intermed * intermed % mod;
		}
	}

	printf("Result: %d\n", intermed);
	return 0;
}
