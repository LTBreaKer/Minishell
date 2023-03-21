/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:52:44 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/20 21:58:07 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start && ft_strlen(s) >= start)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		len = 0;
	p = malloc(len + 1);
	if (!p)
		return (0);
	if (len == 0 || start > ft_strlen(s))
	{
		p[i] = 0;
		return (p);
	}
	while (s[start] && i < len)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}
