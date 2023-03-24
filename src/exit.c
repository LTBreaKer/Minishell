/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:05:14 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/24 20:02:21 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_helper(char **args, int check, int i)
{
	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_env.status = 1;
		if (check == 1)
			(exit(g_env.status));
		return (1);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_env.status = 1;
		if (check == 1)
			(ft_putendl_fd("exit", 1), exit(g_env.status));
		return (1);
	}
	i = ft_atoi(args[1], 1);
	if (i == -1)
	{
		g_env.status = 255;
		(exit(g_env.status));
	}
	g_env.status = i;
	(ft_putendl_fd("exit", 1), exit(g_env.status));
}

void	ft_exit(char **args, int check)
{
	int	i;

	i = 0;
	if (args && args[1])
	{
		while (args[1][i])
		{
			if (args[1][i] == '-' && i == 0)
				i++;
			if (!ft_isdigit(args[1][i]))
			{
				ft_putendl_fd("exit", 1);
				ft_putendl_fd("minishell: exit: numeric argument required", 2);
				g_env.status = 255;
				exit(g_env.status);
			}
			i++;
		}
		if (exit_helper(args, check, i) == 1)
			return ;
	}
	ft_putendl_fd("exit", 1);
	exit(g_env.status);
}
