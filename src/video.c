#include "../include/video.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Video
createVideo (char *title, char *author, char *id, char *duration)
{
	Video video;

	if (title != NULL && strlen (title) > 0)
	{
		video.title = (char *)calloc (strlen (title) + 1, sizeof (char));
		strcpy (video.title, title);
	}

	if (author != NULL && strlen (author) > 0)
	{
		video.author = (char *)calloc (strlen (author) + 1, sizeof (char));
		strcpy (video.author, author);
	}

	if (id != NULL && strlen (id) > 0)
	{
		video.id = (char *)calloc (strlen (id) + 1, sizeof (char));
		strcpy (video.id, id);
	}

	if (duration != NULL && strlen (duration) > 0)
	{
		video.duration = (char *)calloc (strlen (duration) + 1, sizeof (char));
		strcpy (video.duration, duration);
	}

	return video;
}

void
printVideo (char *format, Video *videos, int numberOfVideos)
{
	if (format != NULL && strlen (format) > 0)
	{
		for (int i = 0; i < numberOfVideos; i++)
		{
			for (int j = 0; j < strlen (format); j++)
			{
				switch (format[j])
				{
					case 'a':
						printf ("%s", videos[i].author);
						break;
					case 'd':
						printf ("%s", videos[i].duration);
						break;
					case 'i':
						printf ("%s", videos[i].id);
						break;
					case 't':
						printf ("%s", videos[i].title);
						break;
					case 'R':
						printf ("\n");
						break;
					case 'T':
						printf ("\t");
						break;
					default:
						if (!isalpha (format[j]))
						{
							printf ("%c", format[j]);
						}
				}
			}
			printf ("\n");
		}
	}
	else
	{
		for (int i = 0; i < numberOfVideos; i++)
		{
			printf ("%s\t%s\n", videos[i].id, videos[i].title);
		}
	}
}

void
freeVideo (Video *v)
{
	free (v->title);
	free (v->author);
	free (v->id);
	free (v->duration);
}
