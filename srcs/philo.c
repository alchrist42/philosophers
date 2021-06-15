#include "philo.h"

int	main(int argc, char **argv)
{
	if (inicialise(argc, argv))
		return (1);
	printf("numb=%lld, die=%lld, eat=%lld, sleep=%lld, cnt=%llu\n", g_p.number, g_p.tt_die, g_p.tt_eat, g_p.tt_sleep, g_p.cnt_eats);
	inicialise_phils();
	g_p.print_time = get_time();
	
	if (run_philo_treads())
		return (1);
	if (pthread_create(&g_p.log_trd, NULL, logging_thread, (void *)NULL))
		return (1);
	
	pthread_join(g_p.philo[1].trd, NULL);
	pthread_join(g_p.log_trd, NULL);
	
}

int	run_philo_treads(void)
{
	size_t	i;

	i = 0;
	while (i < g_p.number)
	{
		if (pthread_create(&g_p.philo[i].trd, NULL, philo_life, (void *)(g_p.philo + i)))
			return (1);
		i += 2;
		if (i >= g_p.number && !(i % 2))
			i = 1;
		usleep(30);
	}
	return (0);
}



void	*philo_life(void *philosoph)
{
	t_philo	*philo;

	philo = (t_philo *)philosoph;
	philo->birth = get_time();
	philo->last_eat = get_time();
	while (!g_p.cnt_enable || philo->eat_count == g_p.cnt_eats)
	{
		if (philo->pos % 2)
		{
			pthread_mutex_lock(philo->lfork);
			ft_append_message(get_time() - philo->birth, philo->pos, LFORK, 1);
			pthread_mutex_lock(philo->rfork);
			ft_append_message(get_time() - philo->birth, philo->pos, RFORK, 1);
		}
		else
		{
			pthread_mutex_lock(philo->rfork);
			ft_append_message(get_time() - philo->birth, philo->pos, RFORK, 1);
			pthread_mutex_lock(philo->lfork);
			ft_append_message(get_time() - philo->birth, philo->pos, LFORK, 1);
		}
		ft_append_message(get_time() - philo->birth, philo->pos, EAT, 1);
		philo->last_eat = get_time();
		
		usleep_fix(g_p.tt_eat);
		pthread_mutex_unlock(philo->lfork);
		// ft_append_message(get_time() - philo->birth, philo->pos, RLFORK, 1);
		pthread_mutex_unlock(philo->rfork);
		// ft_append_message(get_time() - philo->birth, philo->pos, RRFORK, 1);
		if (++philo->eat_count == g_p.cnt_eats)
			break;
		ft_append_message(get_time() - philo->birth, philo->pos, SLEEP, 1);
		usleep_fix(g_p.tt_sleep);
		ft_append_message(get_time() - philo->birth, philo->pos, THINK, 1);
	}
	return ((void *)NULL);
}
