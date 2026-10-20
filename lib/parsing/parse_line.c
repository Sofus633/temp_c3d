/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rueapen <rueapen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:50:26 by rueapen           #+#    #+#             */
/*   Updated: 2026/10/10 22:50:26 by rueapen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	all_ids_found(t_game *game)
{
	return (game->no_found && game->so_found && game->we_found
		&& game->ea_found && game->f_found && game->c_found);
}

static char	*parse_identifier(t_game *game, char *p)
{
	char	*space;
	char	*rest;

	space = find_char(p, ' ');
	if (space == NULL)
		return ("Identifier without value or invalid line");
	*space = '\0';
	rest = skip_spaces(space + 1);
	if (*rest == '\0')
		return ("Identifier without value");
	if (ft_strncmp(p, "F", 2) == 0)
		return (parse_color(&game->floor, &game->f_found, rest));
	if (ft_strncmp(p, "C", 2) == 0)
		return (parse_color(&game->ceiling, &game->c_found, rest));
	return (parse_texture(game, p, rest));
}

static char	*handle_map_line(t_game *game, char *line, char *p)
{
	if (*p == '\0')
	{
		game->map_started = 2;
		return (NULL);
	}
	if (game->map_started == 2)
	{
		if (is_map_line(line))
			return ("Empty line inside the map");
		return ("Invalid content after the map");
	}
	if (!is_map_line(line))
		return ("Invalid character in map");
	return (add_map_line(game, line));
}

char	*parse_line(t_game *game, char *line)
{
	char	*p;

	strip_eol(line);
	p = skip_spaces(line);
	if (game->map_started != 0)
		return (handle_map_line(game, line, p));
	if (*p == '\0')
		return (NULL);
	if (is_map_line(line))
	{
		if (!all_ids_found(game))
			return ("Map found before all identifiers were set");
		game->map_started = 1;
		return (add_map_line(game, line));
	}
	return (parse_identifier(game, p));
}
