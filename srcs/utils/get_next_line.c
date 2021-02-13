/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 11:33:36 by bditte            #+#    #+#             */
/*   Updated: 2021/02/13 16:12:32 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"

void	putstr(char	*str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

void	verify(char **str, int ret)
{
	if (ret)
	{
		free(*str);
		*str = 0;
	}
}

int	get_next_line(int fd, char **line)
{
	char		*str[256];
	char		*buffer;
	int			read_value;
	char		c;

	if (!line || BUFFER_SIZE <= 0 || (read(fd, &c, 0) == -1)
		|| !(buffer = malloc(BUFFER_SIZE + 1)))
		return (-1);
	str[fd] = malloc(1);
	*str[fd] = 0;
	while (!ft_strchr_gnl(str[fd], '\n')
		&& (read_value = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_value] = 0;
		str[fd] = ft_strjoin_gnl(&str[fd], buffer);
	}
	*line = ft_newline(str[fd]);
	free(buffer);
	verify(&str[fd], 1);
	return (1);
}
