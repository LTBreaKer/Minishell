/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:24:37 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/24 02:01:53 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_heredoc(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	tmp = cmd;
	i = 0;
	while (tmp)
	{
		tmp->herepipe = NULL;
		if (arr_size(tmp->heredoc))
		{
			tmp->herepipe = malloc(sizeof(int) * 2);
			if (!tmp->herepipe)
				return (perror("malloc"));
			if (pipe(tmp->herepipe) == -1)
				return (perror("pipe"));
		}
		tmp = tmp->next;
	}
	return ;
}

void	herdoc_child_loop(t_cmd *tmp, int i)
{
	if (!tmp->heredoc[i + 1])
	{
		g_env.line = here_expand(g_env.line);
		ft_putstr_fd(g_env.line, tmp->herepipe[1]);
	}
	free(g_env.line);
	g_env.line = readline("> ");
	if (g_env.line)
		g_env.line = ft_strjoin3(g_env.line, "\n");
}

void	heredoc_child(struct termios term, t_cmd *tmp)
{
	int	i;

	i = 0;
	(signal(SIGINT, SIG_DFL), signal(SIGQUIT, sigquit_handler));
	while (tmp->heredoc[i])
	{
		tcsetattr(0, TCSANOW, &term);
		g_env.line = readline("> ");
		if (g_env.line)
			g_env.line = ft_strjoin3(g_env.line, "\n");
		while (g_env.line && (ft_strncmp(g_env.line, tmp->heredoc[i],
					ft_strlen(tmp->heredoc[i]))
				|| g_env.line[ft_strlen(tmp->heredoc[i])] != '\n'))
			herdoc_child_loop(tmp, i);
		i++;
	}
	(close(tmp->herepipe[1]), close(tmp->herepipe[0]));
	exit(0);
}

int	herdoc_loop(t_cmd *tmp, struct termios term, struct termios term2)
{
	int	i;

	g_env.h_id = fork();
	if (g_env.h_id == 0)
		heredoc_child(term, tmp);
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
	}
	return (0);
}

int	heredoc(t_cmd *cmd)
{
	t_cmd			*tmp;
	int				i;
	struct termios	term;
	struct termios	term2;

	i = 0;
	tmp = cmd;
	g_env.line = NULL;
	tcgetattr(0, &term);
	term2 = term;
	term.c_lflag &= ~ISIG;
	term.c_lflag &= ~ECHOCTL;
	make_heredoc(tmp);
	while (tmp)
	{
		if (tmp->heredoc)
		{
			if (herdoc_loop(tmp, term, term2))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
