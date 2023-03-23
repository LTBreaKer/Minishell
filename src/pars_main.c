/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:54:13 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/23 00:39:38 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	doconly(t_lex *g, t_cmd **lst)
{
	t_cmd	*new;
	char	*tmp;
	int	i;

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

void	freee_sub_split(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		i++;
	}
	free(splited);
}

int	main(int ac, char **av, char **envp)
{
	// (void)ac;int ac, char **av, char **env
	// (void)av;
	// make_env(env);
	// printf("%s\n", ft_get_value("USER"));
	(void)ac;
	(void)av;
	t_lex	g;
	struct termios	term;
	struct termios	term2;
	t_cmd	*lst_final;
	char	*err;
	int		lx;
	t_cmd	*tmp;
	
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
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
		tcsetattr(0, TCSANOW, &term2);
		if (g.line == NULL)
			ft_exit(NULL, 0);
		lx = lex(&g);
		if (lx == 3)
		{
			if ((err = syntax_check(&g)) != NULL)
			{
				printf("minishell: syntax error near unexpected token `%s\'\n", err);
				g_env.status = 258;
				doconly(&g, &lst_final);
				freee_sub_split(g.splited2);
				//freee_sub_split(g.splited1);
			}
			else
			{
				expand_me(&g);
				fill_the_list(&g, &lst_final);
				free(g.deleted);
				tmp = lst_final;
				while (tmp)
				{
					int i = 0;
					printf("{in : %d}\n", tmp->in);
					printf("{out : %d}\n", tmp->out);
					printf("{wf : %d}\n", tmp->wf);
					if (tmp->args)
					{
						while (tmp->args[i])
						{
							printf("{arg%d : %s}\n", i, tmp->args[i]);
							i++;
						}
					}
					else
						printf("{arg : NULL}\n");
					i = 0;
					if (!tmp->heredoc)
								printf("{her doc : %s}\n}", (char *)tmp->heredoc);
					if (tmp->heredoc)
					{
						while (tmp->heredoc[i])
						{
							
							printf("{here doc %d : %s}\n", i, (char *)tmp->heredoc[i]);
							i++;
						}
					}
					printf("------------------------------\n");
					tmp = tmp->next;
				}
				freee_sub_split(g.splited2);
				//freee_sub_split(g.splited1);
			}
			add_history(g.line);
			
		}
		else if (lx == 2)
			free(g.splited2);
		if (lst_final)
			(clean_me(&g, lst_final->args),
			ft_execute(lst_final, envp));
		while (lst_final)
		{
			
			int		j;
			if (lst_final->herepipe)
				free(lst_final->herepipe);
			if (lst_final->args)
			{
				j = 0;
				while (lst_final->args[j])
					free(lst_final->args[j++]);
				free(lst_final->args);
			 }
			if (lst_final->heredoc)
			{
				j = 0;
				while (lst_final->heredoc[j])
					free(lst_final->heredoc[j++]);
				free(lst_final->heredoc);
			}
			tmp = lst_final;
			lst_final = lst_final->next;
			free(tmp);
		}
		free(g.line);
	}
	
	return (0);
}
