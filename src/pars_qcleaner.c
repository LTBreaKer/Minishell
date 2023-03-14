/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_qcleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:34:34 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/14 13:38:58 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*fcleaned_helper(t_lex *g, char *s, char *ret, int n)
{
	g->i++;
	while (s[g->i] && s[g->i] != n)
	{
		ret[g->k] = s[g->i];
		g->i++;
		g->k++;
	}
	return (ret);
}

char	*fill_cleaned(t_lex *g, char *s, char *ret)
{
	g->k = 0;
	g->i = 0;
	while (s[g->i])
	{
		if (s[g->i] == 39)
			ret = fcleaned_helper(g, s, ret, 39);
		else if (s[g->i] == 34)
			ret = fcleaned_helper(g, s, ret, 34);
		if (s[g->i] && (s[g->i] == 34 || s[g->i] == 39))
			g->i++;
		else if (s[g->i] && s[g->i] != 34 && s[g->i] != 39)
		{
			ret[g->k] = s[g->i];
			g->i++;
			g->k++;
		}
	}
	return (ret);
}

void	cquotes_helper(t_lex *g, char *s, int n)
{
	g->i++;
	while (s[g->i] != n && s[g->i])
	{
		g->len++;
		g->i++;
	}
}

char	*clean_quotes(t_lex *g, char *s)
{
	char	*ret;

	g->len = 0;
	g->i = 0;
	while (s[g->i])
	{
		if (s[g->i] == 39)
			cquotes_helper(g, s, 39);
		else if (s[g->i] == 34)
			cquotes_helper(g, s, 34);
		if (s[g->i] && (s[g->i] == 34 || s[g->i] == 39))
			g->i++;
		else if (s[g->i] && s[g->i] != 34 && s[g->i] != 39)
		{
			g->i++;
			g->len++;
		}
	}
	ret = malloc(sizeof(char) * (g->len + 1));
	ret[g->len] = '\0';
	ret = fill_cleaned(g, s, ret);
	return (ret);
}

void	clean_me(t_lex *g, char **args)
{
	char	*clean;

	if (args == NULL)
		return;
	g->j = 0;
	while (args[g->j])
	{
		clean = clean_quotes(g, args[g->j]);
		free(args[g->j]);
		args[g->j] = clean;
		g->j++;
	}
}
