#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

# define FORK	" has taken a fork"
# define EAT	" is eating"
# define SLEEP	" is sleeping"
# define THINK	" is thinking"
# define DIE	" died"

# define COLORED	1
# define STND		"\033[0m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define PURPLE		"\033[35m"
# define BLUE		"\033[36m"
# define RED		"\033[1;31m"

# define TIMEOUT_CHECKING 3000

typedef struct s_philo
{
	size_t			pos;
	pthread_t		trd;
	uint64_t		birth;
	uint64_t		last_eat;
	uint64_t		eat_count;
	void			*p;
	char			msg[256];
	size_t			msg_i;
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
uint64_t	get_time(void);

//logging_utils
void		print_msg2(t_param *p, uint64_t tm, char *color, char *msg);
char		*ft_strdup(const char *s1);
char		*ft_itoa_ulong(uint64_t n);
size_t		ft_strlen(const char *s);
size_t		ft_strcpy(char *dst, const char *src);

// ft_atoi_long
char		ft_atoi_long(const char *str, uint64_t *x);

#endif