/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:54:13 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/24 01:13:53 by aharrass         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	t_lex			g;
	struct termios	term;
	struct termios	term2;
	t_cmd			*lst_final;
	t_cmd			*tmp;

	(void)ac;
	(void)av;
	(signal(SIGINT, sigint_handler), signal(SIGQUIT, sigquit_handler));
	lst_final = NULL;
	tcgetattr(0, &term);
	term2 = term;
	term.c_lflag &= ~ISIG;
	term.c_lflag &= ~ECHOCTL;
	g.tmp = NULL;
	g_env.export = NULL;
	make_env(envp);
	while (1)
	{
		tcsetattr(0, TCSANOW, &term);
		g.line = readline("\033[32;1mminishell-$ \033[0m");
		add_history(g.line);
		tcsetattr(0, TCSANOW, &term2);
		if (g.line == NULL)
			ft_exit(NULL, 0);
		g.lx = lex(&g);
		if (g.lx == 3)
		{
			if ((g.err = syntax_check(&g)) != NULL)
			{
				printf("minishell: syntax error near unexpected token `%s\'\n",
						g.err);
				g_env.status = 258;
				doconly(&g, &lst_final);
				free_split(g.splited2);
			}
			else
			{
				expand_me(&g);
				fill_the_list(&g, &lst_final);
				free(g.deleted);
				// tmp = lst_final;
				// while (tmp)
				// {
				// 	int i = 0;
				// 	printf("{in : %d}\n", tmp->in);
				// 	printf("{out : %d}\n", tmp->out);
				// 	printf("{wf : %d}\n", tmp->wf);
				// 	if (tmp->args)
				// 	{
				// 		while (tmp->args[i])
				// 		{
				// 			printf("{arg%d : %s}\n", i, tmp->args[i]);
				// 			i++;
				// 		}
				// 	}
				// 	else
				// 		printf("{arg : NULL}\n");
				// 	i = 0;
				// 	if (!tmp->heredoc)
				// 				printf("{her doc : %s}\n}",
										// (char *)tmp->heredoc);
				// 	if (tmp->heredoc)
				// 	{
				// 		while (tmp->heredoc[i])
				// 		{
				// 			printf("{here doc %d : %s}\n", i,
									// (char *)tmp->heredoc[i]);
				// 			i++;
				// 		}
				// 	}
				// 	printf("------------------------------\n");
				// 	tmp = tmp->next;
				// }
				free_split(g.splited2);
			}
			
		}
		else if (g.lx == 2)
			free(g.splited2);
		tmp = lst_final;
		while (tmp)
		{
			if (tmp)
				clean_me(&g, tmp->args),
					tmp = tmp->next;
		}
		if (lst_final)
			ft_execute(lst_final, envp);
		while (lst_final)
		{
			if (lst_final->herepipe)
				free(lst_final->herepipe);
			if (lst_final->args)
				free_split(lst_final->args);
			if (lst_final->heredoc)
				free_split(lst_final->heredoc);
			tmp = lst_final,
			lst_final = lst_final->next,
			free(tmp);
		}
		free(g.line);
	}
	return (0);
}
