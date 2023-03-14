/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:19:22 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/14 19:28:09 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int qchecker(char *s, char c, int start, int end)
{
	while (s[start] && start < end)
	{
		if (s[start] == c)
			return (start);
		start++;
	}
	return (-1);
}

int	xpnd_status(char *s, int i)
{
	int	j;
	int	k;
	int index;

	k = 0;
	j = 0;
	index = 0;
	while (s[index] && index < i)
	{
		while (index < i)
		{
			if (s[index] == 34)
			{	
				j = qchecker(s, 34, index + 1, i);
				if (j == -1)
					return (0);
				else
				{
					index = j + 1;
					break;
				}
			}
			else if (s[index] == 39)
			{
				j = qchecker(s, 39, index + 1, i);
				if (j == -1)
					return (1);
				else
				{
					index = j + 1;
					break;
				}
			}
			index++;
		}
	}
	return (0);
}

char	*get_target(char *s, int idx)
{
	char	*ret;
	int		dolar;
	int		len;
	int		i;

	dolar = idx;
	i = 0;
	len = 0;
	while (s[idx] && s[idx] != ' '
	&& s[idx] != '\t' && s[idx] != '\n'
	&& s[idx] != 34 && s[idx] != 39
	&& s[idx] != '$')
	{
		len++;
		idx++;
	}
	ret = malloc (sizeof(char) * (len + 1));
	ret[len] = '\0';
	while (i < len )
	{
		ret[i] = s[dolar];
		i++;
		dolar++;
	}
	return (ret);
}

char	*go_xpnd(char *s, int idx)
{
	char	*target;
	char	*value;
	char	*ret;
	int		len;
	int		ret_len;
	int		i;
	int		j;
	int		dol;

	i = 0;
	j = 0;
	len = 0;
	dol = idx + 1;
	idx++;
	target = get_target(s, idx);
	if (*target == '?' && *(target + 1) == 0)
		return (free(target), ft_itoa(g_env.status));
	while (s[idx] && s[idx] != ' ' && s[idx] != '\t' && s[idx] != '\n' && s[idx] != 34 && s[idx] != 39 && s[idx] != '$')
	{
		len++;
		idx++;
	}
	// free target
	// while (i < len )
	// {
	// 	target[i] = s[dol];
	// 	i++;
	// 	dol++;
	// }
	value = ft_get_value(target);
	if (!value)
	{
		free(target);
		return (NULL);
	}
	// printf("s     		: %s\ns      address = %p\n", s, s);
	// printf("targDt      : %s\ntarget address = %p\n", target, target);
	// printf("------------------\n");
	free(target);
	ret_len = ft_strlen(s) - (len + 1) + ft_strlen(value);
	ret = malloc (sizeof(char) * (ret_len + 1));
	ret[ret_len] = '\0';
	dol = dol - i;
	i = 0;
	while (i < dol - 1)
	{
		ret[i] = s[i];
		i++;
	}
	while (value[j])
	{
		ret[i] = value[j];
		i++;
		j++;
	}
	j = dol + len;
	while (s[j])
	{
		ret[i] = s[j];
		i++;
		j++;
	}
	return (ret);
}

char	*exec_expand(char **args)
{
	char	*ret;
	int		on;
	int		doc;
	int		j;
	int		i;

	j = 0;
	ret = NULL;
	while (args[j])
	{
		i = 0;
		doc = 0;
		if (!ft_strcmp(args[j], "<<"))
		{
			doc = 1;
			j++;
		}
		while (args[j][i])
		{
			if (on == 1)
				i = 0;
			on = 0;
			if (args[j][i] == '$')
			{
				if (xpnd_status(args[j], i) == 0 && doc == 0)
				{
					ret = go_xpnd(args[j], i);
					if (ret)
					{
						free(args[j]);
						args[j] = ft_strdup(ret);
						free(ret);
						on = 1;
					}
				}
			}
			if (on == 0)
				i++;
		}
		j++;
	}
	return 0;
}

void	expand_me(char **args)
{
	exec_expand(args);
}

