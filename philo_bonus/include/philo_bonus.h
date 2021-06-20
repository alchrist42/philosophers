#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

# define FORK  " has taken a fork"
# define EAT	" is eating"
# define SLEEP	" is sleeping"
# define THINK	" is thinking"
# define DIE	" died"

# define COLORED	1
# define STND "\033[0m"
# define G "\033[32m"
# define Y "\033[33m"
# define B "\033[35m"
# define M "\033[36m"
# define RB "\033[1;31m"

# define TIMEOUT_CHECKING 3000

typedef struct s_philo
{
	size_t			pos;
	pthread_t		trd;
	uint64_t		birth;
	uint64_t		last_eat;
	uint64_t		eat_count;
	void			*p;
}					t_philo;

typedef struct s_param
{
	uint64_t	number;
	uint64_t	tt_die;
	uint64_t	tt_eat;
	uint64_t	tt_sleep;
	uint64_t	cnt_eats;
	bool		cnt_enable;
	uint64_t	well_fed;
	int			*pid;
	size_t		p_ind;
	sem_t		*forks;
	sem_t		*out_msg;
	sem_t		*both_fork;

	t_philo		philo;

	

}	t_param;

// philo_main
int			main(int argc, char **argv);
void		run_forks(t_param *p);
void		observer_waiter(t_param *p);

// philo_fork
void		child_life(t_param *p);
void		*philo_birth(void *param);
void		philo_loop(t_param *p, t_philo *philo);

// inicialise
void		parcing(t_param *p, int argc, char **argv);
void		inicialise_params(t_param *p);

// utils
void		print_msg(t_param *p, uint64_t tm, size_t pos, char *msg);
uint64_t	get_time(void);

// ft_atoi_long
char		ft_atoi_long(const char *str, uint64_t *x);

#endif