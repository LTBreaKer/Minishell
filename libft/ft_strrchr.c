/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:56:57 by aharrass          #+#    #+#             */
/*   Updated: 2022/10/07 20:22:11 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	while (i > 0)
	{
		if (*(s + i) == (char) c)
			return ((char *)(s + i));
		i--;
	}
	if (*(s + i) == (char) c)
		return ((char *)(s + i));
	return (0);
}
