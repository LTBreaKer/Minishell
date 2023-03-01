/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 02:04:12 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/01 05:22:19 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export(char *var)
{
	t_env	*tmp;
	t_export	*tmp3;
	char	**tmp2;
	char 	*pwd;

	tmp = g_env.env;
	tmp3 = g_env.export;
	pwd = getcwd(NULL, 0);
	if (var == NULL)
	{
		while (tmp->next)
		{
			printf("declare -x %s=\"%s\"\n", tmp->var, tmp->value);
			tmp = tmp->next;
		}
		while (tmp3)
		{
			printf("declare -x %s=\"%s\"\n", tmp3->var, tmp3->value);
			tmp3 = tmp3->next;
		}
		printf("declare -x _=\"%s/minishell\"\n", pwd);
	}
	else if (ft_strnstr(var, "=", ft_strlen(var)))
	{
		tmp2 = ft_split(var, '=');
		while (tmp)
		{
			if (!ft_strncmp(tmp->var, tmp2[0], ft_strlen(tmp->var)))
			{
				free(tmp->value);
				if (tmp2[1] == NULL)
					tmp->value = "";
				else if (tmp2[1] != NULL)
					tmp->value = tmp2[1];
				return (free(pwd));
			}
			tmp = tmp->next;
		}
		ft_lstadd_back(&g_env.env, ft_lstnew(var));
	}
	else if (ft_strnstr(var, "=", ft_strlen(var)) == NULL)
	{
		
		while (tmp)
		{
			
			if (!ft_strncmp(tmp->var, var, ft_strlen(tmp->var)))
			{
				return (free(pwd));
			}
			tmp = tmp->next;
		}
		ft_lstadd_back_export(&g_env.export, ft_lstnew_export(var));
	}
	free(pwd);
}
