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

typedef struct s_philo
{
	size_t			pos;
	pthread_t		trd;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	uint64_t		birth;
	uint64_t		last_eat;
	uint64_t		eat_count;
}					t_philo;

typedef struct s_param
{
	uint64_t		number;
	uint64_t		tt_die;
	uint64_t		tt_eat;
	uint64_t		tt_sleep;
	uint64_t		cnt_eats;
	bool			cnt_enable;
	t_philo			*philo;
	pthread_mutex_t	*mtx;
	pthread_mutex_t	mtx_msg;
	pthread_mutex_t	mtx_out;
	pthread_t		watcher_trd;
	pthread_t		log_trd;
	uint64_t		print_time;
	char			msg[64856];
	size_t			msg_i;
}	t_param;

t_param	g_p;

// philo1
int		main(int argc, char **argv);
int		run_philo_treads(void);
void	*philo_life(void *philosoph);

// inicialise
int		inicialise(int argc, char **argv);
void	inicialise_phils(void);

//utils

uint64_t	get_time(void);
void		usleep_fix(uint64_t time);

//logging
int		print_buffer(bool lock_msg);
void	*logging_thread(void *msg);
char	*ft_strdup(const char *s1);
char	*ft_itoa_ulong(uint64_t n);
size_t	ft_strlen(const char *s);
// void	ft_info_message(uint64_t tm, int ind_phil, char *s);
int	ft_append_message(uint64_t tm, int ind_phil, char *s, bool unlock);
size_t	ft_strcpy(char *dst, const char *src);


//ft_atoi_long
char	ft_atoi_long(const char *str, uint64_t *x);

#endif