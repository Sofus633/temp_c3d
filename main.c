/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cascrizz <cascrizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:51:12 by cascrizz          #+#    #+#             */
/*   Updated: 2026/10/10 22:51:12 by cascrizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_mlx(t_game *g)
{
	t_image	*b;

	g->mlx = mlx_init();
	if (!g->mlx)
		engine_error(g, "mlx_init failed");
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "cub3D");
	if (!g->win)
		engine_error(g, "Cannot create window");
	b = &g->buffer;
	b->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!b->img)
		engine_error(g, "Cannot create image");
	b->width = WIDTH;
	b->height = HEIGHT;
	b->data = mlx_get_data_addr(b->img, &b->bpp, &b->size_line, &b->endian);
	if (!b->data)
		engine_error(g, "Cannot access image data");
}

static void	init_hooks(t_game *g)
{
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, 17, 0, close_window, g);
	mlx_loop_hook(g->mlx, game_loop, g);
	g->last_time = get_time_us();
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3D <map.cub>\n", 2);
		return (1);
	}
	ft_bzero(&game, sizeof(game));
	init_map(&game, argv[1]);
	game.floor_color = rgb_to_int(game.floor);
	game.ceil_color = rgb_to_int(game.ceiling);
	init_mlx(&game);
	load_textures(&game);
	init_player(&game);
	init_hooks(&game);
	mlx_loop(game.mlx);
	clean_exit(&game, 0);
	return (0);
}
