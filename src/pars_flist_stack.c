/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_flist_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:49:59 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/16 20:42:50 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*ft_lstfinalnew(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->in = -2;
	new->out = -2;
	new->wf = 0;
	new->args = NULL;
	new->heredoc = NULL;
	new->next = NULL;
	return (new);
}

t_cmd	*ft_lstlast(t_cmd	*s)
{
	if (!s)
		return (s);
	while (s->next)
		s = s->next;
	return (s);
}

void	ft_lstadd_backfinal(t_cmd **env, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = ft_lstlast(*env);
	tmp->next = new;
}

int	check_dash_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i - 1] == 'n' && (str[i] == ' '
			|| str[i] == '\0' || str[i] == '\t' || str[i] == '\n'))
		return (1);
	else
		return (0);
}

int	ambig_check(char c, char *s)
{
	int	i;

	i = 0;
	if (c == 'x')
		return (1);
	if (!s)
		return (0);
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
		i++;
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	if (s[i] == '\0')
		return (1);
	else
		return (0);
}
