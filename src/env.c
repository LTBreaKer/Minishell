/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:18:08 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/01 01:59:40 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(void)
{
	t_env	*tmp;

	tmp = g_env.env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->var, tmp->value);
		tmp = tmp->next;
	}
}
