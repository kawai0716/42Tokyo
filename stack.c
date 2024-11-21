t_stack stack_bottom(t_stack *stack)
{
	while(stack != NULL && stack->next != NULL)
		stack = stack->next;
	return(stack);
}

t_stack stack_second_bottom(t_stack *stack)
{
	while(stack != NULL && stack -> next != NULL && stack -> next -> next != NULL)
		stack = stack -> next;
	return(stack);
}
