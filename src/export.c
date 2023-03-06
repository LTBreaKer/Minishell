/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 02:04:12 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/04 11:02:04 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_trim(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (ft_strdup(""));
	if (str[i] == '\"' && str[ft_strlen(str) - 1] == '\"')
	{
		str[ft_strlen(str) - 1] = '\0';
		return (ft_strdup(str + 1));
	}
	else if (str[i] == '\'' && str[ft_strlen(str) - 1] == '\'')
	{
		str[ft_strlen(str) - 1] = '\0';
		return (ft_strdup(str + 1));
	}
	else
		return (ft_strdup(str));
}

int	ft_check_name(char *var)
{
	char	**tmp;
	size_t	i;

	i = 1;
	if (var == NULL)
		return (0);
	tmp = ft_split(var, '=');
	if (ft_isdigit(tmp[0][0]))
		return (printf("minishell: export: `%s': not a valid identifier\n",
				tmp[0]), 1);
	while (tmp[0][i])
	{
		if (i == ft_strlen(tmp[0]) - 1 && tmp[0][i] == '+'
			&& ft_strlen(tmp[0]) < ft_strlen(var)
			&& var[ft_strlen(tmp[0])] == '=')
			return (0);
		if (!ft_isalnum(tmp[0][i]) && tmp[0][i] != '_')
			return (printf("minishell: export: `%s': not a valid identifier\n",
					tmp[0]), 1);
		i++;
	}
	i = 0;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
	return (0);
}

void	ft_export(char *var)
{
	t_env		*tmp;
	t_export	*tmp3;
	char		**tmp2;
	char		*pwd;
	int			i;

	i = 0;
	if (ft_check_name(var) == 1)
		return ;
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
			printf("declare -x %s=\"\"\n", tmp3->var);
			tmp3 = tmp3->next;
		}
		printf("declare -x _=\"%s/minishell\"\n", pwd);
		return (free(pwd));
	}
	else if (ft_strnstr(var, "=", ft_strlen(var)))
	{
		tmp2 = ft_split(var, '=');
		while (tmp)
		{
			if (!ft_strcmp(tmp->var, tmp2[0]))
			{
				if (tmp->value != NULL)
					free(tmp->value);
				tmp->value = ft_trim(tmp2[1]);
				return (free(pwd), free(tmp2[0]), free(tmp2[1]), free(tmp2));
			}
			tmp = tmp->next;
		}
		ft_lstadd_after_last(&g_env.env, ft_lstnew(var, 0));
		ft_lstremove(&g_env.export, tmp2[0]);
		while (tmp2[i])
			free(tmp2[i++]);
		free(tmp2);
	}
	else if (ft_strnstr(var, "=", ft_strlen(var)) == NULL)
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->var, var))
				return (free(pwd));
			tmp = tmp->next;
		}
		ft_lstadd_back_export(&g_env.export, ft_lstnew_export(var));
	}
	free(pwd);
}
