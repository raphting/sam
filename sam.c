#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Multiplies two longs and aborts if overflow happens, otherwise find the result in the pointer res
void check_overflow_mul(long a, long b, long * res) {
	if(__builtin_smull_overflow(a, b, res)) {
		printf("We experienced a 'long' overflow. Please try smaller input values.\n");
		exit(1);
	}
}


int main(int argc, char *argv[]) {

	/*We need exactly 3 arguments int exp mod*/
	if(argc != 4) {
		printf("Usage: %s int exp mod\n", argv[0]);
		return 1;
	}

	int intBits = sizeof(long) * 8;

	/*Get command line args*/
	long myInt = atol(argv[1]);
	long exp = atol(argv[2]);
	long mod = atol(argv[3]);


	/*Check command line args*/
	if(myInt < 1 || exp < 1 || mod < 1) {
		printf("Please only use positive integers as input.\n");
		return 1;
	}


	/*Generate square and multiply token*/
	int usedBits = intBits - __builtin_clz(exp); //clz count leading zeros

	//the intermediate (and eventually final) result
	long intermed = 1;

	for(int i = 1; i <= usedBits; i++) {
		//check if leading bit is 0 or 1
		long tmpExp = exp >> (usedBits - i);

		check_overflow_mul(intermed, intermed, &intermed); 
		intermed = intermed % mod;

		if((tmpExp & 1) == 1) {
			check_overflow_mul(intermed, myInt, &intermed);
			intermed = intermed % mod;
		}
	}

	printf("Result: %ld\n", intermed);
	return 0;
}

