/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:25:21 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/12 13:34:51 by aharrass         ###   ########.fr       */
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
	//close(pipes[0][0]);
	return (pipes);
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

char	*get_cmd(t_cmd *cmd)
{
	char	*cmd_path;
	char	*tmp;
	char	**paths;
	int		i;

	i = 0;
	if (access(cmd->args[0], F_OK) == 0)
		return (cmd->args[0]);
	
	tmp = ft_get_value("PATH");
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		cmd_path = ft_strjoin2(paths[i++], "/");
		cmd_path = ft_strjoin2(cmd_path, cmd->args[0]);
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

int	built_in(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0 && cmd->args[0][4] == '\0')
		return (ft_echo(cmd), 0);
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0 && cmd->args[0][2] == '\0')
		return (ft_cd(cmd->args[1]), 0);
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0 && cmd->args[0][3] == '\0')
		return (ft_pwd(), 0);
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0
			&& cmd->args[0][6] == '\0')
		return (ft_export(cmd->args), 0);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0
			&& cmd->args[0][5] == '\0')
		return (ft_unset(cmd->args), 0);
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0 && cmd->args[0][3] == '\0')
		return (ft_env(), 0);
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0
			&& cmd->args[0][4] == '\0')
		return(ft_exit(cmd->args, 0), 1);
	return (1);
}

int	ft_execute(t_cmd *cmd, char **envp)
{
	int		cmd_count;
	int		**pipes;
	int		*pid;
	int		i;
	char	*cmd_path;
	int		s;
	t_cmd	*tmp;

	i = 0;
	s = 0;
	tmp = cmd;
	cmd_count = count_cmd(cmd);
	pipes = make_pipes(cmd_count);
	pid = ft_calloc(sizeof(int) , cmd_count);
	if (!pid)
		return (perror("malloc"), 1);
	while (tmp)
	{
		if (ft_strncmp(tmp->args[0], "exit", 4) == 0
					&& tmp->args[0][4] == '\0' && tmp->next == NULL)
		{
					ft_exit(tmp->args, 0);
					tmp = tmp->next;
		}
		else if (ft_strncmp(cmd->args[0], "cd", 2) == 0 && cmd->args[0][2] == '\0')
		{
			ft_cd(cmd->args[1]);
			tmp = tmp->next;
		}
		else if (ft_strncmp(cmd->args[0], "export", 6) == 0 && cmd->args[0][6] == '\0')
		{
			ft_export(cmd->args);
			tmp = tmp->next;
		}
		else
		{
			s = 1;
			pid[i] = fork();
			if (pid[i] == -1)
				return (perror("fork"), 1);
			if (pid[i] == 0)
			{
				if (tmp->in == -1 || tmp->out == -1 || tmp->err == -1)
					exit(1);
				if (tmp->err != -2)
					(dup2(tmp->err, 2), close(tmp->err));
				if (i == 0)
				{
					if (tmp->next)
						(dup2(pipes[i][1], 1), close(pipes[i][1]));
					if (tmp->in != -2)
						(dup2(tmp->in, 0), close(tmp->in));
					if (tmp->out != -2)
						(dup2(tmp->out, 1), close(tmp->out));
				}
				else if (i == cmd_count - 1)
				{
					close(pipes[i - 1][1]);
					dup2(pipes[i - 1][0], 0);
					close(pipes[i - 1][0]);
					if (tmp->out != -2)
						(dup2(tmp->out, 1), close(tmp->out));
					if (tmp->in != -2)
						(dup2(tmp->in, 0), close(tmp->in));
				}
				else if (i != 0)
				{
					close(pipes[i - 1][1]);
					dup2(pipes[i - 1][0], 0);
					close(pipes[i][0]);
					if (tmp->next)
						(dup2(pipes[i][1], 1), close(pipes[i][1]));
					if (tmp->in != -2)
						(dup2(tmp->in, 0), close(tmp->in));
					if (tmp->out != -2)
						(dup2(tmp->out, 1), close(tmp->out));
					close(pipes[i - 1][0]);
				}
				//check command
				if (!built_in(tmp))
					exit(0);
				else
				{
					cmd_path = get_cmd(tmp);
					if (!cmd_path)
						(ft_error(tmp->args[0]), exit(127));
					execve(cmd_path, tmp->args, envp);
					write(2, "minishell: ", 11);
					(perror(tmp->args[0]), exit(126));
				}
			}
			else
			{
				int t = tmp->in;
				close(tmp->in);
				close(tmp->out);
				if (i == 0)
				{
					if (pipes)
					{
						//close(pipes[i][0]);
						close(pipes[i][1]);
					}
				}
				else if (i == cmd_count - 1)
				{
					//close(tmp->in);
					close(t);
					close(pipes[i - 1][0]);
					close(pipes[i - 1][1]);
				}
				else if (i != 0)
				{
					close(pipes[i][1]);
					close(pipes[i - 1][0]);
					close(pipes[i - 1][1]);
				}
				i++;
				tmp = tmp->next;
			}
		}
	}
	if (pid)
	{
		if (s)
		{
			int k;

			k = i - 1;
			//i = 0;
			// while (i < k)
			// 	waitpid(pid[i++], NULL, 0);
			waitpid(pid[k], &g_env.status, 0);
			close_pipes(pipes, cmd_count);
			if (WIFEXITED(g_env.status))
				g_env.status = WEXITSTATUS(g_env.status);
			else
				g_env.status = 1;
		}
	}
	if (pid)
		free(pid);
	i = 0;
	// if (cmd_count > 1)
	// 	while (pipes[i])
	// 		free(pipes[i++]);
	//free(pipes);
	return (0);
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
