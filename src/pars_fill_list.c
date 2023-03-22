/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_fill_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:11:11 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/21 21:12:58 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_args(t_lex *g, t_cmd *new)
{
	g->k = 1;
	while (g->splited2[g->i] && ft_strcmp(g->splited2[g->i], "<<")
		&& ft_strcmp(g->splited2[g->i], "<") && ft_strcmp(g->splited2[g->i],
			">>") && ft_strcmp(g->splited2[g->i], ">")
		&& ft_strcmp(g->splited2[g->i], "|"))
	{
		g->full_cmd = ft_strjoin3(g->full_cmd, g->splited2[g->i]);
		if (!ft_strcmp(g->full_cmd, "echo") && g->idx == 0)
		{
			g->idx = 1;
			while (g->splited2[g->k] && check_dash_n(g->splited2[g->k]) != 0)
			{
				g->k++;
				g->i++;
				g->idx = 2;
			}
			if (g->idx == 2)
				fill_args_helper2(g);
		}
		g->full_cmd = ft_strjoin3(g->full_cmd, " ");
		g->i++;
	}
	fill_args_helper(g, new);
}

void	distribution(t_lex *g, t_cmd *new)
{
	while (g->splited2[g->i] && ft_strcmp(g->splited2[g->i], "|"))
	{
		g->idx = 0;
		if (ft_strcmp(g->splited2[g->i], "<<") && ft_strcmp(g->splited2[g->i],
				"<") && ft_strcmp(g->splited2[g->i], ">>")
			&& ft_strcmp(g->splited2[g->i], ">") && ft_strcmp(g->splited2[g->i],
				"|"))
			fill_args(g, new);
		else if (!ft_strcmp(g->splited2[g->i], ">"))
			fill_out(g, new);
		else if (!ft_strcmp(g->splited2[g->i], "<"))
			fill_in(g, new);
		else if (!ft_strcmp(g->splited2[g->i], ">>"))
			fill_append(g, new);
		else if (!ft_strcmp(g->splited2[g->i], "<<"))
			fill_heredoc(g, new);
		if (g->ambg == 1)
			while (g->splited2[g->i] && ft_strcmp(g->splited2[g->i], "|"))
				g->i++;
		else if (g->splited2[g->i])
			g->i++;
	}
}

void	fill_the_list(t_lex *g, t_cmd **lst_final)
{
	t_cmd	*new;

	g->i = 0;
	while (g->splited2[g->i])
	{
		g->ambg = 0;
		new = ft_lstfinalnew();
		g->full_cmd = ft_strdup("");
		g->full_heredoc = ft_strdup("");
		distribution(g, new);
		if (g->full_cmd)
			free(g->full_cmd);
		ftlist_helper(g, new);
		ft_lstadd_backfinal(lst_final, new);
		if (g->splited2[g->i])
			g->i++;
	}
}
