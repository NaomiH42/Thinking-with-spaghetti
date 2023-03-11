#include "philosophers.h"

void	error_msg(int	err)
{
	if (err == 1)
		printf("Incorrect number of arguments.\n");
	exit(0);
}

unsigned long int	long_atoi(const char *nptr)
{
	size_t	i;
	int		res;

	res = 0;
	i = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	return (res);
}
