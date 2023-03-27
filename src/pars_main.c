/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:54:13 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/27 14:23:51 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	doconly(t_lex *g, t_cmd **lst)
{
	t_cmd	*new;
	char	*tmp;
	int		i;

	i = 0;
	g->full_heredoc = NULL;
	if (i < g->idx_stx)
	{
		g->full_heredoc = ft_strdup("");
		new = ft_lstfinalnew();
	}
	while (i < g->idx_stx)
	{
		if (!ft_strcmp(g->splited2[i], "<<"))
		{
			i++;
			tmp = g->splited2[i];
			g->splited2[i] = clean_quotes2(g->splited2[i]);
			free(tmp);
			g->full_heredoc = ft_strjoin3(g->full_heredoc, g->splited2[i]);
			g->full_heredoc = ft_strjoin3(g->full_heredoc, " ");
		}
		i++;
	}
	clone_top(g, new, lst);
}

void	syntax_manager(t_lex *g, t_cmd **lst_final)
{
	g->lx = lex(g);
	if (g->lx == 3)
	{
		g->err = syntax_check(g);
		if (g->err != NULL)
		{
			printf("minishell: syntax error near unexpected token `%s\'\n",
				g->err);
			g_env.status = 258;
			(doconly(g, lst_final), free_split(g->splited2));
		}
		else
			(expand_me(g), fill_the_list(g, lst_final), free(g->deleted),
				free_split(g->splited2));
	}
	else if (g->lx == 2)
		free(g->splited2);
}

void	ft_get_line(t_lex *g, t_cmd **lst_final)
{
	struct termios	term;
	struct termios	term2;

	tcgetattr(0, &term);
	term2 = term;
	term.c_lflag &= ~ISIG;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	g->line = readline("\033[32;1mminishell-$ \033[0m");
	(add_history(g->line), tcsetattr(0, TCSANOW, &term2));
	if (g->line == NULL)
		ft_exit(NULL, 0);
	syntax_manager(g, lst_final);
}

void	free_all(t_cmd **lst_final)
{
	t_cmd	*tmp;

	while (*lst_final)
	{
		if ((*lst_final)->herepipe)
			free((*lst_final)->herepipe);
		if ((*lst_final)->args)
			free_split((*lst_final)->args);
		if ((*lst_final)->heredoc)
			free_split((*lst_final)->heredoc);
		tmp = (*lst_final);
		(*lst_final) = (*lst_final)->next;
		free(tmp);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_lex	g;
	t_cmd	*lst_final;
	t_cmd	*tmp;

	(void)ac;
	(void)av;
	(signal(SIGINT, sigint_handler), signal(SIGQUIT, sigquit_handler));
	lst_final = NULL;
	g.tmp = NULL;
	g_env.export = NULL;
	make_env(envp);
	while (1)
	{
		ft_get_line(&g, &lst_final);
		tmp = lst_final;
		while (tmp)
		{
			clean_me(&g, tmp->args),
			tmp = tmp->next;
		}
		if (lst_final)
			ft_execute(lst_final, envp);
		(free_all(&lst_final), free(g.line));
	}
}
