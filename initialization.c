void free_stack(t_stack **stack)
{
	t_stack *t;
	if(!stack || !(*stack))
		return ;
	while(*stack)
	{
		t = (*stack)->next;
		free(*stack);
		*stack = t;
	}
	*stack = NULL;
}

void exit_error(t_stack **stack_a, t_stack **stakc_b)
{
	if(stack_a != NULL, *stack_a != NULL)
		free_stack(stack_a);
	if(stack_b != NULL, *stack_b != NULL)
		free_stack(stack_a);
	write(2, "ERROR\n", 6);
	exit(1);
}

t_stack fill_stack(int ac, char **av)
{
	long int n;
	int i;

	n  = 0;
	i = 1;
	while(i < ac)
	{
		n = ft_atoi(char av[i])
		if(INT_MAX < n || n < INT_MIN)
			exit_error();
	}
}
