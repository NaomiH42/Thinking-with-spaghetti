#include "philosophers.h"

void	error_msg(int	err)
{
	if (err == 1)
		printf("Incorrect number of arguments.\n");
	else
		printf("Invalid argument.\n");
	exit(0);
}

int	long_atoi(const char *nptr)
{
	size_t	i;
	int		m;
	int		res;

	m = 1;
	res = 0;
	i = 0;
	while ((nptr[i] == ' ') || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-')
	{
		i++;
		m = -1;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	return (res * m);
}
