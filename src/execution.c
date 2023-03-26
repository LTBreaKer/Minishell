/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:25:21 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/26 02:13:09 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_now(t_cmd *tmp, char **envp)
{
	DIR		*direc;
	char	*cmd_path;

	direc = opendir(tmp->args[0]);
	if (direc != NULL)
	{
		closedir(direc);
		print_err("minishell: ", tmp->args[0], ": is a directory\n");
		exit(126);
	}
	if (!built_in(tmp))
		exit(0);
	else
	{
		cmd_path = get_cmd(tmp);
		if (!cmd_path)
			(ft_error(tmp->args[0]), exit(127));
		if (execve(cmd_path, tmp->args, envp) == -1)
			(write(2, "minishell: ", 11),
				perror(tmp->args[0]),
				exit(126));
		exit(0);
	}
}

void	child_handler(int i, t_cmd *tmp, int **pipes, char **envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!tmp->args)
		exit(1);
	if (tmp->in == -1 || tmp->out == -1)
		exit(1);
	dup_handler(i, pipes, tmp);
	exec_now(tmp, envp);
}

int	fork_handler(t_cmd *tmp, int **pipes, t_cmd *cmd, char **envp)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	while (tmp)
	{
		if (check_null_cmd(&tmp, &i, pipes))
			continue ;
		if (built_in_parent(cmd))
			tmp = tmp->next;
		else
		{
			s = 1;
			g_env.pid[i] = fork();
			if (g_env.pid[i] == -1)
				return (perror("fork"), 0);
			if (g_env.pid[i] == 0)
				(child_handler(i, tmp, pipes, envp));
			ft_closep(tmp, pipes, i++);
			tmp = tmp->next;
		}
	}
	return (s);
}

void	wait_handler(int s, int **pipes)
{
	int	i;

	if (g_env.pid)
	{
		if (s)
		{
			waitpid(g_env.pid[g_env.cmd_count - 1], &g_env.status, 0);
			i = 0;
			while (i < g_env.cmd_count - 1)
				waitpid(g_env.pid[i++], NULL, 0);
			if (WIFSIGNALED(g_env.status))
				g_env.status = WTERMSIG(g_env.status) + 128;
			else if (WIFEXITED(g_env.status))
				g_env.status = WEXITSTATUS(g_env.status);
			else
				g_env.status = 1;
		}
	}
	if (g_env.pid)
		free(g_env.pid);
	if (pipes)
		close_pipes(pipes, g_env.cmd_count);
}

int	ft_execute(t_cmd *cmd, char **envp)
{
	int		**pipes;
	int		i;
	int		s;
	t_cmd	*tmp;

	i = 0;
	cmd->herepipe = NULL;
	tmp = cmd;
	g_env.cmd_count = count_cmd(cmd);
	pipes = make_pipes(g_env.cmd_count);
	if (!pipes && g_env.cmd_count > 1)
		return (1);
	g_env.pid = ft_calloc(sizeof(int), g_env.cmd_count);
	if (!g_env.pid)
		return (perror("malloc"), 1);
	if (heredoc(cmd))
	{
		if (pipes)
			close_pipes(pipes, g_env.cmd_count);
		return (free(g_env.pid), 1);
	}
	s = fork_handler(tmp, pipes, cmd, envp);
	wait_handler(s, pipes);
	return (0);
}
