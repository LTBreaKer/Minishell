/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:17:54 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/23 21:12:06 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int sig)
{
	int	i;

	(void)sig;
	i = 0;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	if (g_env.h_id)
	{
		kill(g_env.h_id, SIGINT);
	}
	if (g_env.pid)
	{
		while (g_env.pid[i])
		{
			kill(g_env.pid[i], SIGINT);
			i++;
		}
	}
	g_env.status = 1;
}

void	sigquit_handler(int sig)
{
	int	i;

	(void)sig;
	i = 0;
	if (g_env.h_id)
		rl_on_new_line();
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (g_env.pid)
	{
		while (g_env.pid[i])
		{
			kill(g_env.pid[i], SIGQUIT);
			i++;
		}
	}
}
