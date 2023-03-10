/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_me.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:24:11 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/03 15:25:00 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_me(char **splited, int i)
{
	while (i-- > 0)
		free(splited[i]);
	free(splited);
}
