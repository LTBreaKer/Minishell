/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:25:21 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/21 18:52:53 by aharrass         ###   ########.fr       */
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
	
	if (!cmd->args)
		exit(0);
	if (!cmd->args[0])
		exit (0);
	if ((cmd->args[0][0] == '.' || cmd->args[0][0] == '/'))
	{
		if (access(cmd->args[0], F_OK) == 0)
			return (cmd->args[0]);
		else
		{	ft_putstr_fd("minishell: ", 2);
			perror (cmd->args[0]);
			exit (127);
		}
	}
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
	if (cmd->args)
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
					free(tmp->herepipe);
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

int	ft_execute(t_cmd *cmd, char **envp)
{
	int		**pipes;
	int		i;
	char	*cmd_path;
	int		s;
	DIR		*direc;
	t_cmd	*tmp;

	i = 0;
	s = 0;
	
	cmd->herepipe = NULL;
	tmp = cmd;
	g_env.cmd_count = count_cmd(cmd);
	pipes = make_pipes(g_env.cmd_count);
	if (!pipes && g_env.cmd_count > 1)
		return (1);
	g_env.pid = ft_calloc(sizeof(int) , g_env.cmd_count);
	if (!g_env.pid)
		return (perror("malloc"), 1);
	
	if (heredoc(cmd))
		return (1);
	while (tmp)
	{
		if (!tmp->args)
		{
			ft_putstr_fd("i = ", 2);
			ft_putnbr_fd(i, 2);
			ft_putstr_fd("\n", 2);
			ft_closep(tmp, pipes, i);
			i++;
			tmp = tmp->next;
			continue;
		}
		if (cmd->args && ft_strncmp(tmp->args[0], "exit", 4) == 0
					&& tmp->args[0][4] == '\0' && cmd->next == NULL)
		{
					ft_exit(tmp->args, 0);
					tmp = tmp->next;
		}
		else if (cmd->args && ft_strncmp(cmd->args[0], "cd", 2) == 0 && cmd->args[0][2] == '\0' && cmd->next == NULL)
		{
			ft_cd(cmd->args[1]);
			tmp = tmp->next;
		}
		else if (cmd->args && ft_strncmp(cmd->args[0], "export", 6) == 0 && cmd->args[0][6] == '\0' && cmd->next == NULL)
		{
			ft_export(cmd->args);
			tmp = tmp->next;
		}
		else if (cmd->args && ft_strncmp(cmd->args[0], "unset", 5) == 0 && cmd->args[0][5] == '\0' && cmd->next == NULL)
		{
			ft_unset(cmd->args);
			tmp = tmp->next;
		}
		else
		{
			s = 1;
			g_env.pid[i] = fork();
			if (g_env.pid[i] == -1)
				return (perror("fork"), 1);
			if (g_env.pid[i] == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				if (!tmp->args)
					exit(1);
				if (tmp->in == -1 || tmp->out == -1)
					exit(1);
				if (i == 0)
				{
					if (tmp->next)
						(dup2(pipes[i][1], 1), close(pipes[i][1]), close(pipes[i][0]));
					if (tmp->in != -2)
						(dup2(tmp->in, 0), close(tmp->in));
					if (tmp->out != -2)
						(dup2(tmp->out, 1), close(tmp->out));
				}
				else if (i == g_env.cmd_count - 1)
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
					close(pipes[i - 1][0]);
					if (tmp->next)
						(dup2(pipes[i][1], 1), close(pipes[i][1]), close(pipes[i][0]));
					if (tmp->in != -2)
						(dup2(tmp->in, 0), close(tmp->in));
					if (tmp->out != -2)
						(dup2(tmp->out, 1), close(tmp->out));
				}
				if (tmp->heredoc && tmp->wf == 1)
				{
					dup2(tmp->herepipe[0], 0);
					close(tmp->herepipe[0]);
					close(tmp->herepipe[1]);
				}
					
				//check command
				if ((direc = opendir(tmp->args[0])) != NULL)
				{
					closedir(direc);
					write(2, "minishell: ", 11);
					write(2, tmp->args[0], ft_strlen(tmp->args[0]));
					write(2, ": is a directory\n", 17);
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
						perror(tmp->args[0]), exit(126));
					exit(0);
				}
			}
			else
			{
				ft_closep(tmp, pipes, i);
				i++;
				tmp = tmp->next;
			}
		}
	}
	if (g_env.pid)
	{
		if (s)
		{
			int k;

			k = g_env.cmd_count - 1;
			waitpid(g_env.pid[k], &g_env.status, 0);
			close_pipes(pipes, g_env.cmd_count);
			i = 0;
			while (i < k)
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
	i = 0;
	// if (g_env.cmd_count > 1)
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
