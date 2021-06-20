#include "philo.h"

int	print_buffer(t_param *p, bool lock_msg)
{
	char	*temp_s;
	size_t	old_len;

	if (lock_msg)
		pthread_mutex_lock(&p->mtx_msg);
	p->print_time = get_time();
	p->msg[p->msg_i] = 0;
	temp_s = malloc(p->msg_i);
	if (!temp_s)
		return (1);
	ft_strcpy(temp_s, p->msg);
	old_len = p->msg_i;
	p->msg_i = 0;
	if (lock_msg)
		pthread_mutex_unlock(&p->mtx_msg);
	pthread_mutex_lock(&p->mtx_out);
	write(1, temp_s, old_len);
	free(temp_s);
	pthread_mutex_unlock(&p->mtx_out);
	return (0);
}

void	*observer_waiter(void *param)
{
	size_t		i;
	uint64_t	tm;
	t_param		*p;

	p = (t_param *)param;
	while (!p->cnt_enable || p->well_fed < p->number)
	{
		tm = get_time();
		i = 0;
		while (i < p->number)
		{
			if (tm - p->philo[i++].last_eat > p->tt_die)
			{
				pthread_mutex_lock(&p->mtx_msg);
				ft_append_msg(tm - p->philo[i - 1].birth, p->philo + i - 1, RB, DIE);
				print_buffer(p, 0);
				return (NULL);
			}
		}
		if (p->msg_i > BUF * 0.9 || (p->msg_i && tm - p->print_time > 100))
			print_buffer(p, 1);
		usleep(2000);
	}
	print_buffer(p, 1);
	return (NULL);
}

int	ft_append_msg(uint64_t tm, t_philo *philo, char *clr, char *msg)
{
	char	*temp_s;
	t_param *p;

	p = (t_param *)philo->p;
	if (!(msg == DIE))
		pthread_mutex_lock(&p->mtx_msg);
	if (COLORED)
		p->msg_i += ft_strcpy(p->msg + p->msg_i, clr);
	temp_s = ft_itoa_ulong(tm);
	p->msg_i += ft_strcpy(p->msg + p->msg_i, temp_s);
	free(temp_s);
	p->msg[p->msg_i++] = ' ';
	temp_s = ft_itoa_ulong(philo->pos);
	p->msg_i += ft_strcpy(p->msg + p->msg_i, temp_s);
	free(temp_s);
	p->msg_i += ft_strcpy(p->msg + p->msg_i, msg);
	if (COLORED)
		p->msg_i += ft_strcpy(p->msg + p->msg_i, STND);
	p->msg[p->msg_i++] = '\n';
	if (!(msg == DIE))
		pthread_mutex_unlock(&p->mtx_msg);
	return (0);
}
