#pragma once

int tokenCount(char *string, char *delimiter);
char** tokenizer(char *string, char *delimiter);
void freeTokens(char **tokens, int size);
char* queryNormalizer(char *query);
int* jsonDataLimits(int tokenCount, char **tokens, char *topDelimiter, char *bottomDelimiter);
char* curlToJSON(char *url);
