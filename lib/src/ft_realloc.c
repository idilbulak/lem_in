// realloc() : to dynamically reallocate memory for a previously allocated block of memory.
// stdlib.h
// **str

#include "../inc/lib.h"

int ft_realloc(void **str, int *size, int dst_size, size_t size_type)
{
	char			*tmp;
	unsigned int	size_str;
	unsigned int	new_size;

	size_str = *size;
	new_size = dst_size;
	if (new_size == size_str)
		return (1);
	if (!(tmp = malloc(new_size * size_type)))
		return (0);
	if (size_str)
	{
		ft_memcpy(tmp, *str, size_str * size_type);
		free(*str);
	}
	*str = tmp;
	if (new_size > size_str)
		ft_memset(*str + size_str, 0, (new_size - size_str) * size_type);
	*size = new_size;
	return (1);
}

// int main()
// {
//     char *str = malloc(10 * sizeof(char));
//     int size = 10;
//     int dst_size = 20;                        
//     size_t size_type = sizeof(char);           
//     if (!str)
//     {
//         printf("Error: memory allocation failed.\n");
//         return (1);
//     }
//     strcpy(str, "Hello");
//     printf("Original string: %s\n", str);
//     printf("Original size: %d\n", size);
//     if (!ft_realloc((void**)&str, &size, dst_size, size_type))
//     {
//         printf("Error: memory reallocation failed.\n");
//         return (1);
//     }
//     strcat(str, " World");
//     printf("New string: %s\n", str);
//     printf("New size: %d\n", size);
//     free(str);
//     return (0);
// }