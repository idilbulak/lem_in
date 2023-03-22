#ifndef BFS_H
# define BFS_H

#include "vec.h"
#include "../inc/bfs.h"

#define MAX_VERTICES 100

void print_path(t_vec* path);
int not_visited(int x, t_vec* path);
t_vec **bfs(t_vec** graph, int src, int dest);


#endif