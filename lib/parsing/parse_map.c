/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rueapen <rueapen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:50:26 by rueapen           #+#    #+#             */
/*   Updated: 2026/10/10 22:50:26 by rueapen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

char	*add_map_line(t_game *game, char *line)
{
	char	**new_map;
	int		i;

	new_map = ft_calloc(game->map_height + 2, sizeof(char *));
	if (new_map == NULL)
		return ("Malloc failed");
	i = 0;
	while (i < game->map_height)
	{
		new_map[i] = game->map_lines[i];
		i++;
	}
	new_map[i] = ft_strdup(line);
	if (new_map[i] == NULL)
	{
		free(new_map);
		return ("Malloc failed");
	}
	free(game->map_lines);
	game->map_lines = new_map;
	game->map_height++;
	if ((int)ft_strlen(line) > game->map_width)
		game->map_width = ft_strlen(line);
	return (NULL);
}

static int	row_players(t_game *game, int y)
{
	int	x;
	int	count;

	x = 0;
	count = 0;
	while (game->map_lines[y][x] != '\0')
	{
		if (is_player(game->map_lines[y][x]))
		{
			count++;
			game->player_x = x;
			game->player_y = y;
			game->player_dir = game->map_lines[y][x];
		}
		x++;
	}
	return (count);
}

char	*find_player(t_game *game)
{
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (y < game->map_height)
	{
		count += row_players(game, y);
		y++;
	}
	if (count == 0)
		return ("No player start position in map");
	if (count > 1)
		return ("More than one player start position in map");
	return (NULL);
}
