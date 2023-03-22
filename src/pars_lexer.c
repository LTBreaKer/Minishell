/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:16:19 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/20 09:44:39 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lex_helper1(t_lex *g, t_stack **lst)
{
	if (g->line[g->idx] == '|' || g->line[g->idx] == '<'
		|| g->line[g->idx] == '>')
		add_push(lst, ' ');
	else if (g->line[g->idx + 1] == '|' || g->line[g->idx + 1] == '<'
			|| g->line[g->idx + 1] == '>')
		add_push(lst, ' ');
}

void	lex_helper2(t_lex *g, t_stack **lst)
{
	if (g->line[g->idx] == 39)
	{
		add_push(lst, g->line[g->idx]);
		g->idx--;
		while (g->line[g->idx] != 39)
		{
			add_push(lst, g->line[g->idx]);
			g->idx--;
		}
	}
	else if (g->line[g->idx] == 34)
	{
		add_push(lst, g->line[g->idx]);
		g->idx--;
		while (g->line[g->idx] != 34)
		{
			add_push(lst, g->line[g->idx]);
			g->idx--;
		}
	}
}

void	lex_helper3(t_lex *g, t_stack **lst)
{
	if (g->line[g->idx] == '<' && g->line[g->idx + 1] == '<')
	{
		add_push(lst, g->line[g->idx]);
		g->idx--;
	}
	else if (g->line[g->idx] == '>' && g->line[g->idx + 1] == '>')
	{
		add_push(lst, g->line[g->idx]);
		g->idx--;
	}
}

void	lex_helper0(t_lex *g, t_stack **lst)
{
	lex_helper1(g, lst);
	lex_helper2(g, lst);
	add_push(lst, g->line[g->idx]);
	g->idx--;
	if (g->idx >= 0)
		lex_helper3(g, lst);
}

int	lex(t_lex *g)
{
	t_stack	*lst;

	lst = NULL;
	if (quotes_check(g) == 0)
	{
		printf("quotes error \n");
		g_env.status = 255;
		return (1);
	}
	g->idx = ft_strlen(g->line) - 1;
	while (g->idx >= 0)
		lex_helper0(g, &lst);
	g->new_line_tmp = lst_to_str(lst);
	free_lst(lst);
	g->splited2 = ft_split_qk(g->new_line_tmp, ' ');
	free(g->new_line_tmp);
	if (g->splited2[0][0] == '\0')
		return (2);
	return (3);
}
