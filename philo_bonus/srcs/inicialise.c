#include "philo_bonus.h"

void	parcing(t_param *p, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		exit (1);
	p->cnt_enable = (argc == 6);
	if (ft_atoi_long(argv[1], &p->number) || ft_atoi_long(argv[2], &p->tt_die)
		|| ft_atoi_long(argv[3], &p->tt_eat)
		|| ft_atoi_long(argv[4], &p->tt_sleep)
		|| (p->cnt_enable && ft_atoi_long(argv[5], &p->cnt_eats)))
		exit (1);
	if (!p->number || (p->cnt_enable && !p->cnt_eats))
		exit (1);
}

void	inicialise_params(t_param *p)
{
	sem_unlink("forks");
	sem_unlink("out_msg");
	sem_unlink("both_fork");
	p->forks = sem_open("forks", O_CREAT, S_IRWXU, p->number);
	p->out_msg = sem_open("out_msg", O_CREAT, S_IRWXU, p->number);
	p->both_fork = sem_open("both_fork", O_CREAT, S_IRWXU, p->number);
	if (p->forks == SEM_FAILED || p->out_msg == SEM_FAILED
		|| p->both_fork == SEM_FAILED)
		exit(1);
	p->p_ind = 0;
	p->philo.pos = 1;
	p->philo.eat_count = 0;
	p->well_fed = 0;
	p->pid = malloc(sizeof(*p->pid) * p->number);
	if (!p->pid)
		exit (1);
}
