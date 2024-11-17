t_stack stack_bottom(t_stack *stack)
{
	while(stack != NULL && stack->next != NULL)
		stack = stack->next;
	return(stack);
}
