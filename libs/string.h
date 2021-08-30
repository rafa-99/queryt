#pragma once

typedef struct string
{
	char *string;
	int length;
} String;

String newString(char *string);
void freeString(String *s);
