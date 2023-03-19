#include "../inc/parse.h"

char	**pass_comments(char **tokens)
{
	int	i;

	i = 0;
	while(tokens[i] && tokens[i][0] == '#')
		i++;
	return (tokens + i);
}

t_room	*get_room(char *token)
{
	char	**arr;
	t_room	*room;

	arr = ft_split(token, ' ');
	room = malloc(sizeof(t_room) * 1);
	room->name = arr[0];
	room->coord_x = ft_atoi(arr[1]);
	room->coord_y = ft_atoi(arr[2]);
	return (room);
}

t_link	*get_link(char *token)
{
	char	**arr;
	t_link	*link;

	arr = ft_split(token, '-');
	link = malloc(sizeof(t_link) * 1);
	link->room1= arr[0];
	link->room2= arr[1];
	return (link);
}

char	**find_start(char **tokens, t_data *data)
{
	int		i;
	t_room	**tmp_rooms;

	tokens = pass_comments(tokens);
	data->start = get_room(tokens[0]);
	if (!data->room_count)
	{
		data->room_count = 1;
		data->rooms = malloc(sizeof(t_room *) * (data->room_count + 1));
		data->rooms[0] = data->start;
		data->rooms[0]->index = 0;
		data->rooms[1] = 0;
		return (tokens + 1);
	}
	data->room_count += 1;
	tmp_rooms = malloc(sizeof(t_room *) * (data->room_count + 1));
	i = 0;
	while(i < data->room_count - 1)
	{
		tmp_rooms[i] = data->rooms[i];
		i++;
	}
	tmp_rooms[i] = data->start;
	tmp_rooms[i]->index = data->room_count - 1;
	tmp_rooms[i + 1] = 0;
	free(data->rooms);
	data->rooms = tmp_rooms;
	return (tokens + 1);
}

char	**find_end(char **tokens, t_data *data)
{
	int		i;
	t_room	**tmp_rooms;

	tokens = pass_comments(tokens);
	data->end = get_room(tokens[0]);
	// data->end->index = data->room_count - 1;
	if (!data->room_count)
	{
		data->room_count = 1;
		data->rooms = malloc(sizeof(t_room *) * (data->room_count + 1));
		data->rooms[0] = data->end;
		data->rooms[0]->index = 0;
		data->rooms[1] = 0;
		return (tokens + 1);
	}
	data->room_count += 1;
	tmp_rooms = malloc(sizeof(t_room *) * (data->room_count + 1));
	i = 0;
	while(i < data->room_count - 1)
	{
		tmp_rooms[i] = data->rooms[i];
		i++;
	}
	tmp_rooms[i] = data->end;
	tmp_rooms[i]->index = data->room_count - 1;
	tmp_rooms[i + 1] = 0;
	free(data->rooms);
	data->rooms = tmp_rooms;
	return (tokens + 1);
}

char	**find_ant_count(char **tokens, t_data *data)
{
	tokens = pass_comments(tokens);
	data->ant_count = ft_atoi(tokens[0]);
	if (!data->ant_count)
	{
		printf("ERROR: ant_count\n");
		exit(1);
	}
	return (tokens + 1);
}

char	**add_room(char **tokens, t_data *data)
{
	int		i;
	t_room	*room;
	t_room	**tmp_rooms;

	room = get_room(tokens[0]);
	if (!data->room_count)
	{
		data->room_count = 1;
		data->rooms = malloc(sizeof(t_room *) * (data->room_count + 1));
		data->rooms[0] = room;
		data->rooms[0]->index = 0;
		data->rooms[1] = 0;
		return (tokens + 1);
	}
	data->room_count += 1;
	tmp_rooms = malloc(sizeof(t_room *) * (data->room_count + 1));
	i = 0;
	while(i < data->room_count - 1)
	{
		tmp_rooms[i] = data->rooms[i];
		i++;
	}
	tmp_rooms[i] = room;
	tmp_rooms[i]->index = data->room_count - 1;
	tmp_rooms[i + 1] = 0;
	free(data->rooms);
	data->rooms = tmp_rooms;
	return (tokens + 1);
}

char	**add_link(char **tokens, t_data *data)
{
	int		i;
	t_link	*link;
	t_link	**tmp_links;

	link = get_link(tokens[0]);
	if (!data->link_count)
	{
		data->link_count = 1;
		data->links = malloc(sizeof(t_link *) * (data->link_count + 1));
		data->links[0] = link;
		data->links[1] = 0;
		return (tokens + 1);
	}
	data->link_count += 1;
	tmp_links = malloc(sizeof(t_link *) * (data->link_count + 1));
	i = 0;
	while(i < data->link_count - 1)
	{
		tmp_links[i] = data->links[i];
		i++;
	}
	tmp_links[i] = link;
	tmp_links[i + 1] = 0;
	// free(data->links);
	data->links = tmp_links;
	return (tokens + 1);
}

int	get_index(t_data *data, char *name)
{
	int	i;

	i = 0;
	while (i < data->room_count)
	{
		if (ft_strcmp(data->rooms[i]->name, name) == 0)
			return (data->rooms[i]->index);
		i++;
	};

}

void	get_adjecent_matrix(t_data *data)
{
	data->matrix = (t_vec**)malloc(data->room_count* sizeof(t_vec*));
	for (int i = 0; i < data->room_count; i++) {
        data->matrix[i] = vec(10);
    }
	int	i;
	int	r1;
	int	r2;
	i = 0;
	while (i < data->link_count)
	{
		r1 = get_index(data, data->links[i]->room1);
		r2 = get_index(data, data->links[i]->room2);
		push_back_vec(data->matrix[r1], r2);
		i++;
	}
}

void	parse_map(char *str, t_data *data)
{
	char	**tokens;
	
	tokens = ft_split(str, '\n');
	tokens = find_ant_count(tokens, data);
	data->room_count =0;
	data->link_count =0;
	while (*tokens)
	{
		if (ft_strcmp(tokens[0], "##start") == 0)
			tokens = find_start(tokens + 1, data);
		else if (ft_strcmp(tokens[0], "##end") == 0)
			tokens = find_end(tokens + 1, data);
		else if (*tokens[0] == '#')
			tokens++;
		else if (ft_strrchr(tokens[0], ' '))
			tokens = add_room(tokens, data);
		else if (ft_strrchr(tokens[0], '-'))
			tokens = add_link(tokens, data);
		else
			tokens++;
	}
	get_adjecent_matrix(data);
}