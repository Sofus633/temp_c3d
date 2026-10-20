/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rueapen <rueapen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:50:26 by rueapen           #+#    #+#             */
/*   Updated: 2026/10/10 22:50:26 by rueapen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	has_cub_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5 || path[len - 5] == '/')
		return (0);
	return (ft_strncmp(path + len - 4, ".cub", 5) == 0);
}

char	*check_identifiers(t_game *game)
{
	if (!game->no_found)
		return ("Missing NO identifier");
	if (!game->so_found)
		return ("Missing SO identifier");
	if (!game->we_found)
		return ("Missing WE identifier");
	if (!game->ea_found)
		return ("Missing EA identifier");
	if (!game->f_found)
		return ("Missing F identifier");
	if (!game->c_found)
		return ("Missing C identifier");
	return (NULL);
}

char	*validate_map(t_game *game)
{
	char	*error;

	if (game->map_height == 0)
		return ("No map found in file");
	error = find_player(game);
	if (error != NULL)
		return (error);
	return (check_map_walls(game));
}
