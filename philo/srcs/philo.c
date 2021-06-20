#include "philo.h"

int	main(int argc, char **argv)
{
	t_param	p;

	if (parcing(&p, argc, argv) || inicialise_params(&p))
		return (1);
	inicialise_phils(&p);
	if (run_philo_treads(&p))
		return (1);
	if (pthread_create(&p.observer_trd, NULL, observer_waiter, (void *)&p))
		return (1);
	pthread_join(p.observer_trd, NULL);
}

int	run_philo_treads(t_param *p)
{
	size_t	i;

	i = 0;
	while (i < p->number)
	{
		if (pthread_create(&p->philo[i].trd, NULL,
				philo_life, (void *)(p->philo + i)))
			return (1);
		i += 2;
		if (i >= p->number && !(i % 2))
			i = 1;
		usleep(5);
	}
	return (0);
}

void	*philo_life(void *philosoph)
{
	t_philo	*philo;
	t_param	*p;

	philo = (t_philo *)philosoph;
	p = (t_param *)philo->p;
	philo->birth = get_time();
	philo->last_eat = philo->birth;
	while (true)
	{
		take_forks(p, philo);
		while (get_time() - philo->last_eat < p->tt_eat)
			usleep(300);
		if (p->cnt_enable && ++philo->eat_count == p->cnt_eats)
			p->well_fed++;
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
		ft_append_msg(get_time() - philo->birth, philo, M, SLEEP);
		while (get_time() - philo->last_eat < p->tt_eat + p->tt_sleep)
			usleep(300);
		ft_append_msg(get_time() - philo->birth, philo, B, THINK);
	}
	return (NULL);
}

void	take_forks(t_param *p, t_philo *philo)
{
	if (philo->pos % 2)
	{
		pthread_mutex_lock(philo->lfork);
		ft_append_msg(get_time() - philo->birth, philo, Y, LFORK);
		pthread_mutex_lock(philo->rfork);
		ft_append_msg(get_time() - philo->birth, philo, Y, RFORK);
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		ft_append_msg(get_time() - philo->birth, philo, Y, RFORK);
		pthread_mutex_lock(philo->lfork);
		ft_append_msg(get_time() - philo->birth, philo, Y, LFORK);
	}
	if (get_time() - philo->last_eat < p->tt_die)
		ft_append_msg(get_time() - philo->birth, philo, G, EAT);
	
	philo->last_eat = get_time();
}
