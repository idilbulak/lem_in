#ifndef VEC_H
# define VEC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_vec {
	int *array;
	int size;
	int capacity;
} t_vec;

t_vec*	vec(int capacity);
void	resize_vec(t_vec* vec);
void	push_back_vec(t_vec* vec, int value);
int		size_vec(t_vec* vec);

#endif