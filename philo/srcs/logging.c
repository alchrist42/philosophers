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

void	*observer_waiter(void *msg)
{
	size_t		i;
	uint64_t	tm;

	(void)msg;
	while (!g_p.cnt_enable || g_p.well_fed < g_p.number)
	{
		tm = get_time();
		i = 0;
		while (i < g_p.number)
		{
			if (tm - g_p.philo[i++].last_eat > g_p.tt_die)
			{
				pthread_mutex_lock(&g_p.mtx_msg);
				ft_append_msg(tm - g_p.philo[i - 1].birth, i, RB, DIE);
				print_buffer(0);
				return (NULL);
			}
		}
		if (g_p.msg_i > BUF * 0.9 || (g_p.msg_i && tm - g_p.print_time > 100))
			print_buffer(1);
		usleep(2000);
	}
	print_buffer(1);
	return (NULL);
}

int	ft_append_msg(uint64_t tm, int pos, char *clr, char *msg)
{
	char	*temp_s;

	if (!(msg == DIE))
		pthread_mutex_lock(&g_p.mtx_msg);
	if (COLORED)
		g_p.msg_i += ft_strcpy(g_p.msg + g_p.msg_i, clr);
	temp_s = ft_itoa_ulong(tm);
	g_p.msg_i += ft_strcpy(g_p.msg + g_p.msg_i, temp_s);
	free(temp_s);
	g_p.msg[g_p.msg_i++] = ' ';
	temp_s = ft_itoa_ulong(pos);
	g_p.msg_i += ft_strcpy(g_p.msg + g_p.msg_i, temp_s);
	free(temp_s);
	g_p.msg_i += ft_strcpy(g_p.msg + g_p.msg_i, msg);
	if (COLORED)
		g_p.msg_i += ft_strcpy(g_p.msg + g_p.msg_i, STND);
	g_p.msg[g_p.msg_i++] = '\n';
	if (!(msg == DIE))
		pthread_mutex_unlock(&g_p.mtx_msg);
	return (0);
}
