/*
The Filter program does not utilize any filename commandline parameters. 
Instead, Filter reads a text file from standard input (stdin) and writes to standard output (stdout) a copy 
of the input with all upper-case letters converted to lower-case. 
Filter specifically must be designed to read one character, convert it, output it, and then loop until the incoming data is finished.
*/
#include<stdio.h>
#include<ctype.h>
#define DELAY_A_WHILE() {volatile int j; for(j=0;j<1000000;++j);}

int main(int argc, char *argv[])
{
	while (1)
	{
		int ch;
		if ((ch = getchar()) == EOF)
			break;
		fputc(tolower(ch), stdout);
		DELAY_A_WHILE();
	}
	return(0);
}