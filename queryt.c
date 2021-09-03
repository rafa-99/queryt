#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <json-c/json.h>
#include "include/utils.h"
#include "include/video.h"
#include "libs/curl.h"

void processOptions(int *options, char **args);

int main(int argc, char **argv)
{
	int o = 0, opts[] = { 0, 0, 0, 0, 0 };
	char **args = (char **) calloc(3, sizeof(char *));
	for ( int i = 0; i < 3; i++ )
	{
		args[i] = (char *) calloc(1, sizeof(char *));
	}

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
				args[0] = (char *) realloc(args[0], strlen(optarg) + 1);
				strcpy(args[0], optarg);
				break;
			case 'h':
				opts[1]++;
				break;
			case 'm':
				opts[2]++;
				args[1] = (char *) realloc(args[1], strlen(optarg) + 1);
				strcpy(args[1], optarg);
				break;
			case 's':
				opts[3]++;
				args[2] = (char *) realloc(args[2], strlen(optarg) + 1);
				strcpy(args[2], optarg);
				break;
			case 'v':
				opts[4]++;
		}
	}

	processOptions(opts, args);

	for ( int i = 0; i < 3; i++ )
	{
		free(args[i]);
	}
	free(args);

	return 0;
}

void processOptions(int *options, char **args)
{
	if ( !options[1] && options[3] && !options[4] )
	{
		char *query = queryNormalizer(args[2]);
		if ( query != NULL )
		{
			char *link = (char *) calloc(strlen("https://www.youtube.com/results?search_query=") + strlen(query) + 1, sizeof(char));
			strcpy(link, "https://www.youtube.com/results?search_query=");
			strcat(link, query);

			char *json = extractQueryJSON(link);
			free(link);
			free(query);

			if ( json != NULL && strlen(json) > 0 )
			{
				json_object *queryRoot = json_tokener_parse(json), *handler;
				free(json);
				if ( queryRoot != NULL && json_object_get_type(queryRoot) != json_type_null )
				{
				}
				else
				{
					json_object_put(queryRoot);
				}
			}
			else
			{
				free(json);
			}

		}
	}
	else
	{
		if ( options[1] || (options[3] && options[4]))
		{
			puts("Help Message");
		}
		else
		{
			if ( options[4] )
			{
				puts("Version Message");
			}
			else
			{
				puts("-s is required!");
			}
		}
	}
}
