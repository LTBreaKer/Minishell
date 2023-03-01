/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:14:11 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/01 05:23:53 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_lstnew(char *var)
{
	t_env	*new;
	char	**tmp;
	int		i;

	i = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	tmp = ft_split(var, '=');
	new->var = tmp[0];
	if (tmp[1] == NULL)
		new->value = "";
	else if (tmp[1] != NULL)
		new->value = tmp[1];
	new->next = NULL;
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
	if (tmp[1] == NULL)
		new->value = "";
	else if (tmp[1] != NULL)
		new->value = tmp[1];
	new->next = NULL;
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