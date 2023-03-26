/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:09:26 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/26 17:29:50 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	**make_pipes(int cmd_count)
{
	int	**pipes;
	int	i;

	i = 0;
	if (cmd_count == 0 || cmd_count == 1)
		return (NULL);
	pipes = malloc(sizeof(int *) * cmd_count - 1);
	if (!pipes)
		return (perror("malloc"), NULL);
	while (i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (perror("malloc"), NULL);
		if (pipe(pipes[i]) == -1)
			return (perror("pipe"), NULL);
		i++;
	}
	return (pipes);
}

int	built_in(t_cmd *cmd)
{
	if (cmd->args)
	{
		if (ft_strncmp(cmd->args[0], "echo", 4) == 0 && cmd->args[0][4] == '\0')
			return (ft_echo(cmd), 0);
		else if (ft_strncmp(cmd->args[0], "cd", 2) == 0
			&& cmd->args[0][2] == '\0')
			return (ft_cd(cmd->args[1], 1), 0);
		else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0
			&& cmd->args[0][3] == '\0')
			return (ft_pwd(), 0);
		else if (ft_strncmp(cmd->args[0], "export", 6) == 0
			&& cmd->args[0][6] == '\0')
			return (ft_export(cmd->args, 1), 0);
		else if (ft_strncmp(cmd->args[0], "unset", 5) == 0
			&& cmd->args[0][5] == '\0')
			return (ft_unset(cmd->args, 1), 0);
		else if (ft_strncmp(cmd->args[0], "env", 3) == 0
			&& cmd->args[0][3] == '\0')
			return (ft_env(), 0);
		else if (ft_strncmp(cmd->args[0], "exit", 4) == 0
			&& cmd->args[0][4] == '\0')
			return (ft_exit(cmd->args, 1), 1);
	}
	return (1);
}

void	ft_closep(t_cmd *tmp, int **pipes, int i)
{
	close(tmp->in);
	close(tmp->out);
	if (tmp->herepipe)
	{
		close(tmp->herepipe[0]);
		close(tmp->herepipe[1]);
	}
	if (i == 0)
	{
		if (pipes)
			close(pipes[i][1]);
	}
	else if (i == g_env.cmd_count - 1)
	{
		close(tmp->in);
		close(pipes[i - 1][0]);
		close(pipes[i - 1][1]);
	}
	else if (i != 0)
	{
		close(pipes[i][1]);
		close(pipes[i - 1][0]);
		close(pipes[i - 1][1]);
	}
}

int	check_null_cmd(t_cmd **tmp, int *i, int **pipes)
{
	if (((*tmp)->in == -1 || (*tmp)->out == -1))
	{
		(*i)++;
		(*tmp) = (*tmp)->next;
		g_env.status = 1;
		return (1);
	}
	if (!(*tmp)->args)
	{
		ft_closep(*tmp, pipes, *i);
		(*i)++;
		(*tmp) = (*tmp)->next;
		return (1);
	}
	return (0);
}

int	built_in_parent(t_cmd *cmd)
{
	if (cmd->args && ft_strncmp(cmd->args[0], "exit", 4) == 0
		&& cmd->args[0][4] == '\0' && cmd->next == NULL)
		return (ft_exit(cmd->args, 0), 1);
	else if (cmd->args && ft_strncmp(cmd->args[0], "cd", 2) == 0
		&& cmd->args[0][2] == '\0' && cmd->next == NULL)
		return (ft_cd(cmd->args[1], 0), 1);
	else if (cmd->args && ft_strncmp(cmd->args[0], "export", 6) == 0
		&& cmd->args[0][6] == '\0' && cmd->next == NULL)
		return (ft_export(cmd->args, 0), 1);
	else if (cmd->args && ft_strncmp(cmd->args[0], "unset", 5) == 0
		&& cmd->args[0][5] == '\0' && cmd->next == NULL)
		return (ft_unset(cmd->args, 0), 1);
	return (0);
}
