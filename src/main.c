#include <fcntl.h>
#include <time.h>
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

int	count_paths(t_vec** paths)
{
    int	count;
	
	count = 0;
    for (int i = 0; i < 1024; i++) {
        if (paths[i] != NULL) {
            count++;
        }
    }
    return count;
}
// The assign_paths_to_ants function uses a simple greedy algorithm to assign ants to paths. At each step, it assigns each ant to the path with the smallest number of rooms, without considering the consequences of that assignment on future ants. This is a local search strategy that tries to optimize the assignment of ants to paths by minimizing the number of rooms traveled by each ant individually, without considering the global cost of the assignment.

// The algorithm used in assign_paths_to_ants can be seen as a variant of the "nearest-neighbor" heuristic commonly used in the traveling salesman problem. In this problem, the goal is to find the shortest possible route that visits a given set of cities and returns to the starting city. The nearest-neighbor heuristic works by starting at a random city and then visiting the nearest unvisited city, and repeating this process until all cities have been visited. This algorithm is a simple and fast heuristic that can give good results for small to medium-sized instances of the problem, but it can also be very inefficient for larger instances or instances with complex structures.
int* assign_paths_to_ants(int num_ants, int num_paths, int* path_capacity) {
    int* ant_path = (int*) malloc(num_ants * sizeof(int)); // allocate memory for the ant_path array
    int* path_room_count = (int*) calloc(num_paths, sizeof(int)); // allocate memory for the path_room_count array and initialize it to 0

    for (int i = 0; i < num_ants; i++) {
        int curr_path = 0;
        int curr_room_count = path_room_count[curr_path] + path_capacity[curr_path]; // calculate the number of rooms in the current path
        for (int j = 1; j < num_paths; j++) {
            int next_room_count = path_room_count[j] + path_capacity[j]; // calculate the number of rooms in the next path
            if (next_room_count < curr_room_count) {
                curr_path = j;
                curr_room_count = next_room_count;
            }
        }
        ant_path[i] = curr_path; // assign the current ant to the path with the smallest number of rooms
        path_room_count[curr_path] += path_capacity[curr_path]; // update the number of rooms in the chosen path
    }

    free(path_room_count); // free memory for the path_room_count array
    return ant_path;
}

void print_ant_movement(int* ant_path, t_vec** paths, int num_ants) {
    int path_count = sizeof(paths) / sizeof(t_vec*);
    int room_count = paths[0]->size;
    int ant_pos[num_ants];
    int ant_end[num_ants];
    for (int i = 0; i < num_ants; i++) {
        ant_pos[i] = -1;
        ant_end[i] = -1;
    }
    for (int i = 0; i < path_count; i++) {
        for (int j = 0; j < room_count; j++) {
            int num_ants_in_room[room_count];
            for (int k = 0; k < room_count; k++) {
                num_ants_in_room[k] = 0;
            }
            for (int k = 0; k < num_ants; k++) {
                if (ant_path[k] == i && ant_pos[k] == j) {
                    num_ants_in_room[j]++;
                } else if (ant_path[k] == i && ant_end[k] == j) {
                    num_ants_in_room[j]++;
                }
            }
            for (int k = 0; k < num_ants; k++) {
                if (ant_path[k] == i && ant_pos[k] == j && num_ants_in_room[j] > 1) {
                    ant_end[k] = j;
                    printf("Ant%d is in room %d, ", k+1, j+1);
                } else if (ant_path[k] == i && ant_pos[k] == j) {
                    ant_pos[k] = -1;
                    ant_end[k] = j;
                    printf("Ant%d is in room %d, ", k+1, j+1);
                }
            }
            for (int k = 0; k < num_ants; k++) {
                if (ant_path[k] == i && ant_pos[k] == -1 && ant_end[k] == j && num_ants_in_room[j] == 0) {
                    ant_pos[k] = j;
                    printf("Ant%d is on room %d, ", k+1, j+1);
                }
            }
        }
    }
    printf("\n");
}

void	solution(t_data *data)
{
	t_vec	**paths;
	t_room	*room;
	int		path_count;
	int		*path_capacity;

	paths = bfs(data->matrix, data->start->index, data->end->index);
	print_path(paths[0]);
    print_path(paths[1]);
    // // print_path(paths[2]);
	path_count = count_paths(paths);
	path_capacity = malloc(sizeof(int) * path_count);
	for(int j=0; j < path_count; j++)
		path_capacity[j] = paths[j]->size - 2;

	int* ant_path = assign_paths_to_ants(data->ant_count, path_count, path_capacity);

	// printf("Ant paths: ");
    // for (int i = 0; i < data->ant_count; i++) {
    //     printf("%d ", ant_path[i]);
    // }
    // printf("\n");

	// print_ant_movement(ant_path, paths, data->ant_count);

    free(ant_path);
}

int	main(int ac, char **av)
{
	t_data	*data;
	char	*str;
	clock_t	start;
	clock_t	end;
	double	time_used;

	data = malloc(sizeof(t_data) * 1);
	check_ac(ac);
	read_map(av[1], &str);
	start = clock();
	parse_map(str, data);
	end = clock();
	time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("time used for parsing: %f seconds\n", time_used);
	for(int i=0; i < data->room_count; i++)
		printf("rooms[%d] name: %s, x_coord %d, y_coord %d, index %d\n", i, data->rooms[i]->name, data->rooms[i]->coord_x, data->rooms[i]->coord_y, data->rooms[i]->index);
	start = clock();
	solution(data);
	end = clock();
	time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("time used for the solution: %f seconds\n", time_used);
	return (0);
}


	// printf("ant_count: %d\n", data->ant_count);
	// printf("start name: %s, x_coord %d, y_coord %d\n", data->start->name, data->start->coord_x, data->start->coord_y);
	// printf("end name: %s, x_coord %d, y_coord %d\n", data->end->name, data->end->coord_x, data->end->coord_y);
	// for(int i=0; i < data->link_count; i++)
	// 	printf("links[%d] room1: %s, room2: %s\n", i, data->links[i]->room1, data->links[i]->room2);