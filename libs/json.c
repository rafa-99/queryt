#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "json.h"

json_object* jsonParseString(char* stringedJSON)
{
	struct json_object *json;
	json = ( stringedJSON != NULL && strlen(stringedJSON) > 0 ) ? json_tokener_parse(stringedJSON) : NULL;
	free(stringedJSON);
	return json;
}
