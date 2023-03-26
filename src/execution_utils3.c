/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:12:50 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/26 02:13:06 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_handler(int i, int **pipes, t_cmd *tmp)
{
	if (i == 0)
	{
		if (tmp->next)
			(dup2(pipes[i][1], 1));
	}
	else if (i == g_env.cmd_count - 1)
		dup2(pipes[i - 1][0], 0);
	else if (i != 0)
	{
		dup2(pipes[i - 1][0], 0);
		dup2(pipes[i][1], 1);
	}
	if (tmp->in != -2)
		dup2(tmp->in, 0);
	if (tmp->out != -2)
		dup2(tmp->out, 1);
	if (tmp->heredoc && tmp->wf == 1)
		(dup2(tmp->herepipe[0], 0), close(tmp->herepipe[0]),
			close(tmp->herepipe[1]));
	(close(tmp->in), close(tmp->out));
	close_pipes2(pipes, g_env.cmd_count);
}
