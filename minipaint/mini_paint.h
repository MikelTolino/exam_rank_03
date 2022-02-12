#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_zone
{
	int width;
	int height;
	char bg;
	char *draw;
} t_zone;

typedef struct s_circle
{
	char c;
	float x;
	float y;
	float radius;
	char bg;
} t_circle;
