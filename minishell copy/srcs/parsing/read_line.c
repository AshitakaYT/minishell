/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 06:59:34 by aucousin          #+#    #+#             */
/*   Updated: 2022/06/03 12:53:06 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

char	*ft_read_line(int buff_size, int pos, int c)
// must be called with 2048, 0, 0.
{
	char	*buffer;

	buffer = malloc(sizeof(char) * buff_size);
	if (!buffer)
	{
		write(2, "allocution error.\n", 17);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		if (read(0, &c, 1) == -1)
		{
			write(2, "read error.\n", 12);
			exit(EXIT_FAILURE);
		}
		if (c == EOF || c == '\n')
		{
			buffer[pos] = '\0';
			return (buffer);
		}
		buffer[pos] = c;
		pos++;
		if (pos >= buff_size)
		{
			buff_size += BUFFER_SIZE;
			buffer = ft_realloc(buffer, buff_size);
			if (!buffer)
			{
				write(2, "allocution error.\n", 17);
				exit(EXIT_FAILURE);
			}
		}
	}
}
