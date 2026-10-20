/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rueapen <rueapen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:50:26 by rueapen           #+#    #+#             */
/*   Updated: 2026/10/10 22:50:26 by rueapen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*check_texture(char **slot)
{
	int		fd;
	char	c;

	if (find_char(*slot, ' ') != NULL)
		return ("Texture path has extra tokens");
	fd = open(*slot, O_RDONLY);
	if (fd == -1)
		return ("Cannot open texture file");
	if (read(fd, &c, 0) == -1)
	{
		close(fd);
		return ("Cannot read texture file");
	}
	close(fd);
	return (NULL);
}

static char	*set_texture(char **slot, int *found, char *rest)
{
	char	*error;

	if (*found)
		return ("Duplicate texture identifier");
	*slot = ft_strtrim(rest, " ");
	if (*slot == NULL)
		return ("Malloc failed");
	error = check_texture(slot);
	if (error == NULL)
		*found = 1;
	return (error);
}

char	*parse_texture(t_game *game, char *id, char *rest)
{
	if (ft_strncmp(id, "NO", 3) == 0)
		return (set_texture(&game->no_texture, &game->no_found, rest));
	if (ft_strncmp(id, "SO", 3) == 0)
		return (set_texture(&game->so_texture, &game->so_found, rest));
	if (ft_strncmp(id, "WE", 3) == 0)
		return (set_texture(&game->we_texture, &game->we_found, rest));
	if (ft_strncmp(id, "EA", 3) == 0)
		return (set_texture(&game->ea_texture, &game->ea_found, rest));
	return ("Unknown identifier or invalid line");
}
