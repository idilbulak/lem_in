#include "../inc/lib.h"

char	*ft_strrchr(const char *s, int c)
{
	int	index;

	index = ft_strlen((char *)s);
	while (index >= 0)
	{
		if (*(s + index) == (char)c)
			return ((char *)s + index);
		index--;
	}
	return (NULL);
}
