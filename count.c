int count_stack(t_stack *stack)
{
	int count;

	count = 0;
	if(!stack)
		return(0);
	while(stack != NULL)
	{
		stack = stack->next;
		count++;
	}
	return(count);
}
