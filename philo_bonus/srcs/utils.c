#include "philo.h"

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

void	usleep_fix(uint64_t time)
{
	uint64_t	t;

	t = get_time();
	while (get_time() - t < time)
		usleep(1);
}

void	usleep_fix2(uint64_t time)
{
	usleep(time * 1000);
}
