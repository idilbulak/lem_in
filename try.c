#include <stdio.h>

#define MAX_ANTS 10
#define MAX_PATHS 10
#define MAX_PATH_LENGTH 10
#define MAX_ROOMS 10

void move_ants(int ant_count, int ant_paths[MAX_ANTS], int paths[MAX_PATHS][MAX_PATH_LENGTH], int room_count) {
    int positions[MAX_ANTS] = {0}; // başlangıçta karıncaların pozisyonu 0
    int room_occupancy[MAX_ROOMS] = {0}; // tüm odalar başlangıçta boş
    int i, j, k;
    for (i = 0; i < ant_count; i++) {
        room_occupancy[0]++; // başlangıç odasına bir karınca yerleştir
        printf("ant%d: %d, ", i+1, positions[i]);
    }
    printf("\n");
    while (room_occupancy[room_count-1] < ant_count) { // tüm karıncalar son odaya ulaşana kadar devam et
        for (i = 0; i < ant_count; i++) {
            if (positions[i] < MAX_PATH_LENGTH && ant_paths[i] < MAX_PATHS && paths[ant_paths[i]][positions[i]+1] != -1 && room_occupancy[paths[ant_paths[i]][positions[i]+1]] == 0) {
                // karınca yeni bir odaya geçebilir
                room_occupancy[paths[ant_paths[i]][positions[i]]]--; // eski odadan ayrıl
                positions[i]++; // yeni odaya geç
                room_occupancy[paths[ant_paths[i]][positions[i]]]++; // yeni odada yer kapla
            }
            printf("ant%d: %d, ", i+1, positions[i]);
        }
        printf("\n");
    }
}

int main() {
    int ant_count = 3;
    int ant_paths[MAX_ANTS] = {0, 0, 1};
    int paths[MAX_PATHS][MAX_PATH_LENGTH] = {{0, 1, 4}, {0, 2, 3, 4}};
    int room_count = 5;
    move_ants(ant_count, ant_paths, paths, room_count);
    return 0;
}


