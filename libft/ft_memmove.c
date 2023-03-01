/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:42:38 by aharrass          #+#    #+#             */
/*   Updated: 2022/10/23 00:42:50 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*char_d;
	char	*char_s;

	i = 0;
	char_d = (char *) dst;
	char_s = (char *) src;
	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		while (len--)
			char_d[len] = char_s[len];
	}
	else
	{
		while (i < len)
		{
			char_d[i] = char_s[i];
			i++;
		}
	}
	return (dst);
}
