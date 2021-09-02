#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "include/utils.h"
#include "include/video.h"

void errorMessage(int errorCode, char* message);
void processOptions(int *options);

int main(int argc, char **argv)
{
	int o = 0, opts[] = { 0, 0, 0, 0, 0 };

	static struct option long_options[] = {
		{"format",	required_argument,	0,	'f'},
		{"help",	no_argument,		0,	'h'},
		{"max",		required_argument,	0,	'm'},
		{"search",	required_argument,	0,	's'},
		{"version",	no_argument,		0,	'v'},
		{0,		0,			0,	0}
	};

	while ((o = getopt_long(argc, argv, "f:hm:s:v", long_options, NULL)) != -1)
	{
		switch(o)
		{
			case 'f':
				opts[0]++;
				break;
			case 'h':
				opts[1]++;
				break;
			case 'm':
				opts[2]++;
				break;
			case 's':
				opts[3]++;
				break;
			case 'v':
				opts[4]++;
				break;
			default:
				errorMessage(1, "");
		}
	}

	processOptions(opts);
	return 0;
}

void errorMessage(int errorCode, char* message)
{
	printf("%s", message);
	exit(errorCode);
}

void processOptions(int *options)
{
	//ToDo
}
