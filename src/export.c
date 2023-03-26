/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 02:04:12 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/26 00:25:10 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_name(char *var)
{
	char	**tmp;
	size_t	i;

	i = 1;
	if (var == NULL)
		return (0);
	tmp = get_var(var);
	if (initial_check(tmp, var) == 1)
		return (1);
	while (tmp[0][i])
	{
		if (i == ft_strlen(tmp[0]) - 1 && tmp[0][i] == '+'
			&& ft_strlen(tmp[0]) < ft_strlen(var)
			&& var[ft_strlen(tmp[0])] == '=')
			break ;
		if (!ft_isalnum(tmp[0][i]) && tmp[0][i] != '_')
			return (ft_putstr_fd("minishell: export: `", 2),
				ft_putstr_fd(var, 2),
				ft_putstr_fd("': not a valid identifier\n", 2),
				free_split(tmp), 1);
		i++;
	}
	return (free_split(tmp), 0);
}

void	print_export(void)
{
	t_env		*tmp;
	t_export	*tmp3;
	char		*pwd;

	tmp = g_env.env;
	tmp3 = g_env.export;
	pwd = getcwd(NULL, 0);
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
	free(pwd);
}

void	change_value(char **tmp2, t_env *tmp, char *var, int check)
{
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
			return (free_split(tmp2));
		}
		tmp = tmp->next;
	}
	ft_lstadd_after_last(&g_env.env, ft_lstnew(var, 0));
	(ft_lstremove(&g_env.export, tmp2[0]), free_split(tmp2));
}

int	ft_export_help(char *var)
{
	t_env		*tmp;
	t_export	*tmp3;
	char		**tmp2;

	if (ft_check_name(var) == 1)
		return ((g_env.status = 1));
	tmp = g_env.env;
	tmp3 = g_env.export;
	if (ft_strnstr(var, "=", ft_strlen(var)))
	{
		tmp2 = get_var(var);
		change_value(tmp2, tmp, var, 0);
	}
	else if (ft_strnstr(var, "=", ft_strlen(var)) == NULL)
	{
		while (tmp)
		{
			if (!ft_strcmp2(tmp->var, var))
				return (0);
			tmp = tmp->next;
		}
		ft_lstadd_back_export(&g_env.export, ft_lstnew_export(var));
	}
	return (0);
}

void	ft_export(char **args, int check)
{
	int	i;
	int	k;

	k = 0;
	i = 1;
	if (args[1] == NULL)
		print_export();
	else
	{
		while (args[i])
		{
			if (ft_export_help(args[i]) && k == 0)
				k = 1;
			i++;
		}
	}
	if (k == 1 && check == 1)
		exit(1);
}
