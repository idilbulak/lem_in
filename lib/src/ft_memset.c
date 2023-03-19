// memset() : to fill a block of memory with a specified value.
// string.h

#include "../inc/lib.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = -1;
	str = (unsigned char*)s;
	while (++i < n)
		str[i] = (unsigned char)c;
	return (str);
}

// int main() {
//     int arr[5] = {1, 2, 3, 4, 5};
//     ft_memset(arr, 0, sizeof(arr));
//     for (int i = 0; i < 5; i++) {
//         printf("arr[%d] = %d\n", i, arr[i]);
//     }
//     return 0;
// }