/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_flist_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:41:38 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/22 20:06:01 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ftlist_helper(t_lex *g, t_cmd *new)
{
	if (!*g->full_heredoc)
	{
		free (g->full_heredoc);
		g->full_heredoc = NULL;
	}
	if (g->full_heredoc)
	{
		new->heredoc = ft_split_qk(g->full_heredoc, ' ');
		free(g->full_heredoc);
	}
}

void	clone_top(t_lex *g, t_cmd *new, t_cmd **lst)
{
	if (g->full_heredoc && !*g->full_heredoc)
	{
		free (g->full_heredoc);
		free(new);
		g->full_heredoc = NULL;
	}
	if (g->full_heredoc)
	{
		new->heredoc = ft_split_qk(g->full_heredoc, ' ');
		ft_lstadd_backfinal(lst, new);
		free(g->full_heredoc);
	}
}

void	fill_args_helper(t_lex *g, t_cmd *new)
{
	g->i--;
	if (new->args != NULL)
	{
		free_split(new->args);
		new->args = ft_split_qk(g->full_cmd, ' ');
	}
	else
		new->args = ft_split_qk(g->full_cmd, ' ');
}

void	fill_args_helper2(t_lex *g)
{
	g->full_cmd = ft_strjoin3(g->full_cmd, " ");
	g->full_cmd = ft_strjoin3(g->full_cmd, "-n");
}

char	*put_stx_idx(t_lex *g, char *ret, int i)
{
	g->idx_stx = i;
	return (ret);
}
