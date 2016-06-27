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
	int myIntLen = strlen(argv[1]);
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
	

	//prepare human readable equation
	char *equation = malloc((myIntLen + 1) * usedBits * 2);
	sprintf(equation, "1");
	int bracketCnt = 0;

	//the intermediate (and eventually final) result
	int intermed = 1;

	char *tmpMulti = malloc(myIntLen + 2);
	sprintf(tmpMulti, "*%d", myInt);

	for(int i = 1; i <= usedBits; i++) {
		//check if leading bit is 0 or 1
		int tmpExp = exp >> (usedBits - i);
		if((tmpExp & 1) == 1) {

			strcat(equation, ")^2");
			bracketCnt++;
			strcat(equation, tmpMulti);

			int tmpIntermed = intermed;
			int squareint = intermed * intermed;
			intermed = squareint % mod;
			printf("%d^2\t= %d\tmod %d = %d\n", tmpIntermed, squareint, mod, intermed);

			tmpIntermed = intermed;
			int intTimesInt = intermed * myInt;
			intermed = intTimesInt % mod;
			printf("%d * %d\t= %d\tmod %d = %d\n", tmpIntermed, myInt, intTimesInt, mod, intermed);

		} else {

			strcat(equation, ")^2");
			bracketCnt++;

			int tmpIntermed = intermed;
			int squareint = intermed * intermed;
			intermed = squareint % mod;
			printf("%d^2\t= %d\tmod %d = %d\n", tmpIntermed, squareint, mod, intermed);
		}
	}

	printf("\n\n");

	char *openBrackets = malloc(bracketCnt * 2);
	for(int i = 0; i < bracketCnt; i++) {
		strcat(openBrackets, "(");
	}
	printf("%s%s mod %d\n\n", openBrackets, equation, mod);

	printf("Result: %d\n=======\n", intermed);

	return 0;
}
