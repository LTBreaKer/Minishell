/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:54:35 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/10 19:59:30 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int main(void)
{
	int id = fork();
	if (id == 0)
	{
		char *args[] = {"awk", "BEGIN", "{print ARGUMENT, ARGC}", "One", "Two", "Three", "four", NULL};
		execve("/usr/bin/awk", args, NULL);
	}
	wait(NULL);
}