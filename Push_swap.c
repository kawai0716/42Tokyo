#include "Push_swap.h"

int main(int ac, char **av)
{
	t_stack *stack_a;
	t_stack *stack_b;

	if(ac < 2)
		return(0);
	stack_a = init_stack();
	stack_b = init_stack();

	if(!parse_arguments(ac, av, &stack_a))
	{
		write(2, error\n, 6);
		freestack(stack_a);
		freestack(stack_b);
		return (1);
	}
	if (stack_a->size <= 3) 
        sortThree(&stack_a);
    else if (stack_a->size <= 6)
        sortSix(&stack_a, &stack_b);
    else
        quickSort(&stack_a, &stack_b, stack_a->size);
    freeStack(stack_a);
    freeStack(stack_b);
    return(0);
}
