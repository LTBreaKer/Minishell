/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_expander_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 21:27:53 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/26 17:41:05 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	qchecker(char *s, char c, int start, int end)
{
	while (s[start] && start < end)
	{
		if (s[start] == c)
			return (start);
		start++;
	}
	return (-1);
}

int	xpnd_help(char *s, int i, int *index, char c)
{
	int	j;

	j = qchecker(s, c, *index + 1, i);
	if (j == -1)
		return (0);
	else
	{
		(*index) = j + 1;
		return (1);
	}
}

int	xpnd_in_loop(char *s, int i, int *index)
{
	while ((*index) < i)
	{
		if (s[(*index)] == 34)
		{
			if (!xpnd_help(s, i, index, 34))
				return (0);
			else
				break ;
		}
		else if (s[(*index)] == 39)
		{
			if (!xpnd_help(s, i, index, 39))
				return (1);
			else
				break ;
		}
		(*index)++;
	}
	return (2);
}

char	*get_target(char *s, int idx)
{
	char	*ret;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (s[idx] == '$')
	{
		ret = malloc (sizeof(char) + 1);
		ret[1] = '\0';
		ret[0] = '$';
		return (ret);
	}
	while ((s[idx] && ft_isalnum(s[idx])) || s[idx] == '_')
	{
		len++;
		idx++;
	}
	ret = malloc (sizeof(char) * (len + 1));
	ret[len] = '\0';
	idx = idx - len;
	while (i < len)
		ret[i++] = s[idx++];
	return (ret);
}

void	shifting(char **args, int j)
{
	int	g;
	int	i;

	i = 0;
	g = j;
	while (args[j])
	{
		if (i == 0)
		{
			free(args[g]);
			i = 1;
		}
		args[j] = args[j + 1];
		j++;
	}
}
