/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 22:42:25 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/17 16:14:47 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *hold)
{
	char		*buf;
	int			rd;

	rd = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (!ft_strchr4(hold, '\n') && rd)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
		{
			free (buf);
			free (hold);
			return (NULL);
		}
		buf[rd] = 0;
		hold = ft_strjoin4(hold, buf);
		if (!hold)
			return (NULL);
	}
	free (buf);
	return (hold);
}

char	*ft_get_line(char *hold)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!ft_strlen4(hold))
		return (NULL);
	while (hold[i] && hold[i] != '\n')
		i++;
	if (hold[i] == '\n')
		line = malloc(sizeof(char) * (i + 2));
	else
		line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	while (j <= i && hold[j])
	{
		line[j] = hold[j];
		j++;
	}
	line[j] = 0;
	return (line);
}

char	*ft_clean(char *hold)
{
	char	*n_hold;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (hold[i] && hold[i] != '\n')
		i++;
	if (!hold[i])
	{
		free (hold);
		return (NULL);
	}
	i++;
	n_hold = malloc(sizeof (char) * (ft_strlen4(hold) - i + 1));
	if (!n_hold)
	{
		free (hold);
		return (NULL);
	}
	while (hold[i])
		n_hold[j++] = hold[i++];
	n_hold[j] = 0;
	free (hold);
	return (n_hold);
}

char	*get_next_line(int fd)
{
	static char	*hold;
	char		*line;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	hold = ft_read(fd, hold);
	if (!hold)
		return (NULL);
	line = ft_get_line(hold);
	hold = ft_clean(hold);
	return (line);
}
