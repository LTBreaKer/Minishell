/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:00:59 by aharrass          #+#    #+#             */
/*   Updated: 2022/10/20 03:15:03 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*char_dst;
	char		*char_src;
	size_t		i;

	i = 0;
	char_dst = (char *) dst;
	char_src = (char *) src;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		char_dst[i] = char_src[i];
		i++;
	}
	return (dst);
}
