// memcpy() : to copy a block of memory from one location to another.
// string.h

#include "../inc/lib.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned long i;

	i = -1;
	while (++i < n)
		*(unsigned char*)(dest + i) = *(unsigned char*)(src + i);
	return (dest);
}

// int main() {
//     char src[] = "Hello, world!";
//     char dest[20];
//     ft_memcpy(dest, src, strlen(src) + 1);
//     printf("src = %s\n", src);
//     printf("dest = %s\n", dest);
//     return 0;
// }
