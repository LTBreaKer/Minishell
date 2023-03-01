/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:52:55 by aharrass          #+#    #+#             */
/*   Updated: 2022/10/20 20:10:16 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_findstart(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				break ;
			j++;
		}
		if (j == ft_strlen(set))
			return ((size_t)(i));
		i++;
	}
	return ((size_t)(i));
}

static size_t	ft_findend(char const *s1, char const *set)
{
	size_t	i;
	int		j;

	i = ft_strlen(s1);
	while (i > 0)
	{
		j = (int)ft_strlen(set);
		while (j >= 0)
		{
			if (s1[i] == set[j])
				break ;
			j--;
		}	
		if (j < 0)
			return (i);
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	start = ft_findstart(s1, set);
	end = ft_findend(s1, set);
	if (start > end)
		return (ft_strdup(""));
	res = (char *)malloc ((end - start + 2));
	if (!res)
		return (0);
	ft_strlcpy(res, (s1 + start), (end - start + 2));
	return (res);
}
