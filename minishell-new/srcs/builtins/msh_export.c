/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:11:10 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/30 11:26:26 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

static int	ft_strscmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	ft_sort_string_tab(char **tab)
{
	int		i;
	int		j;
	int		size;
	char	*swap;

	size = 0;
	while (tab[size])
		size++;
	i = 0;
	while (i < size)
	{
		j = i;
		while (j < size)
		{
			if (ft_strscmp(tab[j], tab[i]) < 0)
			{
				swap = tab[j];
				tab[j] = tab[i];
				tab[i] = swap;
				j = i;
			}
			j++;
		}
		i++;
	}
}

char	*ft_strdupexport(char *src)
{
	char	*dest;
	int		i;
	int		y;

	dest = malloc((ft_strlen((const char *)src) + 1 + 2) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	y = 0;
	while (i < ft_strlen((const char *)src))
	{
		dest[y] = src[i];
		if (src[i] == '=' && src[i + 1] && i == y)
			dest[++y] = '"';
		i++;
		y++;
	}
	dest[y] = '"';
	dest[++y] = '\0';
	return (dest);
}

void	msh_printfexport(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("declare -x %s\n", tab[i]);
		i++;
	}
}

int	msh_exportcount(char **env)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			count++;
		i++;
	}
	return (count);
}
