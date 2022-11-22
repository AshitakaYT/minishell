/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 06:57:40 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/27 09:55:08 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

char	*ft_strndup(char const *src, int n)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (n < j)
		j = n;
	dest = malloc((j + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (i < j)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_isin(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_len_alnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isprintsh(str[i]) && str[i] != ' ')
		i++;
	return (i);
}

int	ft_lenquote(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != 39)
		i++;
	if (!str[i])
		return (-1);
	i++;
	return (i);
}

int	ft_lendbquote(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != '"')
		i++;
	if (!str[i])
		return (-1);
	i++;
	return (i);
}
