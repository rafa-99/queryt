#pragma once

int tokenCount(char *string, char *delimiter);
char** tokenizer(char *string, char *delimiter);
void freeTokens(char **tokens, int size);
char* queryNormalizer(char *query);
char* extractQueryJSON(char *youtubeurl);
