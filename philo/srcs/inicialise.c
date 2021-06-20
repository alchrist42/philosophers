#include "philo.h"

int	parcing(t_param *p, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	p->cnt_enable = (argc == 6);
	if (ft_atoi_long(argv[1], &p->number) || ft_atoi_long(argv[2], &p->tt_die)
		|| ft_atoi_long(argv[3], &p->tt_eat)
		|| ft_atoi_long(argv[4], &p->tt_sleep)
		|| (p->cnt_enable && ft_atoi_long(argv[5], &p->cnt_eats)))
		return (1);
	if (!p->number || (p->cnt_enable && !p->cnt_eats))
		return (1);
	return (0);
}

int	inicialise_params(t_param *p)
{
	uint64_t	i;

	p->msg_i = 0;
	p->well_fed = 0;
	p->print_time = 0;
	p->philo = malloc(sizeof(*p->philo) * p->number);
	if (!p->philo)
		return (1);
	p->mtx = malloc(sizeof(*p->mtx) * p->number);
	if (!p->mtx)
		return (1);
	i = 0;
	while (i < p->number)
		if (pthread_mutex_init(&p->mtx[i++], NULL))
			return (1);
	if (pthread_mutex_init(&p->mtx_msg, NULL)
		|| pthread_mutex_init(&p->mtx_out, NULL))
		return (1);
	return (0);
}

void	inicialise_phils(t_param *p)
{
	uint64_t	i;

	i = 0;
	while (i < p->number)
	{
		p->philo[i].p = (void *)p;
		p->philo[i].pos = i + 1;
		p->philo[i].eat_count = 0;
		if (i == 0)
			p->philo[i].lfork = &p->mtx[p->number - 1];
		else
			p->philo[i].lfork = &p->mtx[i - 1];
		p->philo[i].rfork = &p->mtx[i];
		i++;
	}
}
