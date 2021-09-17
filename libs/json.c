#include "json.h"
#include "../include/video.h"
#include <json-c/json.h>
#include <string.h>

json_object *
jsonParseString (char *stringedJSON)
{
	return (stringedJSON != NULL && strlen (stringedJSON) > 0)
		? json_tokener_parse (stringedJSON)
		: NULL;
}

json_object *
objectPathNavigator (json_object *object, char path[][MAXLENGTH], int depth)
{
	json_object *navigator
		= (json_object_get_type (object) == json_type_array)
		? json_object_array_get_idx (object, atoi (path[0]))
		: json_object_object_get (object, path[0]);

	for (int i = 1; i < depth; i++)
	{
		navigator = (json_object_get_type (navigator) == json_type_array)
			? json_object_array_get_idx (navigator, atoi (path[i]))
			: json_object_object_get (navigator, path[i]);
	}

	return navigator;
}

json_object *
navigateToVideos (json_object *jsonRoot)
{
	char path[][MAXLENGTH] = { "contents",
		"twoColumnSearchResultsRenderer",
		"primaryContents",
		"sectionListRenderer",
		"contents",
		"0",
		"itemSectionRenderer",
		"contents" };

	return objectPathNavigator (jsonRoot, path,
			sizeof (path) / sizeof (path[0]));
}

int
videoCounter (json_object *contents)
{
	int counter = 0;
	json_object *iterator;

	for (int i = 0; i < json_object_array_length (contents); i++)
	{
		iterator = json_object_array_get_idx (contents, i);
		iterator = json_object_object_get (iterator, "videoRenderer");

		if (json_object_get_type (iterator) != json_type_null)
		{
			counter++;
		}
	}

	return counter;
}

Video *
generateVideos (json_object *contents)
{
	char idPath[][MAXLENGTH] = { "videoId" };

	char titlePath[][MAXLENGTH] = { "title", "runs", "0", "text" };

	char authorPath[][MAXLENGTH] = { "ownerText", "runs", "0", "text" };

	char lengthPath[][MAXLENGTH] = { "lengthText", "simpleText" };

	Video *videos = (Video *)calloc (videoCounter (contents), sizeof (Video));

	for (int i = 0, j = 0; i < json_object_array_length (contents); i++)
	{
		// Initializing Vars For Each Video Structure
		char title[TITLE + 1], author[AUTHOR + 1], id[VIDEOID + 1],
		duration[DURATION + 1];
		json_object *iterator = json_object_array_get_idx (contents, i),
			    *dataHolder;

		// Grabbing the information from each path of the JSON
		iterator = json_object_object_get (iterator, "videoRenderer");
		if (json_object_get_type (iterator) != json_type_null)
		{
			// ID Path
			dataHolder = objectPathNavigator (
					iterator, idPath, sizeof (idPath) / sizeof (idPath[0]));
			strcpy (id, json_object_get_string (dataHolder));

			// Title Path
			dataHolder = objectPathNavigator (
					iterator, titlePath, sizeof (titlePath) / sizeof (titlePath[0]));
			strcpy (title, json_object_get_string (dataHolder));

			// Author Path
			dataHolder = objectPathNavigator (iterator, authorPath,
					sizeof (authorPath)
					/ sizeof (authorPath[0]));
			strcpy (author, json_object_get_string (dataHolder));

			// Video Length Path
			dataHolder = objectPathNavigator (iterator, lengthPath,
					sizeof (lengthPath)
					/ sizeof (lengthPath[0]));
			(json_object_get_type (dataHolder) != json_type_null)
				? strcpy (duration, json_object_get_string (dataHolder))
				: strcpy (duration, "LIVE NOW");

			// Creating Videos Data
			videos[j++] = createVideo (title, author, id, duration);
		}
	}

	return videos;
}
