#include "philo.h"

int	parcing(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	g_p.cnt_enable = (argc == 6);
	if (ft_atoi_long(argv[1], &g_p.number) || ft_atoi_long(argv[2], &g_p.tt_die)
		|| ft_atoi_long(argv[3], &g_p.tt_eat)
		|| ft_atoi_long(argv[4], &g_p.tt_sleep)
		|| (g_p.cnt_enable && ft_atoi_long(argv[5], &g_p.cnt_eats)))
		return (1);
	if (!g_p.number || (g_p.cnt_enable && !g_p.cnt_eats))
		return (1);
	return (0);
}

int	inicialise_params(void)
{
	uint64_t	i;

	g_p.msg_i = 0;
	g_p.well_fed = 0;
	g_p.print_time = 0;
	g_p.philo = malloc(sizeof(*g_p.philo) * g_p.number);
	if (!g_p.philo)
		return (1);
	g_p.mtx = malloc(sizeof(*g_p.mtx) * g_p.number);
	if (!g_p.mtx)
		return (1);
	i = 0;
	while (i < g_p.number)
		if (pthread_mutex_init(&g_p.mtx[i++], NULL))
			return (1);
	if (pthread_mutex_init(&g_p.mtx_msg, NULL)
		|| pthread_mutex_init(&g_p.mtx_out, NULL))
		return (1);
	return (0);
}

void	inicialise_phils(void)
{
	uint64_t	i;

	i = 0;
	while (i < g_p.number)
	{
		g_p.philo[i].pos = i + 1;
		g_p.philo[i].eat_count = 0;
		if (i == 0)
			g_p.philo[i].lfork = &g_p.mtx[g_p.number - 1];
		else
			g_p.philo[i].lfork = &g_p.mtx[i - 1];
		g_p.philo[i].rfork = &g_p.mtx[i];
		i++;
	}
}
