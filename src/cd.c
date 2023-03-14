/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:06:02 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/14 14:46:25 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	ft_cd(char *dir)
{
	char	*pwd;

	
	if (dir)
		dir = ft_strtrim(dir, " ");
	if (!dir)
		dir = ft_strdup(ft_get_value("HOME"));
	if (!dir)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (!*dir)
	{
		dir = ft_strdup(ft_get_value("PWD"));
		//return (0);
	}
	if ((*dir == '~' && *(dir + 1) == 0))
	{
		free(dir);
		dir = ft_strdup(ft_get_value("HOME"));
	}
	pwd = getcwd(NULL, 0);
	if (*dir == '-' && *(dir + 1) == 0)
	{
		if (chdir(ft_get_value("OLDPWD")) == -1)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			free(pwd);
			free(dir);
			return (1);
		}
		else
			printf("%s\n", ft_get_value("OLDPWD"));
	}
	else if (chdir(dir) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(dir, 2);
		free(pwd);
		free(dir);
		return (1);
	}
	if (ft_change_elem("OLDPWD", pwd))
	{
		ft_lstadd_after_last(&g_env.env, ft_lstnew("OLDPWD=", 0));
		ft_change_elem("OLDPWD", pwd);
	}
	free(pwd);
	pwd = getcwd(NULL, 0);
	if (ft_change_elem("PWD", pwd))
	{
		ft_lstadd_after_last(&g_env.env, ft_lstnew("PWD=", 0));
		ft_change_elem("PWD", pwd);
	}
	free(pwd);
	free(dir);
	return (0);
}
