#include "philo.h"

char	*ft_strdup(const char *s1)
{
	char	*new_str;
	int		len_s;
	int		i;

	len_s = ft_strlen(s1) + 1;
	new_str = (char *)malloc(sizeof(*new_str) * len_s);
	if (!new_str)
		return (new_str);
	i = 0;
	while (i < len_s)
	{
		new_str[i] = s1[i];
		i++;
	}
	return (new_str);
}

char	*ft_itoa_ulong(uint64_t n)
{
	char	s[21];
	int		i;

	s[20] = 0;
	i = 19;
	if (!n)
		s[i--] = '0';
	while (n)
	{
		s[i--] = '0' + n % 10;
		n = n / 10;
	}
	return (ft_strdup(&s[i + 1]));
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		if (dst)
			dst[i] = src[i];
		i++;
	}
	if (dst)
		dst[i] = src[i];
	return (i);
}
