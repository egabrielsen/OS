#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

bool isNumber(char*);
int factorial(int);

int main(int argc, char* argv[]) {
	if (argc == 1) {
		printf("%s\n", "Wrong number of arguments. Expected: ./a.out <something>");
	} else {
		int number = atoi(argv[1]);
		if (number > 12) {
			printf("%s\n", "Overflow");
		} else if (isNumber(argv[1])) {
			printf("%d\n", factorial(number));
		} else {
			printf("%s\n", "Huh?");
		}
	}
}

bool isNumber(char number[])
{
  int i = 0;
  if (number[0] == '-') //if number is negative 'doubt it'
      i = 1;
  for (; number[i] != 0; i++)
  {  
    if (!isdigit(number[i]))
      return false;
  }
  return true;
}

int factorial(int n)
{
  if (n == 0)
    return 1;
  else
    return(n * factorial(n-1));
}