/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_lexer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 07:35:30 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/09 15:51:20 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_sub_split(char **splited)
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

void	find_size(t_lex *g)
{
	int	i;
	int	j;

	i = 0;
	g->len = 0;
	while (g->splited1[i])
	{
		j = 0;
		g->sub_split = ft_split_qk(g->splited1[i], ' ');
		while (g->sub_split[j])
		{
			j++;
			g->len++;
		}
		free_sub_split(g->sub_split);
		i++;
	}
}

char	*fill_it(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * ft_strlen(str) + 1);
	ret[ft_strlen(str)] = '\0';
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

void	ft_transfert(t_lex *g)
{
	int	k;

	find_size(g);
	g->i = 0;
	k = 0;
	g->splited2 = malloc(sizeof(char *) * (g->len + 1));
	g->splited2[g->len] = NULL;
	while (g->splited1[g->i])
	{
		g->sub_split = ft_split_qk(g->splited1[g->i], ' ');
		g->j = 0;
		while (g->sub_split[g->j])
		{
			g->splited2[k] = fill_it(g->sub_split[g->j]);
			g->j++;
			k++;
		}
		free_sub_split(g->sub_split);
		g->i++;
	}
}
