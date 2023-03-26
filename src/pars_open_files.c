/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_open_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:56:58 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/26 17:42:25 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_append(t_lex *g, t_cmd *new)
{
	if (new->out != -2)
		close(new->out);
	if (!ambig_check(g->deleted[g->i + 1], g->splited2[g->i + 1]))
		f_mbig(g, new, 1);
	else
	{
		if (new->out != -1 && new->in != -1)
		{
			trimer(g);
			new->out = open(g->splited2[g->i + 1], O_CREAT | O_APPEND | O_RDWR,
					0644);
			if (new->out == -1)
			{
				ft_putstr_fd("Minishell: ", 2);
				perror(g->splited2[g->i + 1]);
			}
		}
	}
	g->i++;
}

void	fill_heredoc(t_lex *g, t_cmd *new)
{
	char	*tmp;

	new->wf = 1;
	g->i++;
	tmp = g->splited2[g->i];
	g->splited2[g->i] = clean_quotes2(g->splited2[g->i]);
	free(tmp);
	g->full_heredoc = ft_strjoin3(g->full_heredoc, g->splited2[g->i]);
	g->full_heredoc = ft_strjoin3(g->full_heredoc, " ");
}

void	fill_in(t_lex *g, t_cmd *new)
{
	if (new->in != -2)
		close(new->in);
	if (g->deleted[g->i + 1] == 'f'
		|| !ambig_check(g->deleted[g->i + 1], g->splited2[g->i + 1]))
		f_mbig(g, new, 0);
	else if (!ft_strcmp(g->splited2[g->i + 1], ">"))
	{
		g->i++;
		fill_out(g, new);
	}
	else
	{
		if (new->out != -1 && new->in != -1)
			open_in(g, new);
	}
	g->i++;
}

void	fill_out(t_lex *g, t_cmd *new)
{
	if (new->out != -2)
		close(new->out);
	if (!g->splited2[g->i + 1] || g->deleted[g->i + 1] == 'f')
		f_mbig(g, new, 1);
	else if (!ft_strcmp(g->splited2[g->i + 1], "|"))
	{
		if (new->out != -1 && new->in != -1)
		{
			if (!g->splited2[g->i + 2])
				f_mbig(g, new, 1);
			else
				open_out(g, new, &g->splited2[g->i + 2]);
		}
		g->i++;
	}
	else
	{
		if (new->out != -1 && new->in != -1)
			open_out(g, new, &g->splited2[g->i + 1]);
	}
	g->i++;
}
