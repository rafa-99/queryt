#pragma once

typedef struct video
{
	char *title, *author, *id, *duration;
} Video;


Video createVideo(char *title, char *author, char *id, char *duration);
void freeVideo(Video *v);
