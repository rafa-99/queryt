#pragma once
#include <json-c/json.h>

json_object* jsonParseString(char* stringedJSON);
json_object* navigateToVideos(json_object* jsonRoot);
