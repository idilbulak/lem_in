#include "../inc/read.h"

void	read_map(char *map, char **str)
{
	int	i;
	int	fd;
	int	read_bytes;
	int	buffer_size;

	i = 0;
	read_bytes = 0;
	buffer_size = 1025;
	if (!(*str = malloc(1024 * sizeof(char))))
	{
		printf("ERROR: malloc failure\n");
		exit(1);
	}
	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		printf("ERROR: invalid map\n");
		exit(2);
	}
	while(read_bytes == read(fd, *str, 1024) > 0)
	{
		i += read_bytes;
		(*str)[i] = '\0';
		if (i + 1024 >= buffer_size - 1)
			if (!ft_realloc((void **)str, &buffer_size, buffer_size * 2, sizeof(char)))
			{
				printf("ERROR: malloc failure\n");
				exit(1);
			}
	}
	close (fd);
}