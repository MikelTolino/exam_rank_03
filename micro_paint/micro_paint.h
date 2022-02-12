#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct s_zone
{
	int width;
	int height;
	char bg;
	char *draw;
}	t_zone;

typedef struct s_rectangle
{
	char type;
	float	x;
	float	y;
	float width;
	float height;
	char bg;
}	t_rectangle;
