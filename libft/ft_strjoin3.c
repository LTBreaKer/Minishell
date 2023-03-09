/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:29:32 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/09 15:33:19 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

char	*ft_strjoin3(char *s1, char *s2)
{
	char	*strfinal;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	strfinal = malloc(sizeof (char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!strfinal)
		return (NULL);
	while (s1[i] != '\0')
	{
		strfinal[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		strfinal[i] = *s2;
		s2++;
		i++;
	}
	strfinal[i] = '\0';
	free(s1);
	return (strfinal);
}
