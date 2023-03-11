#include "push_swap_bonus.h"

int	input(t_stack **a, t_stack **b, char *action)
{
	if (!ft_strncmp(action, "sa\n", 3))
		return (sa_c(a), 1);
	else if (!ft_strncmp(action, "sb\n", 3))
		return (sb_c(b), 1);
	else if (!ft_strncmp(action, "ss\n", 3))
		return (ss_c(a, b), 1);
	else if (!ft_strncmp(action, "pa\n", 3))
		return (pa_c(a, b), 1);
	else if (!ft_strncmp(action, "pb\n", 3))
		return (pb_c(a, b), 1);
	else if (!ft_strncmp(action, "ra\n", 3))
		return (ra_c(a), 1);
	else if (!ft_strncmp(action, "rb\n", 3))
		return (rb_c(b), 1);
	else if (!ft_strncmp(action, "rr\n", 3))
		return (rr_c(a, b), 1);
	else if (!ft_strncmp(action, "rra\n", 4))
		return (rra_c(a), 1);
	else if (!ft_strncmp(action, "rrb\n", 4))
		return (rrb_c(b), 1);
	else if (!ft_strncmp(action, "rrr\n", 4))
		return (rrr_c(a, b), 1);
	else
		return (0);
}

void	read_input(t_stack **a, t_stack **b, int flag, char **argv)
{
	char	*buffer;

	buffer = get_next_line(STDIN_FILENO);
	while (buffer)
	{
		if (input(a, b, buffer) == 0)
		{
			free(buffer);
			ft_printf("Error\n");
			free_stuff(NULL, a, flag, argv);
			exit(0);
		}
		free(buffer);
		buffer = get_next_line(STDIN_FILENO);
	}
}

void	print_res(t_stack **a)
{
	if (a_is_sort(a))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
}

int	main(int argc, char **argv)
{
	static int		i;
	static int		flag;
	t_stack			*stacks[3];

	if (argc == 1)
		return (0);
	if (argc == 2)
		argv = split_numbers(&argc, argv, &flag);
	check_arg(argc, argv);
	if (argc == 2)
		return (0);
	stacks[0] = malloc(sizeof(*stacks[0]));
	stacks[0]->content = ft_atoi(argv[++i]);
	stacks[2] = stacks[0];
	stacks[1] = NULL;
	while (++i < argc)
	{
		stacks[2]->next = ft_calloc(sizeof (*stacks[0]), 1);
		stacks[2] = stacks[2]->next;
		stacks[2]->content = ft_atoi(argv[i]);
	}
	read_input(&stacks[0], &stacks[1], flag, argv);
	print_res(&stacks[0]);
	free_stuff(NULL, &(stacks[0]), flag, argv);
}
