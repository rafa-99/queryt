#pragma once
#include <json-c/json.h>
#include "../include/video.h"

json_object* jsonParseString(char* stringedJSON);
json_object* navigateToVideos(json_object* jsonRoot);
int videoCounter(json_object* contents);
Video* generateVideos(json_object* contents);
