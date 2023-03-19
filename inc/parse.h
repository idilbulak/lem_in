#ifndef PARSE_H
# define PARSE_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "../lib/inc/lib.h"
#include "vec.h"

typedef struct	s_room
{
	char	*name;
	int		coord_x;
	int		coord_y;
	int		index;
}		t_room;

typedef struct	s_link
{
	char	*room1;
	char	*room2;
}		t_link;

typedef struct	s_data
{
	int		ant_count;
	t_room	*start;
	t_room	*end;
	t_room	**rooms;
	t_link	**links;
	t_vec	**matrix;
	int		room_count;
	int		link_count;
}		t_data;

void	parse_map(char *str, t_data *data);

#endif

