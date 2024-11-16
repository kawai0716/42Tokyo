void rotate(t_stack **stack)
{
	t_stack *s;
	t_stack *s2;

	s = *stack;
}

void ra(t_stack **stack_a)
{
	rotate(stack_a);
	ft_putstr("ra");
}

void rb(t_stack **stack_b)
{
	rotate(stack_b);
	ft_putstr("rb");
}
