/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:53:54 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/27 09:54:42 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

char	*ft_realloc(char *str, int size)
{
	char	*ret;

	ret = malloc(sizeof(char) * size);
	if (!ret)
		return (NULL);
	ret = ft_strcpy(ret, str);
	free(str);
	return (ret);
}

int	ft_isprintsh(int c)
{
	if (c < 32 || c > 126 || c == 39 || c == '|'
		|| c == '"' || c == '>' || c == '<')
		return (0);
	return (1);
}

int	ft_isred(int c)
{
	if (c == RRED || c == LRED || c == DRRED || c == DLRED)
		return (1);
	return (0);
}

int	ft_isred2(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_istxt(int c)
{
	if (c == TEXT || c == SQTEXT || c == DQTEXT)
		return (1);
	return (0);
}
