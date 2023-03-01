/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:25:21 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/01 05:16:04 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_env(char **envp)
{
	int i;

	i = 0;
	
	if (*envp)
	{
		g_env.env = ft_lstnew(envp[i++]);
		while (envp[i])
		{
			if (envp[i + 1] == NULL)
			{
				ft_lstadd_back(&g_env.env, ft_lstnew("_=/usr/bin/env"));
				i++;
			}
			else
				ft_lstadd_back(&g_env.env, ft_lstnew(envp[i++]));
		}
	}
	else
	{
		g_env.env = ft_lstnew(ft_strjoin("PWD=", getcwd(NULL, 0)));
		ft_lstadd_back(&g_env.env, ft_lstnew("SHLVL=1"));
		ft_lstadd_back(&g_env.env, ft_lstnew("_=/usr/bin/env"));
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	
	g_env.export = NULL;
	make_env(envp);
	ft_export("S");
	ft_export(NULL);
	//ft_env();
	return (0);
}

// void	ft_execute(char **cmd, char **envp, int infile, int outfile)
// {
// 	t_var var;
// 	int i;

// 	i = 0;
// 	while (cmd[i])
// 		i++;
// 	var.fd = malloc(sizeof(int *) * (i - 1));
// 	if (!var.fd)
// 		return ;
	
// }