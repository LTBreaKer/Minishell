/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utlis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:06:35 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/27 18:13:25 by aharrass         ###   ########.fr       */
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

void	close_pipes2(int **pipes, int cmd_count)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
}

void	close_pipes(int **pipes, int cmd_count)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

char	*get_cmd2(char **paths, t_cmd *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
			cmd_path = ft_strjoin2(paths[i++], "/");
		else
			cmd_path = ft_strdup(paths[i++]);
		cmd_path = ft_strjoin2(cmd_path, cmd->args[0]);
		if (access(cmd_path, F_OK) == 0)
			break ;
		free(cmd_path);
	}
	free_split(paths);
	if (access(cmd_path, F_OK) == 0)
		return (cmd_path);
	return (NULL);
}

char	*get_cmd(t_cmd *cmd)
{
	char	*tmp;
	char	**paths;

	if (!cmd->args)
		exit(0);
	if (!cmd->args[0])
		exit(0);
	if (!cmd->args[0][0])
		return (NULL);
	if ((cmd->args[0][0] == '.' || cmd->args[0][0] == '/'))
	{
		if (access(cmd->args[0], F_OK) == 0)
			return (cmd->args[0]);
		else
			(ft_putstr_fd("minishell: ", 2), perror(cmd->args[0]),
				exit(127));
	}
	tmp = ft_get_value("PATH");
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp, ':');
	if (!paths)
		return (NULL);
	return (get_cmd2(paths, cmd));
}
