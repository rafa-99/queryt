#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "../libs/curl.h"
#include "../libs/string.h"

int tokenCount(char *string, char *delimiter)
{
	int totalCount = 0;

	if (string != NULL && delimiter != NULL)
	{
		char *auxString = (char *)calloc(strlen(string) + 1, sizeof(char));
		strcpy(auxString, string);

		char *token = strtok(auxString, delimiter);

		while (token != NULL)
		{
			totalCount++;
			token = strtok(NULL, delimiter);
		}

		free(auxString);
	}

	return totalCount;
}

char **tokenizer(char *string, char *delimiter)
{
	char **tokens = NULL;

	if (string != NULL && delimiter != NULL)
	{
		char *auxString = (char *)calloc(strlen(string) + 1, sizeof(char));
		strcpy(auxString, string);

		tokens = (char **)calloc(tokenCount(auxString, delimiter), sizeof(char *));
		char *tempToken = strtok(auxString, delimiter);

		for (int i = 0; tempToken != NULL; i++)
		{
			tokens[i] = (char *)calloc(strlen(tempToken) + 1, sizeof(char));
			strcpy(tokens[i], tempToken);
			tempToken = strtok(NULL, delimiter);
		}

		free(auxString);
	}
	else
	{
		tokens = (char **)calloc(1, sizeof(char));
	}

	return tokens;
}

void freeTokens(char **tokens, int size)
{
	if ( size > 0 )
	{
		for ( int i = 0; i < size; i++ )
		{
			free(tokens[i]);
		}
	}
	free(tokens);
}

char *queryNormalizer(char *query)
{
	char *norm = NULL;
	if (query != NULL && strlen(query) > 0)
	{
		// Declaring Initial Query Size
		int querySize = strlen(query);

		// Calculating Normalized Query Size Allocation
		for (int i = 0; i < strlen(query); i++)
		{
			if (query[i] == '+' || query[i] == '#' || query[i] == '&')
			{
				querySize += 2;
			}
		}

		// Allocating Memory
		norm = (char *)calloc(querySize + 1, sizeof(char));

		// Creating New Normalized Query
		for (int i = 0, added = 0; i < strlen(query); i++)
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

char* extractQueryJSON(char *youtubeurl)
{
	char *json = NULL;

	if (youtubeurl != NULL && strlen(youtubeurl) > 0)
	{
		char *htmlPage = downloadPage(youtubeurl);
		if ( htmlPage != NULL && strlen(htmlPage) > 0 )
		{
			// Setting Up Vars
			char jsonVar[] = "ytInitialData", needlessHTML[] = ";</script><script", **tokens = tokenizer(htmlPage, " ");
			int numberOfTokens = tokenCount(htmlPage, " ");
			json = (char *)calloc(1, sizeof(char));

			// Extracting JSON String
			for (int i = 0, j = 1; i < numberOfTokens && strstr(tokens[j-1], needlessHTML) == NULL; i++)
			{
				if ( strcmp(tokens[i], jsonVar) == 0 )
				{
					for ( j = i + 2; strstr(tokens[j-1], needlessHTML) == NULL; j++ )
					{
						json = realloc(json, (strlen(json) + strlen(tokens[j]) + 2));
						strcat(json, tokens[j]);
						strcat(json, " ");
					}
				}
			}

			json[strlen(json) - strlen(needlessHTML)] = '\0';
			freeTokens(tokens, numberOfTokens);
		}
		free(htmlPage);
	}
	return json;
}
