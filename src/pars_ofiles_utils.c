/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_ofiles_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:40:01 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/20 13:42:21 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	trimer(t_lex *g)
{
	g->tmp = g->splited2[g->i + 1];
	g->splited2[g->i + 1] = clean_quotes2(g->splited2[g->i + 1]);
	free(g->tmp);
}

void	f_mbig(t_lex *g, t_cmd *new, int i)
{
	ft_putstr_fd("Minishell: ambiguous redirect\n", 2);
	g_env.status = 1;
	if (i == 1)
		new->out = -1;
	else if (i == 0)
		new->in = -1;
	g->ambg = 1;
}

void	open_in(t_lex *g, t_cmd *new)
{
	trimer(g);
	new->in = open(g->splited2[g->i + 1], O_RDONLY);
	if (new->in == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		perror(g->splited2[g->i + 1]);
	}
	new->wf = 2;
}

void	open_out(t_lex *g, t_cmd *new, char **str)
{
	if (ft_strncmp(*str, "/dev/stdout", 12) == 0 && (*str)[12] == 0)
		new->out = -2;
	if (!ambig_check(g->deleted[g->i + 1], *str))
		f_mbig(g, new, 1);
	else
	{
		g->tmp = *str;
		*str = clean_quotes2(*str);
		if (g->tmp)
			free(g->tmp);
		new->out = open(*str, O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, 0644);
		if (new->out == -1)
		{
			ft_putstr_fd("Minishell: ", 2);
			perror(*str);
		}
	}
}
