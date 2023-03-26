/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 10:23:55 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/26 17:29:07 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_err(char *str1, char *str2, char *str3)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
}

int	ft_check_name1(char *var)
{
	size_t	i;

	i = 1;
	if (var == NULL)
		return (0);
	if (ft_isdigit(var[0]) || (!ft_isalnum(var[0]) && var[0] != '_'))
		return (print_err("minishell: unset: `", var,
				"': not a valid identifier\n"), 1);
	while (var[i])
	{
		if (i == ft_strlen(var) - 1 && var[i] == '+'
			&& ft_strlen(var) < ft_strlen(var) && var[ft_strlen(var)] == '=')
			return (0);
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (print_err("minishell: unset: `", var,
					"': not a valid identifier\n"), 1);
		i++;
	}
	return (0);
}

int	ft_unset(char **args, int check)
{
	int	i;

	i = 1;
	if (args[1] == NULL)
		return (0);
	while (args[i])
	{
		if (ft_check_name1(args[i]))
		{
			g_env.status = 1;
			if (!check)
				return (1);
			exit(1);
		}
		ft_env_remove(&g_env.env, args[i]);
		ft_lstremove(&g_env.export, args[i]);
		i++;
	}
	return (0);
}
