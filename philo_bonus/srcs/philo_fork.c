#include "philo_bonus.h"

void	child_life(t_param *p)
{
	uint64_t	tm;

	if (pthread_create(&p->philo.trd, NULL, philo_birth, (void *)p))
		exit (2);
	while (true)
	{
		usleep(TIMEOUT_CHECKING);
		tm = get_time();
		if (tm - p->philo.last_eat > p->tt_die)
		{
			sem_wait(p->out_msg);
			print_msg2(p, tm - p->philo.birth, RED, DIE);
			exit (1);
		}
		if (p->cnt_enable && p->philo.eat_count >= p->cnt_eats)
			exit(0);
	}
}

void	*philo_birth(void *param)
{
	t_param	*p;

	p = (t_param *)param;
	pthread_detach(p->philo.trd);
	p->philo.birth = get_time();
	p->philo.last_eat = get_time();
	while (true)
		philo_loop(p, &p->philo);
}

void	philo_loop(t_param *p, t_philo *philo)
{
	sem_wait(p->both_fork);
	sem_wait(p->forks);
	print_msg2(p, get_time() - philo->birth, GREEN, FORK);
	sem_wait(p->forks);
	sem_post(p->both_fork);
	print_msg2(p, get_time() - philo->birth, GREEN, FORK);
	if (get_time() - philo->last_eat < p->tt_die)
	{
		philo->last_eat = get_time();
		print_msg2(p, philo->last_eat - philo->birth, YELLOW, EAT);
	}
	else
		usleep(p->tt_die * 1000);
	while (get_time() - philo->last_eat < p->tt_eat)
		usleep(300);
	sem_post(p->forks);
	sem_post(p->forks);
	philo->eat_count++;
	print_msg2(p, get_time() - philo->birth, BLUE, SLEEP);
	while (get_time() - philo->last_eat < p->tt_eat + p->tt_sleep)
		usleep(300);
	print_msg2(p, get_time() - philo->birth, PURPLE, THINK);
}
