#include "../includes/main.h"

int ft_strcmp(const char *s1, const char *s2)
{
    size_t i;

    i = 0;
    while (s1[i] && s2[i] && (unsigned char)s1[i] == (unsigned char)s2[i])
    {
        i++;
    }
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	*ft_memset(void *b, int c, size_t len)
{
    unsigned char	*string;
    size_t			i;

    string = (unsigned char *)b;
    i = 0;
    while (i < len)
    {
        string[i] = (unsigned char)c;
        i++;
    }
    return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
