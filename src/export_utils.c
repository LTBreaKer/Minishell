/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:57:47 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/25 19:58:19 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_var(char *var)
{
	int		i;
	char	**tmp;

	i = 0;
	if (var == NULL)
		return (NULL);
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

int	initial_check(char **tmp, char *var)
{
	if (!tmp)
		return (1);
	if (tmp[0] == NULL)
	{
		(ft_putstr_fd("minishell: export: `", 2), ft_putstr_fd(var, 2),
			ft_putstr_fd("': not a valid identifier\n", 2));
		return (free_split(tmp), 1);
	}
	else if (tmp[0][0] == '+')
	{
		(ft_putstr_fd("minishell: export: `", 2), ft_putstr_fd(var, 2),
			ft_putstr_fd("': not a valid identifier\n", 2));
		return (free_split(tmp), 1);
	}
	if (ft_isdigit(tmp[0][0]) || (!ft_isalnum(tmp[0][0]) && tmp[0][0] != '_'))
		return (ft_putstr_fd("minishell: export: `", 2), ft_putstr_fd(var, 2),
			ft_putstr_fd("': not a valid identifier\n", 2), free_split(tmp), 1);
	return (0);
}
