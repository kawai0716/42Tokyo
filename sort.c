void swap(*stack)
{
	int n;

	if(!stack && !stack -> next)
		return;
	n = stack -> value;
	stack -> value = stack -> next -> value;
	stack -> next -> value = n;
	n = stack -> index;
	stack -> index = stack -> next -> index;
	stack -> next -> index = n;
	
}

void sa(t_stack **stack)
{
	sort(*stack);
	ft_putstr("sa\n");
}

void sb(t_stack **stack)
{
	sort(*stack);
	ft_putstr("sb\n");
}

void ss(t_stack **stack_a, t_stack **stack_b)
{
	sort(*stack_a);
	sort(*stack_b);
	ft_putstr("ss\n");
}
