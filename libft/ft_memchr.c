/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:04:23 by aharrass          #+#    #+#             */
/*   Updated: 2022/10/23 19:55:46 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	unsigned char			u_c;
	const unsigned char		*u_s;

	i = 0;
	u_c = (unsigned char) c;
	u_s = (const unsigned char *) s;
	while (i < n)
	{
		if (u_s[i] == u_c)
			return ((void *) &s[i]);
		i++;
	}
	return (NULL);
}
