#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "video.h"

Video createVideo(char *title, char *author, char *id, char *description, time_t duration)
{
	Video video;

	if (title != NULL && strlen(title) > 0)
	{
		video.title = (char *) calloc(TITLE + 1, sizeof(char));
		strcpy(video.title, title);
	}

	if (author != NULL && strlen(author) > 0)
	{
		video.author = (char *) calloc(AUTHOR + 1, sizeof(char));
		strcpy(video.author, author);
	}

	if (id != NULL && strlen(id) > 0)
	{
		video.id = (char *) calloc(VIDEOID + 1, sizeof(char));
		strcpy(video.id, id);
	}

	if (description != NULL && strlen(description) > 0)
	{
		video.description = (char *) calloc(DESCRIPTION + 1, sizeof(char));
		strcpy(video.description, description);
	}
	else
	{
		video.description = (char *) calloc(1, sizeof(char));
	}

	video.duration = duration;

	return video;
}

void freeVideo(Video *v)
{
	free(v->title);
	free(v->author);
	free(v->id);
	free(v->description);
}
