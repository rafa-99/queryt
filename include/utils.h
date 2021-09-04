#pragma once
#include "video.h"

int tokenCount(char *string, char *delimiter);
char** tokenizer(char *string, char *delimiter);
void freeTokens(char **tokens, int size);
char* queryNormalizer(char *query);
char* extractQueryJSON(char *youtubeurl);
int checkNumber(char *num);
void printVideoInfo(char *format, Video *videos, int numberOfVideos);
