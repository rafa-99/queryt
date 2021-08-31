#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "json.h"
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

	json_object *videos = json_object_object_get(jsonRoot, path[0]);

	for( int i = 1; i < sizeof(path)/sizeof(path[0]); i++ )
	{
		if ( json_object_get_type(videos) == json_type_array )
		{
			videos = json_object_array_get_idx(videos, atoi(path[i]));
		}
		else
		{
			videos = json_object_object_get(videos, path[i]);
		}
	}

	return videos;
}
