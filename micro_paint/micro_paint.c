#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "micro_paint.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	if(!str)
		return (i);
	while(str[i])
		i++;
	return (i);
}

void	paint_background(t_zone *zone)
{
	zone->draw = malloc(sizeof(char) * zone->height * zone->width);
	memset(zone->draw, zone->bg, zone->width * zone->height);
}

int	throw_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int	draw_zone(t_zone *zone)
{
	if (zone->width <= 0 || zone->width > 300 || zone->height <= 0 || zone->height > 300 || !zone->bg)
		return (1);
	paint_background(zone);
	return (0);
}

int			is_inner_point(t_rectangle *rect, int x, int y)
{
	if (x >= rect->x && x <= rect->x + rect->width && y >= rect->y && y <= rect->y + rect->height)
		return (1);
	return (0);
}

int	is_outer_point(t_rectangle *rect, int x, int y)
{
	if (is_inner_point(rect, x, y) && (x - rect->x < 1.0 || y - rect->y < 1.0 || rect->x + rect->width - x < 1.0 || rect->y + rect->height - y < 1.0))
		return (1);
	return (0);
}

void			draw_empty(t_zone *zone, t_rectangle *rect)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < zone->height)
	{
		x = 0;
		while (x < zone->width)
		{
			if (is_outer_point(rect, x, y))
				*(zone->draw + y * zone->width + x) = rect->bg;
			x++;
		}
		y++;
	}
}

void			draw_filled(t_zone *zone, t_rectangle *rect)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < zone->height)
	{
		x = 0;
		while (x < zone->width)
		{
			if (is_inner_point(rect, x, y))
				*(zone->draw + y * zone->width + x) = rect->bg;
			x++;
		}
		y++;
	}
}

void paint_terminal(t_zone *zone)
{
	int y;

	y = 0;
	while (y < zone->height)
	{
		write(1, zone->draw + y * zone->width, zone->width);
		write(1, "\n", 1);
		y++;
	}
}

int	read_and_draw(FILE *f, t_zone *zone)
{
	t_rectangle r;
	int count;

	count = 0;
	if ((fscanf(f, "%d %d %c\n", &zone->width, &zone->height, &zone->bg)) != 3)
		return (1);
	if (draw_zone(zone))
		return (1);
	while ((count = fscanf(f, "%c %f %f %f %f %c\n", &r.type, &r.x, &r.y, &r.width, &r.height, &r.bg)) != EOF)
	{
		if (count != 6 || r.width <= 0 || r.height <= 0 || !r.bg || (r.type != 'r' && r.type != 'R'))
			return (1);
		if (r.type == 'r')
			draw_empty(zone, &r);
		if (r.type == 'R')
			draw_filled(zone, &r);
	}
	paint_terminal(zone);
	free(zone->draw);
	return (0);
}

int main(int argc, char **argv)
{
	FILE *f;
	t_zone zone;

	if (argc != 2)
		return (throw_error("Error: argument\n"));
	if (!(f = fopen(argv[1], "r")))
		return (throw_error("Error: Operation file corrupted\n"));
	if (read_and_draw(f, &zone))
		return (throw_error("Error: Operation file corrupted\n"));
	return (0);
}

