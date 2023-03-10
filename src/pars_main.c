/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:54:13 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/10 19:51:27 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	t_cmd	*lst_final;
	char	*err;
	int		lx;
	t_cmd	*tmp;
	
	lst_final = NULL;
	g_env.export = NULL;
	make_env(envp);
	while ((g.line = readline("minishell-$ ")) != NULL)
	{
		lx = lex(&g);
		if (lx == 3)
		{
			if ((err = syntax_check(&g)) != NULL)
			{
				printf("minishell: syntax error near unexpected token `%s\'\n", err);
				freee_sub_split(g.splited2);
				freee_sub_split(g.splited1);
				g_env.status = 258;
			}
			else
			{
				fill_the_list(&g, &lst_final);
				tmp = lst_final;
				while (tmp)
				{
					int i = 0;
					printf("{in : %d}\n", tmp->in);
					printf("{out : %d}\n", tmp->out);
					if (tmp->args)
					{
						while (tmp->args[i])
						{
							printf("{arg%d : %s}\n", i, tmp->args[i]);
							i++;
						}
					}
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
				freee_sub_split(g.splited1);
			}
			add_history(g.line);
		}
		else if (lx == 2)
			free(g.splited1);
		ft_execute(lst_final, envp);
		
		while (lst_final)
		{
			int		j;
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
