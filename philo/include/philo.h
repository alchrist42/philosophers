#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

# define LFORK  " has taken a left fork"
# define RFORK  " has taken a right fork"
# define RLFORK  " release a left fork"
# define RRFORK  " release a right fork"
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

# define BUF 262144

typedef struct s_philo
{
	size_t			pos;
	pthread_t		trd;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	uint64_t		birth;
	uint64_t		last_eat;
	uint64_t		eat_count;
	void			*p;
}					t_philo;

typedef struct s_param
{
	uint64_t		number;
	uint64_t		tt_die;
	uint64_t		tt_eat;
	uint64_t		tt_sleep;
	uint64_t		cnt_eats;
	bool			cnt_enable;
	uint64_t		well_fed;
	t_philo			*philo;
	pthread_mutex_t	*mtx;
	pthread_mutex_t	mtx_msg;
	pthread_mutex_t	mtx_out;
	pthread_t		observer_trd;
	uint64_t		print_time;
	char			msg[BUF];
	size_t			msg_i;
}	t_param;

// philo1
int			main(int argc, char **argv);
int			run_philo_treads(t_param *p);
void		*philo_life(void *philosoph);
void		take_forks(t_param *p, t_philo *philo);

// inicialise
int			parcing(t_param *p, int argc, char **argv);
int			inicialise_params(t_param *p);
void		inicialise_phils(t_param *p);

//utils
uint64_t	get_time(void);
void		usleep_fix(uint64_t time);
void		usleep_fix2(uint64_t time);

//logging
void		*observer_waiter(void *param);
int			ft_append_msg(uint64_t tm, t_philo *philo, char *clr, char *msg);
int			print_buffer(t_param *p, bool lock_msg);

//logging_utils
char		*ft_strdup(const char *s1);
char		*ft_itoa_ulong(uint64_t n);
size_t		ft_strlen(const char *s);
size_t		ft_strcpy(char *dst, const char *src);

//ft_atoi_long
char		ft_atoi_long(const char *str, uint64_t *x);

#endif