/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:24:37 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/17 22:27:24 by aharrass         ###   ########.fr       */
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

void	heredoc(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;
	char	*line;
	int		len;
	int h = 0;

	i = 0;
	tmp = cmd;
	len = 0;
	while (tmp)
	{
		make_heredoc(tmp);
		if (tmp->heredoc)
		{
			g_env.h_id = fork();
			if (g_env.h_id == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				while (tmp->heredoc[i])
				{
					len = ft_strlen(tmp->heredoc[i]);
					ft_putstr_fd("> ", 2);
					line = get_next_line(0);
					while (line && (ft_strncmp(line, tmp->heredoc[i], ft_strlen(tmp->heredoc[i])) || line[len] != '\n'))
					{
						h = 0;
						if (!tmp->heredoc[i + 1])
						{
							while (line[h])
							{
								write(tmp->herepipe[1], &line[h], 1);
								h++;
							}
						}
						free(line);
						ft_putstr_fd("> ", 2);
						line = get_next_line(0);
					}
					i++;
				}
				close(tmp->herepipe[1]);
				exit(0);
			}
			else
			{
				//(close(tmp->herepipe[1]), close(tmp->herepipe[0]));
				waitpid(g_env.h_id, NULL, 0);
			}
		}
		tmp = tmp->next;
	}
}
