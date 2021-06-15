#include "philo.h"

int	print_buffer(bool lock_msg)
{
	char	*temp_s;
	size_t	old_len;

	if (lock_msg)
		pthread_mutex_lock(&g_p.mtx_msg);
	g_p.print_time = get_time();
	g_p.msg[g_p.msg_i] = 0;
	temp_s = malloc(g_p.msg_i);
	if (!temp_s)
		return (1);
	ft_strcpy(temp_s, g_p.msg);
	old_len = g_p.msg_i;
	g_p.msg_i = 0;
	if (lock_msg)
		pthread_mutex_unlock(&g_p.mtx_msg);
	pthread_mutex_lock(&g_p.mtx_out);
	write(1, temp_s, old_len);
	free(temp_s);
	pthread_mutex_unlock(&g_p.mtx_out);
	return (0);
}

void *logging_thread(void *msg)
{
	size_t	i;
	uint64_t	tm;

	(void)msg;
	
	while (true)
	{
		tm = get_time();
		i = 0;
		while (i < g_p.number)
			if (tm - g_p.philo[i++].last_eat > g_p.tt_die)
			{
				printf("%zu: %llu, %llu, rzn=%llu, die=%llu\n", i, tm, g_p.philo[i - 1].last_eat, tm - g_p.philo[i - 1].last_eat, g_p.tt_die);
				pthread_mutex_lock(&g_p.mtx_msg);
				ft_append_message(tm - g_p.philo[i - 1].birth, i, DIE, 0);
				print_buffer(0);
				return (NULL);
			}
		// if anyone dead:
		// append message and break
		if (g_p.msg_i > 50000 || (g_p.msg_i && get_time() - g_p.print_time > 100))
			print_buffer(1);
		usleep(2000);
	}
}

int	ft_append_message(uint64_t tm, int ind_phil, char *s, bool unlock)
{
	char	*temp_s;

	if (unlock)
		pthread_mutex_lock(&g_p.mtx_msg);
	temp_s = ft_itoa_ulong(tm);
	g_p.msg_i += ft_strcpy(g_p.msg + g_p.msg_i, temp_s);
	free(temp_s);
	g_p.msg[g_p.msg_i++] = ' ';
	temp_s = ft_itoa_ulong(ind_phil);
	g_p.msg_i += ft_strcpy(g_p.msg + g_p.msg_i, temp_s);
	free(temp_s);
	g_p.msg[g_p.msg_i++] = ' ';
	g_p.msg_i += ft_strcpy(g_p.msg + g_p.msg_i, s);
	g_p.msg[g_p.msg_i++] = '\n';
	if (unlock)
		pthread_mutex_unlock(&g_p.mtx_msg);
	

	return (0);
}

void	ft_info_message(uint64_t tm, int ind_phil, char *s)
{
	char	*nmbr_s;

	nmbr_s = ft_itoa_ulong(tm);
	write(1, nmbr_s, ft_strlen(nmbr_s));
	free(nmbr_s);
	nmbr_s = ft_itoa_ulong(ind_phil);
	write(1, nmbr_s, ft_strlen(nmbr_s));
	free(nmbr_s);
	
	
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}

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

