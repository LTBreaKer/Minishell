/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_expander_cases.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 21:24:09 by rel-mham          #+#    #+#             */
/*   Updated: 2023/03/20 21:24:57 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*xpanterrogation(char *s, int dol)
{
	char	*value;
	char	*ret;
	int		len;

	value = ft_itoa(g_env.status);
	len = ft_strlen(s) - 2 + ft_strlen(value);
	ret = malloc(sizeof(char) * (len + 1));
	ret[len] = '\0';
	ft_strlcpy(ret, s, dol);
	ft_strlcpy(ret + dol - 1, value, ft_strlen(value) + 1);
	ft_strlcpy(ret + dol - 1 + ft_strlen(value), s + dol + 1, ft_strlen(s) - dol
			+ 1);
	free(value);
	return (ret);
}

char	*dol_dol(char *target, char *s, int dol)
{
	char	*ret;
	int		len;

	free(target);
	len = ft_strlen(s) - 2;
	ret = malloc(sizeof(char) * (len + 1));
	ret[len] = '\0';
	ft_strlcpy(ret, s, dol);
	ft_strlcpy(ret + dol - 1, s + dol + 1, ft_strlen(s) - dol + 1);
	return (ret);
}

char	*null_val(char *target, char *s, int dol, int len)
{
	char	*ret;
	int		ret_len;

	free(target);
	ret_len = ft_strlen(s) - (len + 1);
	ret = malloc(sizeof(char) * (ret_len + 1));
	ret[ret_len] = '\0';
	ft_strlcpy(ret, s, dol);
	ft_strlcpy(ret + dol - 1, s + dol + len, ft_strlen(s) - dol - len + 1);
	return (ret);
}

char	*normal_case(char *value, char *s, int dol, int len)
{
	char	*ret;
	int		ret_len;

	ret_len = ft_strlen(s) - (len + 1) + ft_strlen(value);
	ret = malloc(sizeof(char) * (ret_len + 1));
	ret[ret_len] = '\0';
	ft_strlcpy(ret, s, dol);
	ft_strlcpy(ret + dol - 1, value, ft_strlen(value) + 1);
	ft_strlcpy(ret + dol - 1 + ft_strlen(value), s + dol + len, ft_strlen(s)
			- dol - len + 1);
	return (ret);
}

char	*dol_zero(char *target, t_lex *g, char *s)
{
	char	*ret;
	int		ret_len;

	free(target);
	g->here = 1;
	ret_len = ft_strlen(s);
	ret = malloc(sizeof(char) * (ret_len + 1));
	ret[ret_len] = '\0';
	ft_strlcpy(ret, s, ret_len + 1);
	return (ret);
}
