#include "../includes/philo.h"

void	philo_sleep(unsigned int time)
{
	unsigned int	start;

	start = gettimeofday();
	printf("start: %d\n", start);
	if (time > 1)
		usleep(time * 1000 - 1000);
	while (start - time * 1000 < gettimeofday())
		usleep(1);
	printf("end: %d\n", gettimeofday());
}

int main()
{
	philo_sleep(1000);
	return (0);
}
