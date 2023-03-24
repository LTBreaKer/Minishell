/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:06:02 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/24 20:20:25 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_dir(char **dir, int check)
{
	*dir = ft_strdup(*dir);
	if (!*dir)
	{
		*dir = ft_strdup(ft_get_value("HOME"));
	}
	if (!*dir)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		g_env.status = 1;
		if (check == 1)
			exit(g_env.status);
		return (1);
	}
	if (!**dir)
		*dir = ft_strdup(ft_get_value("PWD"));
	if ((**dir == '~' && *(*dir + 1) == 0))
	{
		free(*dir);
		*dir = ft_strdup(ft_get_value("HOME"));
	}
	return (0);
}

int	cd_helper(char **pwd, int check, char **dir)
{
	if (chdir(*dir) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		g_env.status = 1;
		(ft_putendl_fd(*dir, 2), free(pwd), free(*dir));
		if (check == 1)
			exit(g_env.status);
		return (1);
	}
	if (ft_change_elem("OLDPWD", *pwd))
		(ft_lstadd_after_last(&g_env.env, ft_lstnew("OLDPWD=", 0)),
			ft_change_elem("OLDPWD", *pwd));
	free(*pwd);
	*pwd = getcwd(NULL, 0);
	if (ft_change_elem("PWD", *pwd))
		(ft_lstadd_after_last(&g_env.env, ft_lstnew("PWD=", 0)),
			ft_change_elem("PWD", *pwd));
	return (0);
}

int	ft_cd(char *dir, int check)
{
	char	*pwd;

	if (set_dir(&dir, check) == 1)
		return (1);
	pwd = getcwd(NULL, 0);
	if (*dir == '-' && *(dir + 1) == 0)
	{
		if (chdir(ft_get_value("OLDPWD")) == -1)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			g_env.status = 1;
			(free(pwd), free(dir));
			if (check == 1)
				exit(g_env.status);
			return (1);
		}
		else
			printf("%s\n", ft_get_value("OLDPWD"));
	}
	else
	{
		if (cd_helper(&pwd, check, &dir) == 1)
			return (1);
	}
	return (free(pwd), free(dir), 0);
}
