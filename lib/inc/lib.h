#ifndef LIB_H
# define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int     ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
int     ft_atoi(const char *str);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_realloc(void **str, int *size, int dst_size, size_t size_type);
char	**ft_split(char const *s, char c);
char	*ft_strrchr(const char *s, int c);

#endif