#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define INT_MAX 2147483647


bool IsZero(long input);
bool Equal(long x, long y);
long Successor(long);
long Add(long x, long y);
long Subtract(long x, long y);

int main(int argc, char** args){
	long x = atoi(args[1]);
	long y = atoi(args[2]);

	printf("Is %ld zero? %s\n", x, IsZero(x) ? "True" : "False");
	printf("Is %ld zero? %s\n", y, IsZero(y) ? "True" : "False");
	printf("Does %ld equal %ld? %s\n", x, y, Equal(x, y) ? "True" : "False");
	printf("%ld's next nember is %ld\n", x, Successor(x));
	printf("%ld's next nember is %ld\n", y, Successor(y));
	printf("%ld + %ld = %ld\n", x, y, Add(x, y));
	printf("%ld - %ld = %ld\n", x, y, Subtract(x, y));
	
	return 0;

}

bool IsZero(long x){
	return (x == 0) ? true : false;
}

bool Equal(long x, long y){
	return (x == y) ? true : false;
}

long Successor(long x){
	return (x + 1 < INT_MAX) ? x + 1 : x;
}

long Add(long x, long y){
	if (INT_MAX - x < y){
		return INT_MAX;
	}

	else return x + y;
}

long Subtract(long x, long y){
	return (x > y) ? x - y : 0;
}
