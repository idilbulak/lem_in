#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "../inc/read.h"
#include "../inc/parse.h"
#include "../inc/bfs.h"

void	check_ac(int ac)
{
	if (ac != 2)
	{
		printf("ERROR: wrong argument number\n");
		exit(1);
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	char	*str;

	data = malloc(sizeof(t_data) * 1);
	check_ac(ac);
	read_map(av[1], &str);
	parse_map(str, data);
	for(int i=0; i < data->room_count; i++)
		printf("rooms[%d] name: %s, x_coord %d, y_coord %d, index %d\n", i, data->rooms[i]->name, data->rooms[i]->coord_x, data->rooms[i]->coord_y, data->rooms[i]->index);
	bfs(data->matrix, data->start->index, data->end->index);
	return (0);
}


	// printf("ant_count: %d\n", data->ant_count);
	// printf("start name: %s, x_coord %d, y_coord %d\n", data->start->name, data->start->coord_x, data->start->coord_y);
	// printf("end name: %s, x_coord %d, y_coord %d\n", data->end->name, data->end->coord_x, data->end->coord_y);
	// for(int i=0; i < data->link_count; i++)
	// 	printf("links[%d] room1: %s, room2: %s\n", i, data->links[i]->room1, data->links[i]->room2);