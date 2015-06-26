//Lab 5 : Concurrent Processes with Pipe Interprocess Communication : Source-Filter-Sink
//By Trenton Sanders
#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<WinBase.h>

#define MAX_CMD_LENGTH 200

void executeProcess(char *cmdline, HANDLE hOutput, HANDLE hInput);

int main(int argc, char *argv[])
{
	//Buffers for command lines for processes
	char source[MAX_CMD_LENGTH];
	char filter[MAX_CMD_LENGTH];
	char sink[MAX_CMD_LENGTH];
	
	if (argc != 3)
	{
		printf("\nIncorrect commandline arguments. Please give a source and destination file.\n");
		exit(1);
	}

	//Create commandline args for the child processes
	sprintf_s(source, MAX_CMD_LENGTH, "Source.exe %s", argv[1]);
	sprintf_s(filter, MAX_CMD_LENGTH, "Filter.exe");
	sprintf_s(sink, MAX_CMD_LENGTH, "Sink.exe %s", argv[2]);

	//Setup Pipe settings
	HANDLE hSourceToFilterRead, hSourceToFilterWrite, hFilterToSinkRead, hFilterToSinkWrite;
	SECURITY_ATTRIBUTES PipeAttributes;
	PipeAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	PipeAttributes.lpSecurityDescriptor = NULL;
	PipeAttributes.bInheritHandle = TRUE;

	//Create pipes and start processes
	if (!CreatePipe(&hSourceToFilterRead, &hSourceToFilterWrite, &PipeAttributes, 0))
	{
		fprintf("Error creating Source-to-Filter pipe: %d\n", GetLastError());
		exit(1);
	}
	executeProcess(source, hSourceToFilterWrite, GetStdHandle(STD_INPUT_HANDLE));
	CloseHandle(hSourceToFilterWrite);
	if (!CreatePipe(&hFilterToSinkRead, &hFilterToSinkWrite, &PipeAttributes, 0))
	{
		fprintf("Error creating Filter-to-Sink pipe: %d\n", GetLastError());
		exit(1);
	}
	executeProcess(filter, hFilterToSinkWrite, hSourceToFilterRead);
	CloseHandle(hFilterToSinkWrite);
	CloseHandle(hSourceToFilterRead);
	executeProcess(sink, GetStdHandle(STD_OUTPUT_HANDLE), hFilterToSinkRead);
	CloseHandle(hFilterToSinkRead);

	return(0);
}

void executeProcess(char *cmdline, HANDLE hOutput, HANDLE hInput)
{
	STARTUPINFO si;
	PROCESS_INFORMATION ProcInfoChild;

	//Configure Startup Info
	GetStartupInfo(&si);
	si.dwFlags = si.dwFlags | STARTF_USESTDHANDLES;
	si.hStdOutput = hOutput;
	si.hStdInput = hInput;
	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);

	if (!CreateProcess(
		NULL, cmdline, NULL, NULL,
		TRUE,		//bInheritHandles
		0, NULL, NULL,
		&si,
		&ProcInfoChild))
	{
		fprintf(stderr, "Can't create child process with line: \"%s\". Error code: %d", cmdline, GetLastError());
		exit(1);
	}

	CloseHandle(ProcInfoChild.hProcess);
	CloseHandle(ProcInfoChild.hThread);
}