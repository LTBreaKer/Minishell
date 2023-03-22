/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:19:22 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/20 21:29:46 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	xpnd_status(char *s, int i)
{
	int	index;
	int	ret;

	index = 0;
	while (s[index] && index < i)
	{
		ret = xpnd_in_loop(s, i, &index);
		if (ret != 2)
			return (ret);
	}
	return (0);
}

char	*go_xpnd(t_lex *g, char *s, int idx)
{
	g->len = 0;
	g->id = 0;
	g->dol = idx + 1;
	idx++;
	if (s[idx] == '?')
		return (xpanterrogation(s, g->dol));
	g->target = get_target(s, idx);
	if (g->target[0] == '$')
		return (dol_dol(g->target, s, g->dol));
	else if (g->target[0] == '\0')
		return (dol_zero(g->target, g, s));
	while ((s[idx] && ft_isalnum(s[idx])) || s[idx] == '_')
	{
		g->len++;
		idx++;
	}
	if (g->dol == 1 && s[idx] == '\0')
		g->id = 1;
	g->value = ft_get_value(g->target);
	if (!g->value && g->id)
		return (free(g->target), NULL);
	else if (!g->value && !g->id)
		return (null_val(g->target, s, g->dol, g->len));
	return (free(g->target), normal_case(g->value, s, g->dol, g->len));
}

void	ex_xpnd_help2(t_lex *g, char *ret, int j)
{
	if (ret)
	{
		free(g->splited2[j]);
		g->splited2[j] = ft_strdup(ret);
		g->deleted[j] = 't';
		free(ret);
	}
	else
	{
		g->deleted[j] = 'f';
		shifting(g->splited2, j);
	}
}

void	ex_xpnd_help1(t_lex *g, int j, int doc)
{
	char	*ret;
	int		i;
	int		on;

	on = 0;
	i = 0;
	while (g->splited2[j] && g->splited2[j][i])
	{
		if (on == 1 && !g->here)
			i = 0;
		on = 0;
		g->here = 0;
		if (g->splited2[j] && g->splited2[j][i] == '$')
		{
			if (xpnd_status(g->splited2[j], i) == 0 && doc == 0)
			{
				ret = go_xpnd(g, g->splited2[j], i);
				ex_xpnd_help2(g, ret, j);
				on = 1;
			}
		}
		if (on == 0 || g->here == 1)
			i++;
	}
}

void	expand_me(t_lex *g)
{
	int	doc;
	int	len;
	int	j;
	int	i;

	i = -1;
	len = ft_double_strlen(g->splited2);
	g->deleted = malloc(sizeof(char) * len + 1);
	g->deleted[len] = '\0';
	while (++i < len)
		g->deleted[i] = 'x';
	j = 0;
	while (g->splited2[j])
	{
		doc = 0;
		if (!ft_strcmp(g->splited2[j], "<<"))
		{
			doc = 1;
			g->deleted[j] = 't';
			j++;
		}
		ex_xpnd_help1(g, j, doc);
		j++;
	}
}
