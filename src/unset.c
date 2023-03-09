/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 10:23:55 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/09 09:35:55 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_name1(char *var)
{
	size_t	i;

	i = 1;
	if (var == NULL)
		return (0);
	if (ft_isdigit(var[0]))
		return (printf("minishell: unset: `%s': not a valid identifier\n",
				var), 1);
	while (var[i])
	{
		if (i == ft_strlen(var) - 1 && var[i] == '+'
			&& ft_strlen(var) < ft_strlen(var) && var[ft_strlen(var)] == '=')
			return (0);
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (printf("minishell: unset: `%s': not a valid identifier\n",
					var), 1);
		i++;
	}
	return (0);
}

int	ft_unset(char **args)
{
	int		i;

	i = 1;
	if (args[1] == NULL)
		return (0);
	while (args[i])
	{
		if (ft_check_name1(args[i]))
			return (1);
		ft_env_remove(&g_env.env, args[i]);
		ft_lstremove(&g_env.export, args[i]);
		i++;
	}
	return (0);
}
