/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:54:00 by aharrass          #+#    #+#             */
/*   Updated: 2023/01/09 00:07:10 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi(const char *str)
{
	int					i;
	int					s;
	unsigned long long	j;

	i = 0;
	s = 1;
	j = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		s *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		j = j * 10 + str[i++] - '0';
		if (j > 9223372036854775807 && s == 1)
			return (-1);
		if (j > 9223372036854775807 && s == -1)
			return (0);
	}
	return (j * s);
}
