#include "curl.h"
#include "string.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t
downloadCallback (char *ptr, size_t size, size_t nmemb, String *output)
{
	output->length += nmemb;
	output->string = realloc (output->string, output->length + 1);
	strcat (output->string, ptr);
	return size * nmemb;
}

char *
downloadPage (char *page)
{
	char *str = NULL;

	if (page != NULL && strlen (page) > 0)
	{
		// Initializing cURL and Temporary String Structure
		CURL *curl;
		String s = newString ("");
		curl = curl_easy_init ();

		// Saving cURL'ed webpage into String Structure
		curl_easy_setopt (curl, CURLOPT_URL, page);
		curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, downloadCallback);
		curl_easy_setopt (curl, CURLOPT_WRITEDATA, &s);
		curl_easy_perform (curl);

		str = (char *)calloc (s.length + 1, sizeof (char));
		strcpy (str, s.string);

		// Cleanup
		curl_easy_cleanup (curl);
		freeString (&s);
	}

	return str;
}
