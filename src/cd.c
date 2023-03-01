/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:06:02 by aharrass          #+#    #+#             */
/*   Updated: 2023/02/28 21:19:17 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(char *dir)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(dir, 2);
	}
	else if (*dir == '-' && *(dir + 1) == 0)
	{
		
	}
	else
	{
		free(pwd);
		pwd = getcwd(NULL, 0);
		ft_putendl_fd(pwd, 1);
	}
	free(pwd);
}
