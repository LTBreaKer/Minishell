/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:54:13 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/09 16:22:11 by aharrass         ###   ########.fr       */
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
int	i = 0;
	lst_final = NULL;
	g_env.export = NULL;
	make_env(envp);
	while ((g.line = readline("-> ")) != NULL)
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
				while (lst_final)
				{
					i = 0;
					printf("{in : %d}\n", lst_final->in);
					printf("{out : %d}\n", lst_final->out);
					if (lst_final->args)
					{
						while (lst_final->args[i])
						{
							printf("{cmd : %s}\n", lst_final->args[i]);
							i++;
						}
					}
					i = 0;
					if (!lst_final->heredoc)
								printf("{her doc : %s}\n}", (char *)lst_final->heredoc);
					if (lst_final->heredoc)
					{
						while (lst_final->heredoc[i])
						{
							
							printf("{here doc %d : %s}\n", i, (char *)lst_final->heredoc[i]);
							i++;
						}
					}
					printf("------------------------------\n");
					lst_final = lst_final->next;
				}
				freee_sub_split(g.splited2);
				freee_sub_split(g.splited1);
			}
			add_history(g.line);
		}
		else if (lx == 2)
			free(g.splited1);
		ft_export(NULL);
		free(g.line);
	}
	return (0);
}
