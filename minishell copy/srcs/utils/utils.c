/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 06:57:40 by aucousin          #+#    #+#             */
/*   Updated: 2022/06/07 15:43:28 by aucousin         ###   ########lyon.fr   */
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

void	ft_exit_fd(int fd, char *str)
{
	int	i;

	i = ft_strlen(str);
	write(fd, str, i);
	exit(EXIT_FAILURE);
}

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

int	ft_istxt(int c)
{
	if (c == TEXT || c == SQTEXT|| c == DQTEXT)
		return (1);
	return (0);
}
