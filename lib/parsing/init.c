/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rueapen <rueapen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:50:26 by rueapen           #+#    #+#             */
/*   Updated: 2026/10/10 22:50:26 by rueapen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	init_defaults(t_game *game)
{
	game->floor.r = -1;
	game->floor.g = -1;
	game->floor.b = -1;
	game->ceiling.r = -1;
	game->ceiling.g = -1;
	game->ceiling.b = -1;
	game->no_found = 0;
	game->so_found = 0;
	game->we_found = 0;
	game->ea_found = 0;
	game->f_found = 0;
	game->c_found = 0;
	game->map_lines = NULL;
	game->map = NULL;
	game->map_height = 0;
	game->map_width = 0;
	game->map_started = 0;
	game->player_x = -1;
	game->player_y = -1;
	game->player_dir = '\0';
}

static void	fill_row(t_game *game, int y)
{
	int	x;
	int	len;

	len = ft_strlen(game->map_lines[y]);
	x = 0;
	while (x < game->map_width)
	{
		game->map[y][x] = 1;
		if (x < len && (game->map_lines[y][x] == '0'
			|| is_player(game->map_lines[y][x])))
			game->map[y][x] = 0;
		x++;
	}
}

void	build_map_grid(t_game *game)
{
	int	y;

	game->map = ft_calloc(game->map_height, sizeof(int *));
	if (game->map == NULL)
		error_exit(game, "Malloc failed");
	y = 0;
	while (y < game->map_height)
	{
		game->map[y] = ft_calloc(game->map_width, sizeof(int));
		if (game->map[y] == NULL)
			error_exit(game, "Malloc failed");
		fill_row(game, y);
		y++;
	}
}

void	init_map(t_game *game, char *path)
{
	init_defaults(game);
	if (!has_cub_extension(path))
		error_exit(game, "The map file must have the .cub extension");
	parse_file(game, path);
	build_map_grid(game);
}
