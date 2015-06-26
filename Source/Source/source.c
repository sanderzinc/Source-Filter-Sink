/*
The Source program obtains a source text-file filename from its commandline,
opens the file, and reads and copies the file contents one character at a time directly to standard output (stdout).
When the file has been copied, Source terminates (closing all of its open file handles).
*/
#include<stdio.h>
#define DELAY_A_WHILE() {volatile int j; for(j=0;j<1000000;++j);}

int main(int argc, char *argv[])
{
	FILE *fin;

	if (argc != 2 || fopen_s(&fin, argv[1], "rb"))
	{
		fprintf(stderr, "Usage: source inputfilename\n");
		return(1);
	}

	//Read chars and copy to stdout
	while (1)
	{
		int ch;
		if ((ch = fgetc(fin)) == EOF)
			break;
		fputc(ch, stdout);
		//fputc(ch, stderr);
		DELAY_A_WHILE();
	}
	fclose(fin);
	return(0);
}