/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_syntax_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:57:25 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/27 15:05:02 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quotes_check_helper(t_lex *g)
{
	if (g->line[g->id] == 39)
	{
		g->id++;
		g->dq++;
		while (g->line[g->id] != 39 && g->line[g->id])
			g->id++;
		if (g->line[g->id] == 39)
			g->dq++;
	}
	else if (g->line[g->id] == 34)
	{
		g->id++;
		g->sq++;
		while (g->line[g->id] != 34 && g->line[g->id])
			g->id++;
		if (g->line[g->id] == 34)
			g->sq++;
	}
}

void	red_syntax_helper(t_lex *g)
{
	if (g->line[g->k] == 39)
	{
		g->k++;
		while (g->line[g->k] != 39 && g->line[g->k])
			g->k++;
	}
	else if (g->line[g->k] == 34)
	{
		g->k++;
		while (g->line[g->k] != 34 && g->line[g->k])
			g->k++;
	}
	else if (g->line[g->k] == '<' || g->line[g->k] == '>')
	{
		g->k++;
		while (g->line[g->k] == ' ' || g->line[g->k] == '\t'
			|| g->line[g->k] == '\n')
		{
			g->k++;
			g->here = 1;
		}
		if (g->here == 1 && (g->line[g->k] == '<' || g->line[g->k] == '>'
				|| g->line[g->k] == '|'))
			g->space_exist = 1;
	}
}

int	broken_psh(t_lex *g, int i)
{
	if (!ft_strcmp(g->splited2[i], "|") && !ft_strcmp(g->splited2[i + 1],
			"|"))
		return (0);
	else if ((!ft_strcmp(g->splited2[i], "<") || !ft_strcmp(g->splited2[i],
				">>") || !ft_strcmp(g->splited2[i], "<<"))
		&& (!ft_strcmp(g->splited2[i + 1], "|")))
		return (0);
	else if ((g->splited2[i][0] == '<' || g->splited2[i][0] == '>'
				|| !ft_strcmp(g->splited2[i], ">>")
				|| !ft_strcmp(g->splited2[i], "<<")) && g->splited2[i
			+ 1][0] == '|' && (g->splited2[i + 2][0] == '<' || g->splited2[i
				+ 2][0] == '>' || !ft_strcmp(g->splited2[i + 2], ">>")
				|| !ft_strcmp(g->splited2[i + 2], "<<")))
		return (0);
	else
		return (1);
}

int	broken_psh2(t_lex *g, int i)
{
	if ((!ft_strcmp(g->splited2[i], "<<") || !ft_strcmp(g->splited2[i], ">>"))
		&& (!ft_strcmp(g->splited2[i + 1], "<") || !ft_strcmp(g->splited2[i
					+ 1], ">") || !ft_strcmp(g->splited2[i + 1], "<<")
			|| !ft_strcmp(g->splited2[i + 1], ">>")))
		return (0);
	else if ((!ft_strcmp(g->splited2[i], "<") || !ft_strcmp(g->splited2[i],
				">")) && (!ft_strcmp(g->splited2[i + 1], "<<")
			|| !ft_strcmp(g->splited2[i + 1], ">>")))
		return (0);
	else if (!ft_strcmp(g->splited2[i], ">") && !ft_strcmp(g->splited2[i + 1],
			"<"))
		return (0);
	else if ((!ft_strcmp(g->splited2[i], "<") && !ft_strcmp(g->splited2[i + 1],
				"<")) || (!ft_strcmp(g->splited2[i], ">")
			&& !ft_strcmp(g->splited2[i + 1], ">")))
		return (0);
	else if (((!ft_strcmp(g->splited2[i], ">") && !ft_strcmp(g->splited2[i + 1],
					"<")) || (!ft_strcmp(g->splited2[i], ">")
				&& !ft_strcmp(g->splited2[i + 1], "|")))
		&& g->space_exist == 1)
		return (0);
	else
		return (1);
}

char	*pipe_syntax_helper(t_lex *g)
{
	int	i;
	int	len;

	len = ft_double_strlen(g->splited2) - 1;
	i = 0;
	while (i < len && g->splited2[i])
	{
		if (broken_psh(g, i) == 0)
			return (put_stx_idx(g, "|", i));
		else if (broken_psh2(g, i) == 0)
			return (put_stx_idx(g, "redirection", i));
		i++;
	}
	return (NULL);
}
