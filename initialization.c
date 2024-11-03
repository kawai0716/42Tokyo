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

t_stack *stack_new(int value)
{
	t_stack *new;

	new = malloc(sizeof * new);
	if(!new)
		return(NULL);
	new -> value = value;
	new -> index = 0;
	new -> pos = -1;
	new -> target_pos = -1;
	new -> cost_a = -1;
	new -> cost_b = -1;
	new -> next = NULL;
}

void stack_add_botom(t_stack **stack, t_stack *new)
{
	
}

t_stack fill_stack(int ac, char **av)
{
	long int n;
	int i;
	t_stack *stack_a;

	n  = 0;
	i = 1;
	while(i < ac)
	{
		n = ft_atoi(char av[i])
		if(INT_MAX < n || n < INT_MIN)
			exit_error(&stack_a, NULL);
		if(i == 1)
			stack_a = stack_new((int)n);
		else
			stack_add_botom()
	}
}
