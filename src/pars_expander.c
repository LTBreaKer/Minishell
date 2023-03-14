/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:19:22 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/14 14:56:37 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	sq_checker(char *str)
// {
	
// }

char	*fill_cleaned(char *s, char *ret)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == 39)
		{
			i++;
			while (s[i] && s[i] != 39)
			{
				ret[j] = s[i];
				i++;
				j++;
			}
		}
		else if (s[i] == 34)
		{
			i++;
			while (s[i] && s[i] != 34)
			{
				ret[j] = s[i];
				i++;
				j++;
			}
		}
		if (s[i] && (s[i] == 34 || s[i] == 39))
			i++;
		else if (s[i] && s[i] != 34 && s[i] != 39)
		{
			ret[j] = s[i];
			i++;
			j++;
		}
	}
	return (ret);
}

char	*clean_quotes(char *s)
{
	char	*ret;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == 39)
		{
			i++;
			while (s[i] != 39 && s[i])
			{
				len++;
				i++;
			}
		}
		else if (s[i] == 34)
		{
			i++;
			while (s[i] != 34 && s[i])
			{
				len++;
				i++;
			}
		}
		if (s[i] && (s[i] == 34 || s[i] == 39))
			i++;
		else if (s[i] && s[i] != 34 && s[i] != 39)
		{
			i++;
			len++;
		}
	}
	ret = malloc(sizeof(char) * (len + 1));
	ret[len] = '\0';
	ret = fill_cleaned(s, ret);
	return (ret);
}

// char	*exec_expand(char *s)
// {
// 	char	*ret;
// 	int		i;

// 	i = 0;
// 	ret = NULL;
// 	while (s[i])
// 	{
// 		if (s[i] == '$')
// 		{
// 			if (xpnd_status(s) == 1)
// 			{
// 				if (ret != NULL)
// 					free(ret);
// 				ret = valid_xpnd(s);
// 			}
// 		}
// 	}
// }

void	expand_me(t_lex *g, char **args)
{
	char	*clean;
	// int		xpnd_status;

	g->i = 0;
	// while (g->splited2[g->i])
	// {
	// 	clean = exec_expand(g->splited2[g->i]);
	// }
	g->i = 0;
	if (args == NULL)
		return ;
	while (args[g->i])
	{
		clean = clean_quotes(args[g->i]);
		free(args[g->i]);
		args[g->i] = clean;
		//printf("clean : %s\n", clean);
		g->i++;
	}
}