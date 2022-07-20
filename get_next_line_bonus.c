/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:29:57 by lorbke            #+#    #+#             */
/*   Updated: 2022/07/20 14:49:50 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_temp(char *line, char *temp)
{
	char	*delim;

	if (temp != NULL)
	{
		ft_strlcpy(line, temp, BUFFER_SIZE);
		delim = ft_strchr(line, '\n');
		if (delim != NULL)
		{
			ft_strlcpy(temp, &delim[1], BUFFER_SIZE);
			delim[1] = 0;
			return (1);
		}
		free(temp);
	}
	return (0);
}

int	fill_buffer(int fd, char *buffer)
{
	int	len;

	len = read(fd, buffer, BUFFER_SIZE);
	if (len <= 0)
		return (0);
	buffer[len] = 0;
	return (1);
}

char	*store_temp(char *buffer, char *temp)
{
	char	*delim;

	delim = ft_strchr(buffer, '\n');
	if (delim != NULL)
	{
		temp = malloc(sizeof(char) * BUFFER_SIZE);
		ft_strlcpy(temp, &delim[1], BUFFER_SIZE);
		delim[1] = 0;
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*buffer[1025];
	char		*line[1025];
	static char	*temp[1025];

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 1024)
		return (NULL);
	line[fd] = malloc(sizeof(char) * BUFFER_SIZE);
	line[fd][0] = 0;
	if (get_temp(line[fd], temp[fd]) == 1)
		return (line[fd]);
	temp[fd] = NULL;
	buffer[fd] = malloc(sizeof(char) * BUFFER_SIZE);
	while (temp[fd] == NULL && fill_buffer(fd, buffer[fd]) == 1)
	{
		temp[fd] = store_temp(buffer[fd], temp[fd]);
		line[fd] = ft_strjoin(line[fd], buffer[fd]);
	}
	free(buffer[fd]);
	if (line[fd][0] == 0)
	{
		free(line[fd]);
		return (NULL);
	}
	return (line[fd]);
}

// int	main(void)
// {
// 	int	fd;

// 	// fd = open("text.txt", O_RDONLY);
// 	// fd = open(NULL, O_RDONLY);
// 	fd = open("multiple_line_with_nl.txt", O_RDONLY);
// 	printf(" 1: %s", get_next_line(fd));
// 	return (0);
// }
