/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 02:04:12 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/23 19:59:54 by aharrass         ###   ########.fr       */
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

char	**get_var(char *var)
{
	int		i;
	char	**tmp;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (i == (int)ft_strlen(var) - 1)
		return (ft_split(var, '='));
	else
	{
		tmp = malloc(sizeof(char *) * 3);
		tmp[0] = ft_substr(var, 0, i);
		tmp[1] = ft_substr(var, i + 1, ft_strlen(var) - i);
		tmp[2] = NULL;
	}
	return (tmp);
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	ft_check_name(char *var)
{
	char	**tmp;
	size_t	i;

	i = 1;
	if (var == NULL)
		return (0);
	tmp = get_var(var);
	if (ft_isdigit(tmp[0][0]))
		return (ft_putstr_fd("minishell: export: `", 2), ft_putstr_fd(tmp[0],
				2), ft_putstr_fd("': not a valid identifier\n", 2),
				free_double(tmp), 1);
	while (tmp[0][i])
	{
		if (i == ft_strlen(tmp[0]) - 1 && tmp[0][i] == '+'
			&& ft_strlen(tmp[0]) < ft_strlen(var)
			&& var[ft_strlen(tmp[0])] == '=')
			break ;
		if (!ft_isalnum(tmp[0][i]) && tmp[0][i] != '_')
			return (ft_putstr_fd("minishell: export: `", 2), ft_putstr_fd(tmp[0], 2),
				ft_putstr_fd("': not a valid identifier\n", 2),
					free_double(tmp), 1);
		i++;
	}
	i = 0;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
	return (0);
}

void	ft_export_help(char *var)
{
	t_env		*tmp;
	t_export	*tmp3;
	char		**tmp2;
	char		*pwd;
	int			i;
	int			check;

	i = 0;
	check = 0;
	if (ft_check_name(var) == 1)
		return ((void)(g_env.status = 1));
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
			printf("declare -x %s\n", tmp3->var);
			tmp3 = tmp3->next;
		}
		printf("declare -x _=\"%s/minishell\"\n", pwd);
		return (free(pwd));
	}
	else if (ft_strnstr(var, "=", ft_strlen(var)))
	{
		tmp2 = get_var(var);
		if (tmp2[0][ft_strlen(tmp2[0]) - 1] == '+')
		{
			tmp2[0][ft_strlen(tmp2[0]) - 1] = '\0';
			check = 1;
		}
		while (tmp)
		{
			if (!ft_strcmp2(tmp->var, tmp2[0]))
			{
				if (check == 1)
					tmp->value = ft_strjoin1(tmp->value, ft_strdup(tmp2[1]));
				else
				{
					if (tmp->value != NULL)
						free(tmp->value);
					tmp->value = ft_strdup(tmp2[1]);
				}
				while (tmp2[i])
					free(tmp2[i++]);
				free(tmp2);
				return (free(pwd));
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
			if (!ft_strcmp2(tmp->var, var))
				return (free(pwd));
			tmp = tmp->next;
		}
		ft_lstadd_back_export(&g_env.export, ft_lstnew_export(var));
	}
	free(pwd);
}

void	ft_export(char **args)
{
	int	i;

	i = 1;
	if (args[1] == NULL)
		ft_export_help(NULL);
	else
	{
		while (args[i])
		{
			ft_export_help(args[i]);
			i++;
		}
	}
}
