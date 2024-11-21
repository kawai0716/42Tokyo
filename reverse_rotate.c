void reverse_rotate(t_stack **stack)
{
	t_stack *s1;
	t_stack *s2;

	s1 = stack_bottom(*stack);
	s2 = stack_second_bottom(*stack);
	
}

void rra(t_stack **stack_a)
{
	reverce_rotate(stack_a);
	ft_putstr("rra");
}

void rrb(t_stack **stack_b)
{
	reverce_rotate(stack_b);
	ft_putstr("rrb");
}

void rra(t_stack **stack_a, t_stack **stack_b)
{
	reverce_rotate(stack_a);
	reverce_rotate(stack_b);
	ft_putstr("rrr");
}
