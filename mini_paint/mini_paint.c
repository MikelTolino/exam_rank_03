#include "mini_paint.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

int	throw_error(char *error)
{
	write(1, error, ft_strlen(error));
	return (1);
}

int is_point_inside(t_circle circle, float x, float y)
{
	float distance;

	distance = sqrtf(powf(circle.x - x, 2) + powf(circle.y - y, 2));
	if (distance <= circle.radius)
		return (1);
	return (0);
}

int is_point_outside(t_circle circle, float x, float y)
{
	float distance;

	distance = sqrtf(powf(circle.x - x, 2) + powf(circle.y - y, 2));
	if (circle.radius - distance < 1 && is_point_inside(circle, x, y))
		return (1);
	return (0);
}

void fill_empty(t_zone *zone, t_circle circle)
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
			if (is_point_outside(circle, x, y))
				zone->draw[y * zone->width + x] = circle.bg;
			x++;
		}
		y++;
	}
}

void fill_filled(t_zone *zone, t_circle circle)
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
			if (is_point_inside(circle, x, y))
				zone->draw[y * zone->width + x] = circle.bg;
			x++;
		}
		y++;
	}
}

void fill_circle(t_zone *zone, t_circle circle)
{
	if (circle.type == 'c')
		fill_empty(zone, circle);
	if (circle.type == 'C')
		fill_filled(zone, circle);
}

int fill_background(t_zone *zone)
{
	if (zone->width <= 0 || zone->width > 300 || zone->height <= 0 || zone->height > 300 || !zone->bg)
		return (1);
	zone->draw = (char *)malloc(sizeof(char) * zone->width * zone->height);
	memset(zone->draw, zone->bg, zone->width * zone->height);
	return (0);
}

void print_zone(t_zone *zone)
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

int	read_and_print(FILE *f, t_zone *zone)
{
	t_circle circle;
	int count;

	count = 0;
	if (fscanf(f, "%d %d %c\n", &zone->width, &zone->height, &zone->bg) != 3)
		return (1);
	if (fill_background(zone))
		return (1);
	while ((count = fscanf(f, "%c %f %f %f %c\n", &circle.type, &circle.x, &circle.y, &circle.radius, &circle.bg)) != EOF)
	{
		if (count != 5 || (circle.type != 'c' && circle.type != 'C') || circle.radius <= 0)
			return (1);
		fill_circle(zone, circle);
	}
	fclose(f);
	print_zone(zone);
	return (0);
}

int main(int argc, char **argv)
{
	t_zone zone;
	FILE *f;

	if (argc != 2)
		return (throw_error("Error: argument\n"));
	if (!(f = fopen(argv[1], "r")))
		return (throw_error("Error: Operation file corrupted\n"));
	if (read_and_print(f, &zone))
		return (throw_error("Error: Operation file corrupted\n"));
	return (0);
}

