/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 09:34:28 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/17 16:14:34 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin4(char *s1, char *s2)
{
	size_t	len;
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s2)
		return (0);
	if (!s1)
		return (ft_strdup4(s2));
	len = ft_strlen4(s1) + ft_strlen4(s2);
	res = (malloc(len * (sizeof (*res)) + 1));
	if (!res)
		return (NULL);
	while (s1[j])
		res[i++] = s1[j++];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = 0;
	free (s1);
	return (res);
}

char	*ft_strchr4(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

size_t	ft_strlen4(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup4(const char *s1)
{
	int		i;
	size_t	src_len;
	char	*dup;

	i = 0;
	src_len = ft_strlen4(s1);
	dup = malloc(sizeof(*s1) * src_len + 1);
	if (dup == NULL)
		return (0);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
