#pragma once
#include <json-c/json.h>
#include "../include/video.h"
#define MAXLENGTH 256

json_object* jsonParseString(char* stringedJSON);
json_object* objectPathNavigator(json_object* object, char path[][MAXLENGTH], int depth);
json_object* navigateToVideos(json_object* jsonRoot);
int videoCounter(json_object* contents);
Video* generateVideos(json_object* contents);
