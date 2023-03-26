/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_stack_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:12:05 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/26 17:43:00 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_stack	*ft_lstnew2(char c)
{
	t_stack	*list1;

	list1 = malloc(sizeof(t_stack));
	if (!list1)
		return (NULL);
	list1->c = c;
	list1->next = NULL;
	return (list1);
}

void	ft_lstadd_front(t_stack **lst, t_stack *new)
{
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		new->next = *lst;
		*lst = new;
	}
}

int	ft_lstsize(t_stack *lst)
{
	int	i;

	i = 0;
	if (lst)
	{
		i++;
		while (lst->next)
		{
			lst = lst->next;
			i++;
		}
	}
	return (i);
}

void	add_push(t_stack **lst, char c)
{
	t_stack	*new;

	new = ft_lstnew2(c);
	ft_lstadd_front(lst, new);
}

void	free_lst(t_stack *lst)
{
	t_stack	*tmp;

	tmp = lst;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}
