#pragma once

#define TITLE 100
#define AUTHOR 120
#define VIDEOID 11
#define DURATION 8

/*
 * title -> max 100 characters
 * author -> max 120 characters combined
 * video id -> max 11 characters
 * duration -> max 8 characters
 * thumbnail -> https://i.ytimg.com/vi/[id]/hq720.jpg
 */
typedef struct video
{
	char *title, *author, *id, *duration;
} Video;


Video createVideo(char *title, char *author, char *id, char *duration);
void freeVideo(Video *v);
