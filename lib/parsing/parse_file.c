/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rueapen <rueapen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:50:26 by rueapen           #+#    #+#             */
/*   Updated: 2026/10/10 22:50:26 by rueapen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*validate(t_game *game)
{
	char	*error;

	error = check_identifiers(game);
	if (error != NULL)
		return (error);
	return (validate_map(game));
}

void	parse_file(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	char	*error;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit(game, "Could not open file");
	error = NULL;
	if (read(fd, &line, 0) == -1)
		error = "Could not read file";
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (error == NULL)
			error = parse_line(game, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (error == NULL)
		error = validate(game);
	if (error != NULL)
		error_exit(game, error);
}
