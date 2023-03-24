/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:14:11 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/24 01:29:42 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_export	*ft_lstnew_export(char *var)
{
	t_export	*new;
	char		**tmp;
	int			i;

	i = 0;
	new = malloc(sizeof(t_export));
	if (!new)
		return (NULL);
	tmp = ft_split(var, '=');
	new->var = tmp[0];
	new->next = NULL;
	free(tmp);
	return (new);
}

void	ft_lstadd_back_export(t_export **export, t_export *new)
{
	t_export	*tmp;

	tmp = *export;
	if (!*export)
		return ((void)(*export = new));
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_lstadd_after_last(t_env **env, t_env *new)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = *env;
	tmp2 = *env;
	if (!*env)
		return ((void)(*env = new));
	while (tmp2->next->next)
		tmp2 = tmp2->next;
	while (tmp->next)
		tmp = tmp->next;
	tmp2->next = new;
	new->next = tmp;
}

void	ft_env_remove(t_env **env, char *var)
{
	t_env	*tmp;
	t_env	*tmp2;

	if (!*env)
		return ;
	tmp = *env;
	tmp2 = NULL;
	if (ft_strcmp2(tmp->var, var) == 0)
	{
		*env = tmp->next;
		free(tmp->var);
		free(tmp->value);
		free(tmp);
		return ;
	}
	if (tmp->next && ft_strcmp2(tmp->next->var, var) != 0)
		tmp = tmp->next;
	while (tmp && tmp->next)
	{
		if (ft_strcmp2(tmp->next->var, var) == 0)
			return (tmp2 = tmp->next, tmp->next = tmp->next->next,
				free(tmp2->var), free(tmp2->value), free(tmp2));
		tmp = tmp->next;
	}
}

void	ft_lstremove(t_export **export, char *var)
{
	t_export	*tmp;
	t_export	*tmp2;

	if (!*export)
		return ;
	tmp = *export;
	tmp2 = NULL;
	if (ft_strcmp2(tmp->var, var) == 0)
	{
		*export = tmp->next;
		return (free(tmp->var), free(tmp));
	}
	if (tmp->next && ft_strcmp2(tmp->next->var, var) != 0)
		tmp = tmp->next;
	while (tmp && tmp->next)
	{
		if (ft_strcmp2(tmp->next->var, var) == 0)
		{
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			free(tmp2);
			return ;
		}
		tmp = tmp->next;
	}
}
