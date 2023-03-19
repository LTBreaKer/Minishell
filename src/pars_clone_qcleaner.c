/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_clone_qcleaner.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:34:34 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/18 17:23:25 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*fill_cleaned2(char *s, char *ret)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == 39)
		{
			i++;
			while (s[i] && s[i] != 39)
				ret[k++] = s[i++];
		}
		else if (s[i] == 34)
		{
			i++;
			while (s[i] && s[i] != 34)
				ret[k++] = s[i++];
		}
		if (s[i] && (s[i] == 34 || s[i] == 39))
			i++;
		else if (s[i] && s[i] != 34 && s[i] != 39)
			ret[k++] = s[i++];
	}
	return (ret);
}

void	cquotes_helper2(int *i, int *len, char *s, int n)
{
	(*i)++;
	while (s[*i] != n && s[*i])
	{
		(*len)++;
		(*i)++;
	}
}

char	*clean_quotes2(char *s)
{
	char	*ret;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == 39)
			cquotes_helper2(&i, &len, s, 39);
		else if (s[i] == 34)
			cquotes_helper2(&i, &len, s, 34);
		if (s[i] && (s[i] == 34 || s[i] == 39))
			i++;
		else if (s[i] && s[i] != 34 && s[i] != 39)
		{
			i++;
			len++;
		}
	}
	ret = malloc(sizeof(char) * (len + 1));
	ret[len] = '\0';
	ret = fill_cleaned2(s, ret);
	return (ret);
}
