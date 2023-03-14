/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 22:45:03 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/12 14:21:36 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int main()
{
	char *str[] = {"awk", "BEGIN {print \"Arguments =\", ARGC}", "One", "Two", "Three", "Four", NULL};
	execve("/usr/bin/awk", str, NULL);
}