/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cascrizz <cascrizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:51:12 by cascrizz          #+#    #+#             */
/*   Updated: 2026/10/10 22:51:12 by cascrizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	texture_error(t_game *g, char *path)
{
	ft_putstr_fd("Error\nCannot load texture: ", 2);
	if (path)
		ft_putstr_fd(path, 2);
	ft_putstr_fd("\n", 2);
	clean_exit(g, 1);
}

static void	load_texture(t_game *g, t_image *t, char *path)
{
	if (!path)
		texture_error(g, path);
	t->img = mlx_xpm_file_to_image(g->mlx, path, &t->width, &t->height);
	if (!t->img || t->width <= 0 || t->height <= 0)
		texture_error(g, path);
	t->data = mlx_get_data_addr(t->img, &t->bpp, &t->size_line, &t->endian);
	if (!t->data)
		texture_error(g, path);
}

void	load_textures(t_game *g)
{
	load_texture(g, &g->tex[TEX_NO], g->no_texture);
	load_texture(g, &g->tex[TEX_SO], g->so_texture);
	load_texture(g, &g->tex[TEX_WE], g->we_texture);
	load_texture(g, &g->tex[TEX_EA], g->ea_texture);
}
