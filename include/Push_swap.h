/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:02:54 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/15 06:34:08 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int				value;
	int				index;
	int				pos;
	int				target_pos;
	int				cost_a;
	int				cost_b;
	struct s_stack	*next;
}					t_stack;

void				pa(t_stack **stack_a, t_stack **stack_b);
void				pb(t_stack **stack_a, t_stack **stack_b);
void				sa(t_stack **stack);
void				sb(t_stack **stack);
void				ss(t_stack **stack_a, t_stack **stack_b);
void				ra(t_stack **stack_a);
void				rb(t_stack **stack_b);
void				rr(t_stack **stack_a, t_stack **stack_b);
void				rra(t_stack **stack_a);
void				rrb(t_stack **stack_b);
void				rrr(t_stack **stack_a, t_stack **stack_b);
int					check_number(char **av);
int					ft_isdigit(char c);
int					ft_sign(char c);
int					same_number(const char *s1, const char *s2);
void				cost(t_stack **a, t_stack **b);
int					count_stack(t_stack *stack);
void				fastest_move(t_stack **a, t_stack **b);
void				index_number(t_stack *stack, int stack_size);
t_stack				*stack_new(int value);
t_stack				*fill_stack(int ac, char **av);
void				stack_add_botom(t_stack **stack, t_stack *new);
int					sorted(t_stack *stack);
void				optimal_move(t_stack **a, t_stack **b, int cost_a,
						int cost_b);
void				get_pos(t_stack **stack);
void				get_target_pos(t_stack **a, t_stack **b);
void				sort(t_stack **stack_a, t_stack **stack_b);
t_stack				*move_stack_bottom(t_stack *stack);
t_stack				*stack_second_bottom(t_stack *stack);
void				three_sort(t_stack **stack);
void				free_stack(t_stack **stack);
void				exit_error(t_stack **stack_a, t_stack **stack_b);
void				ft_putstr(char *s);
long int			ft_atoi(char *str);
int					change_plus(int i);

#endif