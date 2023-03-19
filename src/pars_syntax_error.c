/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_syntax_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:52:19 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/16 16:29:39 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*pipe_syntax_helper(t_lex *g)
{
	int	i;

	i = ft_double_strlen(g->splited2) - 1;
	while (--i > 1)
	{
		if (!ft_strcmp(g->splited2[i], "|") && !ft_strcmp(g->splited2[i - 1], "|"))
			return ("|");
		else if ((!ft_strcmp(g->splited2[i - 1], "<")
					|| !ft_strcmp(g->splited2[i - 1], ">>")
					|| !ft_strcmp(g->splited2[i - 1], "<<"))
				&& (!ft_strcmp(g->splited2[i], "|")))
			return ("|");
		else if ((g->splited2[i][0] == '<' || g->splited2[i][0] == '>' || !ft_strcmp(g->splited2[i], ">>") || !ft_strcmp(g->splited2[i], "<<"))
				&& g->splited2[i - 1][0] == '|' && (g->splited2[i - 2][0] == '<' || g->splited2[i - 2][0] == '>' || !ft_strcmp(g->splited2[i - 2], ">>") || !ft_strcmp(g->splited2[i - 2], "<<")))
			return ("|");
	}
	return (NULL);
}

char	*pipe_syntax(t_lex *g)
{
	int		i;
	int		j;
	int		len;
	char	*ret;

	len = ft_double_strlen(g->splited2) - 1;
	j = 0;
	i = 0;
	if ((g->splited2[i][j] == '|' && g->splited2[i][j + 1] == '\0')
		|| (g->splited2[len][j] == '|' && g->splited2[len][j + 1] == '\0'))
		return ("|");
	else if ((g->splited2[i][j] == '|' && g->splited2[i][j + 1] == '|')
			|| (g->splited2[len][j] == '|' && g->splited2[len][j + 1] == '|'))
		return ("|");
	if ((!ft_strcmp(g->splited2[i], "<") || !ft_strcmp(g->splited2[i], "<<")
			|| !ft_strcmp(g->splited2[i], ">>")) && (!ft_strcmp(g->splited2[i
				+ 1], "|")))
		return ("|");
	else if ((!ft_strcmp(g->splited2[i], "<") || !ft_strcmp(g->splited2[i],
					"<<") || !ft_strcmp(g->splited2[i], ">>")
				|| !ft_strcmp(g->splited2[i], ">")) && (!ft_strcmp(g->splited2[i
					+ 1], "||")))
		return ("|");
	ret = pipe_syntax_helper(g);
	return (ret);
}

char	*red_syntax_helper(t_lex *g)
{
	int	i;

	i = ft_double_strlen(g->splited2) - 2;
	while (i > 0)
	{
		if ((!ft_strcmp(g->splited2[i], "<<") || !ft_strcmp(g->splited2[i],
					">>")) && (!ft_strcmp(g->splited2[i - 1], "<")
				|| !ft_strcmp(g->splited2[i - 1], ">")
				|| !ft_strcmp(g->splited2[i - 1], "<<")
				|| !ft_strcmp(g->splited2[i - 1], ">>")))
			return ("redirection");
		else if ((!ft_strcmp(g->splited2[i], "<") || !ft_strcmp(g->splited2[i], ">")) && (!ft_strcmp(g->splited2[i - 1], "<<") || !ft_strcmp(g->splited2[i - 1], ">>")))
			return ("redirection");
		else if (!ft_strcmp(g->splited2[i], "<") && !ft_strcmp(g->splited2[i
					- 1], ">"))
			return ("redirection");
		else if ((!ft_strcmp(g->splited2[i], "<") && !ft_strcmp(g->splited2[i
						- 1], "<")) || (!ft_strcmp(g->splited2[i], ">")
					&& !ft_strcmp(g->splited2[i - 1], ">")))
			return ("redirection");
		else if (((!ft_strcmp(g->splited2[i], ">") && !ft_strcmp(g->splited2[i
					- 1], "<")) || (!ft_strcmp(g->splited2[i], "|") && !ft_strcmp(g->splited2[i - 1], ">"))) && g->space_exist == 1)
			return ("redirection");
		i--;
	}
	return (NULL);
}

void	red_syntax_helper2(t_lex *g)
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
		if (g->here == 1 && (g->line[g->k] == '<' || g->line[g->k] == '>' || g->line[g->k] == '|'))
			g->space_exist = 1;
	}
}

char	*red_syntax(t_lex *g)
{
	int		len;
	char	*ret;

	g->k = 0;
	g->space_exist = 0;
	while (g->line[g->k])
	{
		g->here = 0;
		red_syntax_helper2(g);
		if (g->line[g->k])
			g->k++;
	}
	len = ft_double_strlen(g->splited2) - 1;
	if (!ft_strcmp(g->splited2[len], "<") || !ft_strcmp(g->splited2[len], ">")
		|| !ft_strcmp(g->splited2[len], "<<") || !ft_strcmp(g->splited2[len],
			">>"))
		return ("redirection");
	ret = red_syntax_helper(g);
	return (ret);
}

char	*syntax_check(t_lex *g)
{
	char	*err;

	if (ft_double_strlen(g->splited2) < 2 && (!ft_strcmp(g->splited2[0], "<") || !ft_strcmp(g->splited2[0], ">")
		|| !ft_strcmp(g->splited2[0], "<<") || !ft_strcmp(g->splited2[0],
			">>")))
		return (g->splited2[0]);
	err = pipe_syntax(g);
	if (err != NULL)
		return (err);
	err = red_syntax(g);
	if (err != NULL)
		return (err);
	return (NULL);
}

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

int	quotes_check(t_lex *g)
{
	g->id = 0;
	g->sq = 0;
	g->dq = 0;
	while (g->line[g->id])
	{
		quotes_check_helper(g);
		if (g->line[g->id])
			g->id++;
	}
	if ((g->sq % 2) || (g->dq % 2))
		return (0);
	else
		return (1);
}
