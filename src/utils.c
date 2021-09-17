#include "../include/utils.h"
#include "../include/video.h"
#include "../libs/curl.h"
#include "../libs/string.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JSONVAR "ytInitialData = "

char *
queryNormalizer (char *query)
{
	char *norm = NULL;
	if (query != NULL && strlen (query) > 0)
	{
		// Declaring Initial Query Size
		int querySize = strlen (query);

		// Calculating Normalized Query Size Allocation
		for (int i = 0; i < strlen (query); i++)
		{
			if (query[i] == '+' || query[i] == '#' || query[i] == '&')
			{
				querySize += 2;
			}
		}

		// Allocating Memory
		norm = (char *)calloc (querySize + 1, sizeof (char));

		// Creating New Normalized Query
		for (int i = 0, added = 0; i < strlen (query); i++)
		{
			switch (query[i])
			{
				case '+':
					/* fall through */
				case '#':
					/* fall through */
				case '&':
					for (int j = 0; j < 3; j++)
					{
						switch (j)
						{
							case 0:
								norm[i + j + added] = '%';
								break;
							case 1:
								norm[i + j + added] = '2';
								break;
							case 2:
								switch (query[i])
								{
									case '+':
										norm[i + j + added] = 'B';
										break;
									case '#':
										norm[i + j + added] = '3';
										break;
									case '&':
										norm[i + j + added] = '6';
								}
						}
					}
					added += 2;
					break;
				case ' ':
					norm[i + added] = '+';
					break;
				default:
					norm[i + added] = query[i];
			}
		}
	}
	return norm;
}

char *
extractQueryJSON (char *youtubeurl)
{
	char *json = NULL;

	if (youtubeurl != NULL && strlen (youtubeurl) > 0)
	{
		char *htmlPage = downloadPage (youtubeurl);
		if (htmlPage != NULL && strlen (htmlPage) > 0)
		{
			char *jsonVar = strstr(htmlPage, JSONVAR) + strlen(JSONVAR);
			if ( jsonVar != NULL && strlen(jsonVar) > 0 )
			{
				json = (char *) calloc(strlen(jsonVar) + 1, sizeof(char));
				strcpy(json, jsonVar);
			}
		}
		free (htmlPage);
	}
	return json;
}

int
checkNumber (char *num)
{
	int number = 0, charCheck = 1;

	if (num != NULL && strlen (num) > 0 && strlen (num) < 3)
	{
		for (int i = 0; i < strlen (num) && charCheck; i++)
		{
			if (!isdigit (num[i]))
			{
				charCheck--;
			}
		}

		number = (charCheck) ? atoi (num) : 0;
	}

	return number;
}
