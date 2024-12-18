/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:47:42 by mcombeau          #+#    #+#             */
/*   Updated: 2024/12/18 22:02:35 by sykawai          ###   ########.fr       */
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

/* Initialization */

t_stack				*fill_stack(int ac, char **av);
t_stack				*fill_stack2(int ac, char **av);
void				index_number(t_stack *stack_a, int stack_size);

/* Sorting Algorithms */

int					sorted(t_stack *stack);
void				three_sort(t_stack **stack);
void				sort(t_stack **stack_a, t_stack **stack_b);

/* Position */

void				get_target_position(t_stack **stack_a, t_stack **stack_b);
void				get_position(t_stack **stack);

/* Cost */

void				cost(t_stack **a, t_stack **b);
void				fastest_move(t_stack **a, t_stack **b);

/* Calculate Move */

void				optimal_move(t_stack **a, t_stack **b, int cost_a,
						int cost_b);

/* Operations */

void				pa(t_stack **stack_a, t_stack **stack_b);
void				pb(t_stack **stack_a, t_stack **stack_b);
void				sa(t_stack **stack_a);
void				sb(t_stack **stack_b);
void				ss(t_stack **stack_a, t_stack **stack_b);
void				ra(t_stack **stack_a);
void				rb(t_stack **stack_b);
void				rr(t_stack **stack_a, t_stack **stack_b);
void				rrr(t_stack **stack_a, t_stack **stack_b);
void				rra(t_stack **stack_a);
void				rrb(t_stack **stack_b);

/* Stack Functions */

t_stack				*move_stack_bottom(t_stack *stack);
t_stack				*move_stack_second_bottom(t_stack *stack);
t_stack				*stack_new(int value);
void				stack_add_bottom(t_stack **stack, t_stack *new);
int					count_stack(t_stack *stack);
void				free_stack(t_stack **stack);
void				exit_error(t_stack **stack_a, t_stack **stack_b);
void				ft_putstr(char *s);
long int			ft_atoi(const char *str);
int					change_plus(int i);
char				**ft_split(char const *s, char c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				free_split(char **ptr);
int					count_av(char **av);

/* Input Check */

int					check_number(char **av);
int					ft_isdigit(char c);
int					ft_sign(char c);
int					same_number(const char *s1, const char *s2);
#endif