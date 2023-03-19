/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_flist_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:41:38 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/18 17:32:57 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	trimer(t_lex *g)
{
	g->tmp = g->splited2[g->i + 1];
	g->splited2[g->i + 1] = clean_quotes2(g->splited2[g->i + 1]);
	free(g->tmp);
}

void	fill_append(t_lex *g, t_cmd *new)
{
	if (new->out != -2)
		close(new->out);
	if (!ambig_check(g->deleted[g->i + 1], g->splited2[g->i + 1]))
	{
		ft_putstr_fd("Minishell: ambiguous redirect\n", 2);
		g_env.status = 1;
		new->out = -1;
		g->ambg = 1;
	}
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
	char *tmp;
	new->wf = 1;
	g->i++;
	tmp = g->splited2[g->i];
	g->splited2[g->i] = clean_quotes2(g->splited2[g->i]);
	free(tmp);
	g->full_heredoc = ft_strjoin3(g->full_heredoc, g->splited2[g->i]);
	g->full_heredoc = ft_strjoin3(g->full_heredoc, " ");
}

void	fill_lr(t_lex *g, t_cmd *new)
{
	if (new->in != -2)
		close(new->in);
	else
	{
		if (g->deleted[g->i + 1] == 'f' || !ambig_check(g->deleted[g->i + 1], g->splited2[g->i + 1]))
		{
			ft_putstr_fd("Minishell: ambiguous redirect\n", 2);
			g_env.status = 1;
			new->in = -1;
			g->ambg = 1;
		}
		else if (!ft_strcmp(g->splited2[g->i + 1], ">"))
		{
			g->i++;
			fill_rr(g, new);
		}
		else
		{
			if (new->out != -1 && new->in != -1)
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
		}
	}
	g->i++;
}

int	open_rr(t_lex *g, char **str)
{
	int	fd;

	fd = -2;
	if (ft_strncmp(*str, "/dev/stdout", 12) == 0 && (*str)[12] == 0)
		return (-2);
	if (!ambig_check(g->deleted[g->i + 1], *str))
	{
		ft_putstr_fd("Minishell: ambiguous redirect\n", 2);
		g_env.status = 1;
		fd = -1;
		g->ambg = 1;
	}
	else
	{
		
		g->tmp = *str;
		*str = clean_quotes2(*str);
		// *str = ft_trim(*str);
		if (g->tmp)
			free(g->tmp);
		// WTF ???? 
		fd = open(*str, O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("Minishell: ", 2);
			perror(*str);
		}
	}
	return (fd);
}

void	fill_rr(t_lex *g, t_cmd *new)
{
	if (new->out != -2)
		close(new->out);
	if (!g->splited2[g->i + 1] || g->deleted[g->i + 1] == 'f')
	{
		ft_putstr_fd("Minishell: ambiguous redirect\n", 2);
		g_env.status = 1;
		new->out = -1;
		g->ambg = 1;
	}
	else if (!ft_strcmp(g->splited2[g->i + 1], "|"))
	{
		if (new->out != -1 && new->in != -1)
			new->out = open_rr(g, &g->splited2[g->i + 2]);
		g->i++;
	}
	else
	{
		if (new->out != -1 && new->in != -1)
			new->out = open_rr(g, &g->splited2[g->i + 1]);
	}
	g->i++;
}