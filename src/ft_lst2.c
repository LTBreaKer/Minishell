/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:26:16 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/24 01:30:02 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_lstnew(char *var, int f)
{
	t_env	*new;
	char	**tmp;
	int		i;

	i = 0;
	(void)f;
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	tmp = get_var(var);
	if (f == 1)
		free(var);
	if (tmp[0][ft_strlen(tmp[0]) - 1] == '+')
		tmp[0][ft_strlen(tmp[0]) - 1] = '\0';
	new->var = tmp[0];
	new->value = ft_strdup(tmp[1]);
	new->next = NULL;
	if (tmp[1])
		free(tmp[1]);
	free(tmp);
	return (new);
}

t_env	*ft_lstadd_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	tmp = *env;
	if (!*env)
		return (new);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (*env);
}

int	ft_change_elem(char *var, char *value)
{
	t_env	*tmp;

	tmp = g_env.env;
	while (tmp)
	{
		if (ft_strcmp2(tmp->var, var) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

char	*ft_get_value(char *var)
{
	t_env	*tmp;

	tmp = g_env.env;
	while (tmp)
	{
		if (ft_strcmp2(tmp->var, var) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	count_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}
