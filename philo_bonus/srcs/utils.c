#include "philo_bonus.h"

/*
**	@brief	return lenght null terminated string
**	
**	@param	s		pointer to string
**	@return	size_t	lenght string
*/

uint64_t	get_time(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + tm.tv_usec / 1000);
}

void	print_msg(t_param *p, uint64_t tm, size_t pos, char *msg)
{
	sem_wait(p->out_msg);
	printf("%llu %zu %s\n", tm, pos, msg);
	sem_post(p->out_msg);
}
