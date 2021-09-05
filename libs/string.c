#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

String
newString (char *string)
{
	String s;
	if (string != NULL && strlen (string) > 0)
	{
		s.length = strlen (string);
		s.string = (char *)calloc (s.length + 1, sizeof (char));
		strcpy (s.string, string);
	}
	else
	{
		s.length = 0;
		s.string = (char *)calloc (1, sizeof (char));
	}

	return s;
}

void
freeString (String *s)
{
	s->length = 0;
	free (s->string);
}
