static void sort(t_satck **s1, t_stack **s2)
{
	t_stack *s3;
	if(!s2)
		return;
	s3 = (*s2) -> next;
	(*s2) -> next = *s1;
	*s1=*s2;
	*s2 = s3;
}

void	pa(t_stack **stack_a, t_stack **stack_b)
{
	push(stack_a, stack_b);
	ft_putstr("pa\n");
}

void	pb(t_stack **stack_a, t_stack **stack_b)
{
	push(stack_b, stack_a);
	ft_putstr("pb\n");
}
