/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_qk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:08:51 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/07 18:51:41 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	sa_help(t_data *g, int n)
{
	g->start++;
	g->len++;
	while (g->str[g->start] != n)
	{
		g->start++;
		g->len++;
	}
}

static void	str_alloc(char **splited, t_data *g)
{
	int	i;

	g->start = 0;
	i = -1;
	while (++i < g->nbr_word)
	{
		g->len = 0;
		while (g->str[g->start] && (g->str[g->start] == g->c
				|| g->str[g->start] == '\t' || g->str[g->start] == '\n'))
			g->start++;
		while (g->str[g->start] && g->str[g->start] != g->c
			&& g->str[g->start] != '\t' && g->str[g->start] != '\n')
		{
			if (g->str[g->start] == 39 && g->str[g->start])
				sa_help(g, 39);
			else if (g->str[g->start] == 34 && g->str[g->start])
				sa_help(g, 34);
			g->start++;
			g->len++;
		}
		splited[i] = ft_substr(g->str, g->start - g->len, g->len);
		if (!splited[i])
			free_me(splited, i);
	}
}

void	wc_help(t_data *g, int n)
{
	while (1)
	{
		g->idx++;
		if (g->str[g->idx] == n || g->str[g->idx] == '\0')
		{
			while ((g->str[g->idx + 1] != g->c && g->str[g->idx + 1] != '\t'
					&& g->str[g->idx + 1] != '\n') && g->str[g->idx + 1] != 0)
				g->idx++;
			g->on = 1;
			break ;
		}
	}
	g->i++;
}

int	word_count(t_data *g)
{
	g->i = 0;
	g->on = 0;
	while (g->str[++g->idx])
	{
		if (g->on == 1 && (g->str[g->idx] == 34 || g->str[g->idx] == 39))
		{
			g->idx++;
			while (g->str[g->idx] != 34 && g->str[g->idx] != 39)
				g->idx++;
		}
		else if (g->str[g->idx] == 34)
			wc_help(g, 34);
		else if (g->str[g->idx] == 39)
			wc_help(g, 39);
		else if (g->str[g->idx] != g->c && g->str[g->idx] != '\t'
			&& g->str[g->idx] != '\n' && g->on == 0)
		{
			g->on = 1;
			g->i++;
		}
		else if (g->str[g->idx] == g->c || g->str[g->idx] == '\t'
			|| g->str[g->idx] == '\n')
			g->on = 0;
	}
	return (g->i);
}

char	**ft_split_qk(char const *s, char c)
{
	t_data	g;
	char	**splited;

	if (!s)
		return (NULL);
	g.idx = 0;
	while (s[g.idx] == ' ' || s[g.idx] == '\t' || s[g.idx] == '\n')
		g.idx++;
	if (s[g.idx] == '\0')
	{
		splited = malloc(2 * sizeof(char *));
		splited[1] = NULL;
		splited[0] = "";
		return (splited);
	}
	g.str = s;
	g.idx = -1;
	g.c = c;
	g.nbr_word = word_count(&g);
	splited = malloc((g.nbr_word + 1) * sizeof(char *));
	if (!splited)
		return (NULL);
	str_alloc(splited, &g);
	splited[g.nbr_word] = NULL;
	return (splited);
}
