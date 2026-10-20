/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rueapen <rueapen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:50:40 by rueapen           #+#    #+#             */
/*   Updated: 2025/09/12 18:16:22 by rueapen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_free(char *str)
{
	free(str);
	return (NULL);
}

char	*gnl_cut_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (--i >= 0)
		line[i] = stash[i];
	return (line);
}

char	*gnl_rest(char *stash)
{
	char	*newstash;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
		return (gnl_free(stash));
	newstash = malloc(sizeof(char) * (gnl_len(stash) - i + 1));
	if (!newstash)
		return (gnl_free(stash));
	while (stash[i])
		newstash[j++] = stash[++i];
	newstash[j] = '\0';
	free(stash);
	return (newstash);
}

char	*read_line(int fd, char *save)
{
	char	*buffer;
	int		red;

	red = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (gnl_free(save));
	while (red > 0)
	{
		red = read(fd, buffer, BUFFER_SIZE);
		if (red == -1)
			return (gnl_read_fail(buffer, save));
		buffer[red] = '\0';
		save = gnl_join(save, buffer);
		if (!save)
			return (gnl_free(buffer));
		if (gnl_has_nl(save, '\n'))
			break ;
	}
	free(buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_line(fd, stash);
	if (!stash)
		return (NULL);
	line = gnl_cut_line(stash);
	if (!line)
	{
		stash = gnl_free(stash);
		return (NULL);
	}
	stash = gnl_rest(stash);
	return (line);
}
