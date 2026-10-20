/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cascrizz <cascrizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:51:12 by cascrizz          #+#    #+#             */
/*   Updated: 2026/10/10 22:51:12 by cascrizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

long	get_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000L + tv.tv_usec);
}

int	game_loop(t_game *g)
{
	long	now;
	double	dt;

	now = get_time_us();
	dt = (now - g->last_time) / 1000000.0;
	g->last_time = now;
	if (dt < 0 || dt > MAX_DT)
		dt = MAX_DT;
	update_player(g, dt);
	render_frame(g);
	mlx_put_image_to_window(g->mlx, g->win, g->buffer.img, 0, 0);
	return (0);
}
