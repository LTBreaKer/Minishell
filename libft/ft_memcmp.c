/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:52:54 by aharrass          #+#    #+#             */
/*   Updated: 2022/10/20 03:13:54 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*char_s1;
	unsigned char	*char_s2;

	char_s1 = (unsigned char *) s1;
	char_s2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (char_s1[i] != char_s2[i])
			return (char_s1[i] - char_s2[i]);
		i++;
	}
	return (0);
}
