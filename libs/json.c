#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "json.h"
#include "../include/video.h"
#define MAXLENGTH 256

json_object* jsonParseString(char* stringedJSON)
{
	return ( stringedJSON != NULL && strlen(stringedJSON) > 0 ) ? json_tokener_parse(stringedJSON) : NULL;
}

json_object* navigateToVideos(json_object* jsonRoot)
{
	char path[][MAXLENGTH] = {
		"contents",
		"twoColumnSearchResultsRenderer",
		"primaryContents",
		"sectionListRenderer",
		"contents",
		"0",
		"itemSectionRenderer",
		"contents"
	};

	json_object *navigator = json_object_object_get(jsonRoot, path[0]);

	for( int i = 1; i < sizeof(path)/sizeof(path[0]); i++ )
	{
		navigator = ( json_object_get_type(navigator) == json_type_array ) ?
			json_object_array_get_idx(navigator, atoi(path[i])) :
			json_object_object_get(navigator, path[i]);
	}

	return navigator;
}

int videoCounter(json_object* contents)
{
	int counter = 0;
	json_object *iterator;

	for ( int i = 0; i < json_object_array_length(contents) ; i++)
	{
		iterator = json_object_array_get_idx(contents, i);
		iterator = json_object_object_get(iterator, "videoRenderer");

		if ( json_object_get_type(iterator) != json_type_null )
		{
			counter++;
		}
	}

	return counter;
}

Video* generateVideos(json_object* contents)
{
	Video *videos = (Video *) calloc(json_object_array_length(contents), sizeof(Video));

	for ( int i = 0, k = 0; i < json_object_array_length(contents); i++ )
	{
		// Initializing Vars For Each Video Structure
		char title[TITLE + 1], author[AUTHOR + 1], id[VIDEOID + 1], duration[DURATION + 1];
		json_object *iterator = json_object_array_get_idx(contents, i), *dataHolder;

		// Grabbing the information
		iterator = json_object_object_get(iterator, "videoRenderer");
		if ( json_object_get_type(iterator) != json_type_null )
		{
			dataHolder = json_object_object_get(iterator, "videoId");
			strcpy(id, json_object_get_string(dataHolder));

			// Title Path
			dataHolder = json_object_object_get(iterator, "title");
			dataHolder = json_object_object_get(dataHolder, "runs");
			dataHolder = json_object_array_get_idx(dataHolder, 0);
			dataHolder = json_object_object_get(dataHolder, "text");
			strcpy(title, json_object_get_string(dataHolder));

			// Video Length Path
			dataHolder = json_object_object_get(iterator, "lengthText");
			if ( json_object_get_type(dataHolder) != json_type_null )
			{
				dataHolder = json_object_object_get(dataHolder, "simpleText");
				strcpy(duration, json_object_get_string(dataHolder));
			}
			else
			{
				strcpy(duration, "LIVE NOW");
			}

			// Author Path
			dataHolder = json_object_object_get(iterator, "ownerText");
			dataHolder = json_object_object_get(dataHolder, "runs");
			dataHolder = json_object_array_get_idx(dataHolder, 0);
			dataHolder = json_object_object_get(dataHolder, "text");
			strcpy(author, json_object_get_string(dataHolder));

			// Creating Video Objects
			videos[k++] = createVideo(title, author, id, duration);
		}
	}
	return videos;
}
