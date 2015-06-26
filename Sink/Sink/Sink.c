/*
The Sink program obtains a destination text-file filename from its commandline,
opens the file for writing, and then reads characters one at a time from the standard input file(stdin)
and writes each incoming character directly to the destination sink file.
*/
#include<stdio.h>
#define DELAY_A_WHILE() {volatile int j; for(j=0;j<1000000;++j);}

int main(int argc, char *argv[])
{
	FILE *fout;

	if (argc != 2 || fopen_s(&fout, argv[1], "wb"))
	{
		fprintf(stderr, "Usage: source outputfilename\n");
		return(1);
	}

	//Read chars and copy to stdout
	while (1)
	{
		int ch;
		if ((ch = getchar()) == EOF)
			break;
		fputc(ch, fout);
		DELAY_A_WHILE();
	}
	fclose(fout);
	return(0);
}