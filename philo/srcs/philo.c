#include "philo.h"

int	main(int argc, char **argv)
{
	if (parcing(argc, argv) || inicialise_params())
		return (1);
	inicialise_phils();
	if (run_philo_treads())
		return (1);
	if (pthread_create(&g_p.observer_trd, NULL, observer_waiter, NULL))
		return (1);
	pthread_join(g_p.observer_trd, NULL);
}

int	run_philo_treads(void)
{
	size_t	i;

	i = 0;
	while (i < g_p.number)
	{
		if (pthread_create(&g_p.philo[i].trd, NULL,
				philo_life, (void *)(g_p.philo + i)))
			return (1);
		i += 2;
		if (i >= g_p.number && !(i % 2))
			i = 1;
		usleep(5);
	}
	return (0);
}

void	*philo_life(void *philosoph)
{
	t_philo	*philo;

	philo = (t_philo *)philosoph;
	philo->birth = get_time();
	philo->last_eat = philo->birth;
	while (true)
	{
		take_forks(philo);
		while (get_time() - philo->last_eat < g_p.tt_eat)
			usleep(300);
		if (g_p.cnt_enable && ++philo->eat_count == g_p.cnt_eats)
			g_p.well_fed++;
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
		ft_append_msg(get_time() - philo->birth, philo->pos, M, SLEEP);
		while (get_time() - philo->last_eat < g_p.tt_eat + g_p.tt_sleep)
			usleep(300);
		ft_append_msg(get_time() - philo->birth, philo->pos, B, THINK);
	}
	return (NULL);
}

void	take_forks(t_philo *philo)
{
	if (philo->pos % 2)
	{
		pthread_mutex_lock(philo->lfork);
		ft_append_msg(get_time() - philo->birth, philo->pos, Y, LFORK);
		pthread_mutex_lock(philo->rfork);
		ft_append_msg(get_time() - philo->birth, philo->pos, Y, RFORK);
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		ft_append_msg(get_time() - philo->birth, philo->pos, Y, RFORK);
		pthread_mutex_lock(philo->lfork);
		ft_append_msg(get_time() - philo->birth, philo->pos, Y, LFORK);
	}
	if (get_time() - philo->last_eat > g_p.tt_die)
		pthread_mutex_lock(philo->lfork);
	ft_append_msg(get_time() - philo->birth, philo->pos, G, EAT);
	philo->last_eat = get_time();
}
