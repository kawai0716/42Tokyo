/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:26:20 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/21 15:26:20 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*expand_match_result(char *result, char *match)
{
	char	*temp;
	char	*new_result;

	temp = ft_strjoin(result, " ");
	free(result);
	new_result = ft_strjoin(temp, match);
	free(temp);
	free(match);
	return (new_result);
}
