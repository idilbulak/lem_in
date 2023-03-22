#include "../inc/bfs.h"

void print_path(t_vec* path) {
    for (int i = 0; i < path->size; i++) {
        printf("%d", path->array[i]);
        if (i < path->size - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void    store_path(t_vec** path_array, int index, t_vec* path)
{
    path_array[index] = path;
}

int not_visited(int x, t_vec* path) {
    for (int i = 0; i < path->size; i++) {
        if (path->array[i] == x) {
            return 0;
        }
    }
    return 1;
}

t_vec **bfs(t_vec** graph, int src, int dest)
{
    t_vec** queue = (t_vec**)malloc(MAX_VERTICES * sizeof(t_vec*));
    int front = 0, rear = 0;

    t_vec* path = vec(10);
    push_back_vec(path, src);
    queue[rear++] = path;

    t_vec** paths = (t_vec**)malloc(1024 * sizeof(t_vec*));
    int index = 0;

    while (front < rear) {
        path = queue[front++];
        int last = path->array[path->size - 1];

        if (last == dest) {
            // print_path(path);
            store_path(paths, index, path);
            index++;
        }

        for (int i = 0; i < graph[last]->size; i++) {
            if (not_visited(graph[last]->array[i], path)) {
                t_vec* newPath = vec(path->size + 1);
                for (int j = 0; j < path->size; j++) {
                    push_back_vec(newPath, path->array[j]);
                }
                push_back_vec(newPath, graph[last]->array[i]);
                queue[rear++] = newPath;
            }
        }
    }
    // print_path(paths[0]);
    // print_path(paths[1]);
    // print_path(paths[2]);
    return (paths);
    // for (int i = 0; i < rear; i++) {
    //     free(queue[i]->array);
    //     free(queue[i]);
    // }
    // free(queue);
}


// void print_adjacency_matrix(t_vec **matrix) {
//     printf("Adjacency matrix:\n");
//     for (int i = 0; i < 5; i++) {
//         for (int j = 0; j < 5; j++) {
//             int connected = 0;
//             for (int k = 0; k < matrix[i]->size; k++) {
//                 if (matrix[i]->array[k] == j) {
//                     connected = 1;
//                     break;
//                 }
//             }
//             printf("%d ", connected);
//         }
//         printf("\n");
//     }
// }

// int main() {
//     int numVertices = 5;

//     t_vec** graph = (t_vec**)malloc(numVertices * sizeof(t_vec*));
//     for (int i = 0; i < numVertices; i++) {
//         graph[i] = vec(10);
//     }

//     push_back_vec(graph[0], 1);
//     push_back_vec(graph[0], 2);
//     push_back_vec(graph[1], 4);
//     // push_back_vec(graph[1], 4);
//     push_back_vec(graph[2], 3);
//     push_back_vec(graph[3], 4);
//     print_adjacency_matrix(graph);
//     int src = 0, dest = 4;
//     printf("Paths from source %d to destination %d are:\n", src, dest);

//     bfs(graph, src, dest);

//     for (int i = 0; i < numVertices; i++) {
//         free(graph[i]->array);
//         free(graph[i]);
//     }
//     free(graph);

//     return 0;
// }
