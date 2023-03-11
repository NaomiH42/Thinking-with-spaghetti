#include "push_swap_bonus.h"

void	pa_c(t_stack **a, t_stack **b)
{
	push(b, a);
}

void	pb_c(t_stack **a, t_stack **b)
{
	push(a, b);
}

void	rra_c(t_stack **a)
{
	reverse_rotate(a);
}

void	rrb_c(t_stack **b)
{
	reverse_rotate(b);
}

void	rrr_c(t_stack **a, t_stack **b)
{
	reverse_rotate(a);
	reverse_rotate(b);
}
