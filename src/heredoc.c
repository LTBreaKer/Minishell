/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:24:37 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/22 20:34:48 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

void	make_heredoc(t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->herepipe = NULL;
	if (arr_size(cmd->heredoc))
	{
		cmd->herepipe = malloc(sizeof(int) * 2);
		if (!cmd->herepipe)
			return (perror("malloc"));
		if (pipe(cmd->herepipe) == -1)
			return (perror("pipe"));
	}
	else
		cmd->herepipe = NULL;
	return ;
}

int	heredoc(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;
	struct termios	term;
	struct termios	term2;

	i = 0;
	tmp = cmd;
	g_env.line = NULL;
	tcgetattr(0, &term);
	term2 = term;
	term.c_lflag &= ~ISIG;
	term.c_lflag &= ~ECHOCTL;
	while (tmp)
	{
		make_heredoc(tmp);
		if (tmp->heredoc)
		{
			g_env.h_id = fork();
			if (g_env.h_id == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, sigquit_handler);
				while (tmp->heredoc[i])
				{
					//ft_putstr_fd("> ", 2);
					tcsetattr(0, TCSANOW, &term);
					g_env.line = readline("> ");
					if (g_env.line)
						g_env.line = ft_strjoin3(g_env.line, "\n");
					while (g_env.line && (ft_strncmp(g_env.line, tmp->heredoc[i], ft_strlen(tmp->heredoc[i])) || g_env.line[ft_strlen(tmp->heredoc[i])] != '\n'))
					{
						if (!tmp->heredoc[i + 1])
						{
							g_env.line = here_expand(g_env.line);
							ft_putstr_fd(g_env.line, tmp->herepipe[1]);
						}
						free(g_env.line);
						//ft_putstr_fd("> ", 2);
						g_env.line = readline("> ");
						if (g_env.line)
							g_env.line = ft_strjoin3(g_env.line, "\n");
					}
					i++;
				}
				(close(tmp->herepipe[1]), close(tmp->herepipe[0]));
				exit(0);
			}
			else
			{
				tcsetattr(0, TCSANOW, &term2);
				if (g_env.line)
					free(g_env.line);
				waitpid(g_env.h_id, &i, 0);
				if (WIFSIGNALED(i))
				{
					g_env.status = 1;
					return (1);
				}
				else
					return(0);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
