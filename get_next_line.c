/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:29:57 by lorbke            #+#    #+#             */
/*   Updated: 2022/07/22 18:03:22 by lorbke           ###   ########.fr       */
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
		temp = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (temp == NULL)
			return (NULL);
		ft_strlcpy(temp, &delim[1], BUFFER_SIZE);
		delim[1] = 0;
	}
	return (temp);
}

char	*fill_line(int fd, char **buffer, char **line, char **temp)
{
	*buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (*buffer == NULL)
	{
		free(*line);
		return (NULL);
	}
	while (*temp == NULL && fill_buffer(fd, *buffer) == 1)
	{
		*temp = store_temp(*buffer, *temp);
		*line = ft_strjoin(*line, *buffer);
	}
	free(*buffer);
	return (*line);
}

char	*get_next_line(int fd)
{
	char		*buffer[1024];
	char		*line[1024];
	static char	*temp[1024];

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 1024)
		return (NULL);
	line[fd] = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (line[fd] == NULL)
		return (NULL);
	line[fd][0] = 0;
	if (get_temp(line[fd], temp[fd]) == 1)
		return (line[fd]);
	temp[fd] = NULL;
	line[fd] = fill_line(fd, &buffer[fd], &line[fd], &temp[fd]);
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
// 	int i;
// 	char	*string;

// 	fd = open("text.txt", O_RDONLY);
// 	// fd = open(NULL, O_RDONLY);
// 	// fd = open("multiple_line_with_nl.txt", O_RDONLY);
// 	i = 0;
// 	while (i < 10)
// 	{
// 		string = get_next_line(fd);
// 		printf("%s\n", string);
// 		free(string);
// 		i++;
// 	}
// 	return (0);
// }
