/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:19:22 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/18 16:25:36 by aharrass         ###   ########.fr       */
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
	// s[idx] != ' '
	// && s[idx] != '\t' && s[idx] != '\n'
	// && s[idx] != 34 && s[idx] != 39
	// && s[idx] != '$')
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
	while (i < len )
	{
		ret[i] = s[dolar];
		i++;
		dolar++;
	}
	return (ret);
}

char	*go_xpnd(t_lex *g, char *s, int idx)
{
	char	*target;
	char	*value;
	char	*ret;
	int		len;
	int		ret_len;
	int		i;
	int		j;
	int		dol;
	int		solo;

	i = 0;
	j = 0;
	len = 0;
	solo = 0;
	dol = idx + 1;
	idx++;
	// ================================ echoo $? =================== //
	if (s[idx] == '?')
	{
		value = ft_itoa(g_env.status);
		len = ft_strlen(value);
		ret_len = ft_strlen(s) - 2 + len;
		ret = malloc (sizeof(char) * (ret_len + 1));
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
		j = dol + 1;
		while (s[j])
		{
			ret[i] = s[j];
			i++;
			j++;
		}
		free(value);
		return (ret);
	}
	target = get_target(s, idx);
	// ================================ echo $$ =================== //
	if (target[0] == '$')
	{
		free(target);
		ret_len = ft_strlen(s) - (len + 2);
		ret = malloc (sizeof(char) * (ret_len + 1));
		ret[ret_len] = '\0';
		while (i < dol - 1)
		{
			ret[i] = s[i];
			i++;
		}
		j = dol + len + 1;
		while (s[j])
		{
			ret[i] = s[j];
			i++;
			j++;
		}
		return (ret);
	}
	else if (target[0] == '\0')	// ================================ echoo $USER$ =================== //
	{
		free(target);
		g->here = 1;
		ret_len = ft_strlen(s);
		ret = malloc (sizeof(char) * (ret_len + 1));
		ret[ret_len] = '\0';
		while (i < ret_len)
		{
			ret[i] = s[i];
			i++;
		}
		return (ret);
	}
	while ((s[idx] && ft_isalnum(s[idx])) || s[idx] == '_')
	{
		len++;
		idx++;
	}
	if (dol == 1 && s[idx] == '\0')
		solo = 1;
	value = ft_get_value(target);
	if (!value && solo)
	{
		free(target);
		return (NULL);
	}
	else if (!value && !solo)
	{
		free(target);
		ret_len = ft_strlen(s) - (len + 1);
		ret = malloc (sizeof(char) * (ret_len + 1));
		ret[ret_len] = '\0';
		while (i < dol - 1)
		{
			ret[i] = s[i];
			i++;
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

void	shifting(char **args, int j)
{
	int g;
	int i;

	i = 0;
	g = j;
	//free(args[j]);
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

char	*exec_expand(t_lex *g)
{
	char	*ret;
	int		on;
	int		doc;
	int		j;
	int		i;

	j = 0;
	ret = NULL;
	while (g->splited2[j])
	{
		i = 0;
		doc = 0;
		if (!ft_strcmp(g->splited2[j], "<<"))
		{
			doc = 1;
			g->deleted[j] = 't';
			j++;
		}
		while (g->splited2[j] && g->splited2[j][i])
		{
			if (on == 1)
				i = 0;
			on = 0;
			g->here = 0;
			if (g->splited2[j] && g->splited2[j][i] == '$')
			{
				if (xpnd_status(g->splited2[j], i) == 0 && doc == 0)
				{
					ret = go_xpnd(g, g->splited2[j], i);
					if (ret)
					{
						free(g->splited2[j]);
						g->splited2[j] = ft_strdup(ret);
						g->deleted[j] = 't';
						free(ret);
					}
					else
					{
						g->deleted[j] = 'f';
						shifting(g->splited2, j);
					}
					on = 1;
				}
			}
			if (on == 0 || g->here == 1)
				i++;
		}
		j++;
	}
	return 0;
}

void	expand_me(t_lex *g)
{
	int	i;
	int	len;

	i = -1;
	len = ft_double_strlen(g->splited2);
	g->deleted = malloc (sizeof(char) * len + 1);
	g->deleted[len] = '\0';
	while (++i < len)
		g->deleted[i] = 'x';
	exec_expand(g);
}

