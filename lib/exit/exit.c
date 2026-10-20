/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cascrizz <cascrizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:51:12 by cascrizz          #+#    #+#             */
/*   Updated: 2026/10/10 22:51:12 by cascrizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	destroy_images(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g->tex[i].img)
			mlx_destroy_image(g->mlx, g->tex[i].img);
		g->tex[i].img = NULL;
		i++;
	}
	if (g->buffer.img)
		mlx_destroy_image(g->mlx, g->buffer.img);
	g->buffer.img = NULL;
}

void	clean_exit(t_game *g, int code)
{
	if (g->mlx)
	{
		destroy_images(g);
		if (g->win)
			mlx_destroy_window(g->mlx, g->win);
		g->win = NULL;
		mlx_destroy_display(g->mlx);
		free(g->mlx);
		g->mlx = NULL;
	}
	free_parsing(g);
	exit(code);
}

void	engine_error(t_game *g, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	clean_exit(g, 1);
}

int	close_window(t_game *g)
{
	clean_exit(g, 0);
	return (0);
}
