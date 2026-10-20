/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rueapen <rueapen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:50:26 by rueapen           #+#    #+#             */
/*   Updated: 2026/10/10 22:50:26 by rueapen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_cell_safe(t_game *game, int y, int x)
{
	if (y < 0 || y >= game->map_height)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(game->map_lines[y]))
		return (0);
	if (game->map_lines[y][x] == ' ')
		return (0);
	return (1);
}

static int	cell_leaks(t_game *game, int y, int x)
{
	char	c;

	c = game->map_lines[y][x];
	if (c != '0' && !is_player(c))
		return (0);
	if (!is_cell_safe(game, y - 1, x) || !is_cell_safe(game, y + 1, x)
		|| !is_cell_safe(game, y, x - 1) || !is_cell_safe(game, y, x + 1))
		return (1);
	return (0);
}

char	*check_map_walls(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map_lines[y][x] != '\0')
		{
			if (cell_leaks(game, y, x))
				return ("Map is not closed by walls");
			x++;
		}
		y++;
	}
	return (NULL);
}
