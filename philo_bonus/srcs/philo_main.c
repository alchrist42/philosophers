#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_param	p;

	parcing(&p, argc, argv);
	inicialise_params(&p);
	run_forks(&p);
	observer_waiter(&p);
	return (0);
}

void	run_forks(t_param *p)
{
	while (p->philo.pos <= p->number)
	{
		p->pid[p->philo.pos - 1] = fork();
		if (p->pid[p->philo.pos - 1]) // father
			p->p_ind++;
		else
		{
			child_life(p);
			printf("the impossible exit from child %zu\n", p->philo.pos);
			exit(1);
		}
	}
}

void	observer_waiter(t_param *p)
{
	size_t	i;
	int		ret_status;
	
	i = 0;
	while (p->well_fed < p->number)
	{
		waitpid(-1, &ret_status, 0);
		if (WEXITSTATUS(ret_status) != 0)
			while (i < p->number)
				kill(p->pid[i++], SIGKILL);
		p->well_fed++;
	}
}
