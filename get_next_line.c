/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynini <ynini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:47:17 by ynini             #+#    #+#             */
/*   Updated: 2025/02/26 04:46:47 by ynini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "so_long.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

ssize_t	read_line(int fd, char **stock)
{
	char	*buffer;
	char	*tmp;
	ssize_t	bytes_read;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (free(*stock), *stock = NULL, exit(1), -1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (free(buffer), bytes_read);
	buffer[bytes_read] = '\0';
	tmp = ft_strjoin(*stock, buffer);
	if (!tmp)
		return (free(buffer), free(*stock), *stock = NULL, -1);
	free(buffer);
	free(*stock);
	*stock = tmp;
	return (bytes_read);
}

char	*get_line1(char *stock)
{
	char	*line;
	int		i;

	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
		return (ft_strdup(stock));
	if (stock[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (exit(1), NULL);
	ft_strlcpy(line, stock, i + 1);
	return (line);
}

char	*get_ridof_line(char *stock)
{
	int		i;
	char	*str;

	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
		return (free(stock), NULL);
	if (stock[i] == '\n')
		i++;
	str = ft_strdup(stock + i);
	if (!str)
		return (free(stock), NULL);
	free(stock);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX \
	|| read(fd, NULL, 0) < 0)
		return (free(stock), stock = NULL, NULL);
	while (!ft_strchr(stock, '\n'))
	{
		bytes_read = read_line(fd, &stock);
		if (bytes_read < 0)
			return (free(stock), stock = NULL, NULL);
		if (bytes_read == 0)
			break ;
	}
	if (!stock || !*stock)
		return (free(stock), stock = NULL, NULL);
	line = get_line1(stock);
	if (!line)
		return (free(stock), stock = NULL, NULL);
	stock = get_ridof_line(stock);
	return (line);
}
