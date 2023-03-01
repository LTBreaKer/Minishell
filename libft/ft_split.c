/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:31:20 by aharrass          #+#    #+#             */
/*   Updated: 2022/12/05 18:54:32 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sep_pass(char const *s, char c)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen (s))
	{
		if (s[i] != c)
			break ;
		i++;
	}
	return (i);
}

static int	wrd_pass(char const *s, char c)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen (s))
	{
		if (s[i] == c)
			break ;
		i++;
	}
	return (i);
}

static int	sub_count(char const *s, char c)
{
	int	char_count;
	int	count;
	int	sep_count;
	int	i;

	i = 0;
	char_count = 0;
	sep_count = 0;
	count = 0;
	while (char_count < (int)ft_strlen(s))
	{
		i += char_count + sep_count;
		sep_count = sep_pass((s + i), c);
		char_count = wrd_pass((s + sep_count + i), c);
		if (char_count)
			count += 1;
		if (char_count == 0)
			return (count);
	}
	return (count);
}

static void	ft_free(char **res, int sub_index)
{
	if (!res[sub_index - 1])
	{
		while (sub_index - 1 >= 0)
			free (res[(--sub_index) - 1]);
		free (res);
		return ;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		sub_index;
	int		char_count;
	int		sep_count;
	int		i;

	sub_index = 1;
	char_count = 1;
	sep_count = 0;
	i = -1;
	if (!s)
		return (NULL);
	res = ft_calloc(sizeof(char *), (sub_count(s, c) + 1));
	if (!res)
		return (0);
	while (char_count && sub_index <= sub_count(s, c))
	{
		i += char_count + sep_count;
		sep_count = sep_pass((s + i), c);
		char_count = wrd_pass((s + sep_count + i), c);
		res[(sub_index++) - 1] = ft_substr((s + i + sep_count), 0, char_count);
		ft_free(res, sub_index - 1);
	}
	return (res);
}
