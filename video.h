#pragma once
#include <time.h>

#define TITLE 100
#define AUTHOR 120
#define VIDEOID 11
#define DESCRIPTION 5000

/*
 * title -> max 100 characters
 * author -> max 120 characters combined
 * video id -> max 11 characters
 * video description -> max 5000 characters
 * thumbnail -> https://i.ytimg.com/vi/[id]/hq720.jpg
 */
typedef struct video
{
	char *title, *author, *id, *description;
	time_t duration;
} Video;


Video createVideo(char *title, char *author, char *id, char *description, time_t duration);
void freeVideo(Video *v);
