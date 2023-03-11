#include "push_swap_bonus.h"

void	ra_c(t_stack **a)
{
	rotate(a);
}

void	rb_c(t_stack **b)
{
	rotate(b);
}

void	rr_c(t_stack **a, t_stack **b)
{
	rotate(a);
	rotate(b);
}
