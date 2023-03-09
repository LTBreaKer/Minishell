/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:25:21 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/09 15:48:35 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_env(char **envp)
{
	int	i;

	i = 0;
	if (*envp)
	{
		g_env.env = ft_lstnew(envp[i++], 0);
		while (envp[i])
		{
			if (envp[i + 1] == NULL)
			{
				ft_lstadd_back(&g_env.env, ft_lstnew("_=/usr/bin/env", 0));
				i++;
			}
			else if (ft_strncmp(envp[i], "OLDPWD", 6) == 0)
				i++;
			else
				ft_lstadd_back(&g_env.env, ft_lstnew(envp[i++], 0));
		}
	}
	else
	{
		g_env.env = ft_lstnew(ft_strjoin("PWD=", getcwd(NULL, 0)), 1);
		ft_lstadd_back(&g_env.env, ft_lstnew("SHLVL=1", 0));
		ft_lstadd_back(&g_env.env, ft_lstnew("_=/usr/bin/env", 0));
	}
}

int	**make_pipes(int cmd_count)
{
	int	**pipes;
	int	i;

	i = 0;
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

char	*get_cmd(t_cmd *cmd)
{
	char	*cmd_path;
	char	*tmp;
	char	**paths;
	int		i;

	i = 0;
	if (access(cmd->cmd, F_OK) == 0)
		return (cmd->cmd);
	tmp = ft_get_value("PATH");
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i++], "/");
		cmd_path = ft_strjoin(cmd_path, cmd->cmd);
		if (access(cmd_path, F_OK) == 0)
			break ;
		free(cmd_path);
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	if (access(cmd_path, F_OK) == 0)
		return (cmd_path);
	return (NULL);
}

void	built_in(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0 && cmd->args[0][4] == '\0')
		ft_echo(cmd);
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0 && cmd->args[0][2] == '\0')
		ft_cd(cmd->args[1]);
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0 && cmd->args[0][3] == '\0')
		ft_pwd();
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0
			&& cmd->args[0][6] == '\0')
		ft_export(cmd->args);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0
			&& cmd->args[0][5] == '\0')
		ft_unset(cmd->args);
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0 && cmd->args[0][3] == '\0')
		ft_env();
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0
			&& cmd->args[0][4] == '\0')
		ft_exit(cmd->args);
}

int	ft_execute(t_cmd *cmd, char **envp)
{
	int		cmd_count;
	int		**pipes;
	int		*pid;
	int		i;
	char	*cmd_path;

	i = 0;
	cmd_count = count_cmd(cmd);
	pipes = make_pipes(cmd_count);
	if (!pipes)
		return (1);
	pid = malloc(sizeof(int) * cmd_count);
	if (!pid)
		return (perror("malloc"), 1);
	while (cmd)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (perror("fork"), 1);
		if (pid[i] == 0)
		{
			if (cmd->in == -1 || cmd->out == -1 || cmd->err == -1)
				exit(1);
			if (cmd->err != -2)
				(dup2(cmd->err, 2), close(cmd->err));
			if (i == 0)
			{
				close(pipes[i][0]);
				if (cmd->next)
					(dup2(pipes[i][1], 1), close(pipes[i][1]));
				if (cmd->in != -2)
					(dup2(cmd->in, 0), close(cmd->in));
				if (cmd->out != -2)
					(dup2(cmd->out, 1), close(cmd->out));
			}
			else if (i == cmd_count - 1)
			{
				close(pipes[i - 1][1]);
				dup2(pipes[i - 1][0], 0);
				close(pipes[i - 1][0]);
				dup2(pipes[i][1], 1);
				close(pipes[i][1]);
				close(pipes[i][0]);
				if (cmd->out != -2)
					(dup2(cmd->out, 1), close(cmd->out));
				if (cmd->in != -2)
					(dup2(cmd->in, 0), close(cmd->in));
			}
			else if (i != 0)
			{
				close(pipes[i - 1][1]);
				dup2(pipes[i - 1][0], 0);
				close(pipes[i][0]);
				if (cmd->next)
					(dup2(pipes[i][1], 1), close(pipes[i][1]));
				if (cmd->in != -2)
					(dup2(cmd->in, 0), close(cmd->in));
				if (cmd->out != -2)
					(dup2(cmd->out, 1), close(cmd->out));
				close(pipes[i - 1][0]);
			}
			//check command
			built_in(cmd);
			cmd_path = get_cmd(cmd);
			if (!cmd_path)
				(ft_error(cmd->cmd), exit(1));
			execve(cmd->cmd, cmd->args, envp);
			write(2, "minishell: ", 11);
			(perror(cmd->cmd), exit(126)); 
		}
		else
		{
			if (i == 0)
				close(pipes[i][0]);
			else if (i != cmd_count - 1)
				close(pipes[i][1]);
			else if (i != 0)
				close(pipes[i - 1][0]);
			i++;
			cmd = cmd->next;
		}
	}
	waitpid(pid[i - 1], &g_env.status, 0);
	if (WIFEXITED(g_env.status))
		g_env.status = WEXITSTATUS(g_env.status);
	else
		g_env.status = 1;
	free(pid);
	i = 0;
	while (pipes[i])
		free(pipes[i++]);
	free(pipes);
	return (g_env.status);
}

// int	main(int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	(void)av;
// 	g_env.export = NULL;
// 	make_env(envp);
// 	printf("----------------\n");
// 	return (0);
// }
