/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_expnd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:53:38 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/24 01:24:01 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dollar_index(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*null_value(char *s, int i, int doll_idx)
{
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(s) - (i - doll_idx) + 2));
	if (!new)
		return (perror("malloc"), NULL);
	ft_strlcpy(new, s, doll_idx + 1);
	ft_strlcpy(new + doll_idx, s + i, ft_strlen(s) - i + 1);
	free(s);
	return (new);
}

char	*ft_str_replace(char *s, char *tmp, char *val)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	k = 0;
	new = malloc(sizeof(char) * (ft_strlen(s) - ft_strlen(tmp) + ft_strlen(val)
				+ 2));
	if (!new)
		return (perror("malloc"), NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '$' && ft_strncmp(s + i + 1, tmp, ft_strlen(tmp)) == 0
			&& ft_isalnum(s[i + ft_strlen(tmp) + 1]) == 0 && k++ == 0)
		{
			ft_strlcpy(new + j, val, ft_strlen(val) + 1);
			j += ft_strlen(val);
			i += ft_strlen(tmp) + 1;
		}
		else
			new[j++] = s[i++];
	}
	return (new[j] = '\0', free(s), free(val), new);
}

void	here_help(char **s, int i, int doll_idx, char **tmp)
{
	char	*val;

	val = ft_get_value(*tmp);
	if (!val)
	{
		*s = null_value(*s, i, doll_idx);
		free(*tmp);
	}
	else
	{
		*s = ft_str_replace(*s, *tmp, val);
		free(*tmp);
	}
}

char	*here_expand(char *s)
{
	int		i;
	int		doll_idx;
	char	*tmp;

	doll_idx = dollar_index(s);
	while (doll_idx != -1)
	{
		if (s[doll_idx + 1] == '?')
		{
			s = ft_str_replace(s, "?", ft_itoa(g_env.status));
			doll_idx = dollar_index(s);
			continue ;
		}
		i = doll_idx + 1;
		while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
			i++;
		tmp = ft_substr(s, doll_idx + 1, i - doll_idx - 1);
		here_help(&s, i, doll_idx, &tmp);
		doll_idx = dollar_index(s);
	}
	return (s);
}
