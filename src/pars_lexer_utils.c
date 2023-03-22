/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_lexer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 07:35:30 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/20 09:48:34 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_split(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		i++;
	}
	free(splited);
}

char	*lst_to_str(t_stack *lst)
{
	char	*ret;
	int		len;
	int		i;

	i = 0;
	len = ft_lstsize(lst);
	ret = malloc(sizeof(char) * (len + 1));
	ret[len] = '\0';
	while (lst)
	{
		ret[i] = lst->c;
		i++;
		lst = lst->next;
	}
	return (ret);
}
