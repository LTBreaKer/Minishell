/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:17:02 by aharrass          #+#    #+#             */
/*   Updated: 2023/02/24 17:24:57 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **find_paths(char **envp)
{
	char **paths;

	while(*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (*envp && !ft_strncmp(*envp, "PATH=", 5))
	{
		paths = ft_split(*envp + 5, ':');
		return (paths);
	}
	return (NULL);
}

void	ft_pipe(int infile, char **cmd, int outfile, char **envp)
{
	char **paths;

	paths = find_paths(envp);
}