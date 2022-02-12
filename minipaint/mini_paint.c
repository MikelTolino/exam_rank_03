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

int fill_background(t_zone *zone)
{
	if (zone->width <= 0 || zone->width > 300 || zone->height <= 0 || zone->height > 300 || !zone->bg)
		return (1);
	zone->draw = (char *)malloc(sizeof(char) * zone->width * zone->height);
	memset(zone->draw, zone->bg, zone->width * zone->height);
	return (0);
}

int	read_and_print(FILE *f, t_zone *zone)
{
	t_circle c;
	int count;

	count = 0;
	if (fscanf(f, "%d %d %c\n", &zone->width, &zone->height, &zone->bg) != 3)
		return (1);
	if (fill_background(zone))
		return (1);
	//READ CIRCLE AND WRITE IN DRAWING ZONE
	return (0);
}

int main(int argc, char **argv)
{
	t_zone zone;
	FILE *f;

	if (argc != 2)
		return (throw_error("Error: argument\n"));
	if (!(fopen(argv[1], "r")))
		return (throw_error("Error: Operation file corrupted\n"));
	if (read_and_print(f, &zone))
		return (throw_error("Error: Operation file corrupted\n"));
	return (0);
}
