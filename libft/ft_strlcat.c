/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:19:28 by aharrass          #+#    #+#             */
/*   Updated: 2022/10/20 19:59:22 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dstsize;
	size_t	srcsize;

	i = 0;
	if (!dst && size == 0)
		return (ft_strlen(src));
	dstsize = ft_strlen(dst);
	srcsize = ft_strlen(src);
	if (size == 0)
		return (srcsize);
	while (src[i] && i + dstsize < size - 1)
	{
		dst[dstsize + i] = src[i];
		i++;
	}
	if (size > dstsize)
		dst[dstsize + i] = '\0';
	if (dstsize > size)
		return (srcsize + size);
	return (dstsize + srcsize);
}
