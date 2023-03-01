/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:27:19 by aharrass          #+#    #+#             */
/*   Updated: 2022/10/24 00:14:52 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(long n)
{
	int	len;
	int	buff;

	len = 1;
	if (n >= 0)
		buff = n;
	else
	{
		len++;
		buff = -n;
	}
	while (buff > 9)
	{
		buff /= 10;
		len++;
	}
	return (len);
}

static char	*int_min(int n)
{
	int		len;
	char	*res;

	n += 1;
	len = int_len(n);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res[len] = '\0';
	res[0] = '-';
	n *= -1;
	res[--len] = ((n % 10) + 1) + '0';
	n /= 10;
	while (len > 1)
	{
		res[len - 1] = (n % 10) + '0';
		len--;
		n /= 10;
	}
	return (res);
}

static char	*helper(int n, int len, char *res)
{
	res[len] = '\0';
	while (len > 0)
	{
		res[len - 1] = (n % 10) + '0';
		len--;
		n /= 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	len = int_len(n);
	if (n == -2147483648)
		return (int_min(n));
	res = malloc(sizeof (char) * (len + 1));
	if (!res)
		return (0);
	if (n >= 0)
		return (helper(n, len, res));
	else
	{	
		res[0] = '-';
		res[len] = '\0';
		n *= -1;
		while (len > 1)
		{
			res[len - 1] = (n % 10) + '0';
			len--;
			n /= 10;
		}
	}	
	return (res);
}
