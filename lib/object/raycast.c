/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cascrizz <cascrizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:51:12 by cascrizz          #+#    #+#             */
/*   Updated: 2026/10/10 22:51:12 by cascrizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static double	ray_delta(double d)
{
	if (d == 0)
		return (1e30);
	return (fabs(1 / d));
}

static void	init_ray(t_ray *r, t_game *g, double cam)
{
	r->pos = g->player.pos;
	r->dir.x = g->player.dir.x + g->player.plane.x * cam;
	r->dir.y = g->player.dir.y + g->player.plane.y * cam;
	r->map_x = (int)r->pos.x;
	r->map_y = (int)r->pos.y;
	r->delta.x = ray_delta(r->dir.x);
	r->delta.y = ray_delta(r->dir.y);
	r->step_x = 1;
	r->step_y = 1;
	r->side_dist.x = (r->map_x + 1.0 - r->pos.x) * r->delta.x;
	r->side_dist.y = (r->map_y + 1.0 - r->pos.y) * r->delta.y;
	if (r->dir.x < 0)
	{
		r->step_x = -1;
		r->side_dist.x = (r->pos.x - r->map_x) * r->delta.x;
	}
	if (r->dir.y < 0)
	{
		r->step_y = -1;
		r->side_dist.y = (r->pos.y - r->map_y) * r->delta.y;
	}
	r->side = 0;
}

static void	run_dda(t_ray *r, t_game *g)
{
	while (!is_wall(g, r->map_x, r->map_y))
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta.x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist.y += r->delta.y;
			r->map_y += r->step_y;
			r->side = 1;
		}
	}
}

t_hit	cast_ray(t_game *g, int x)
{
	t_ray	r;
	t_hit	h;

	init_ray(&r, g, 2.0 * x / (double)WIDTH - 1.0);
	run_dda(&r, g);
	h.side = r.side;
	h.step_x = r.step_x;
	h.step_y = r.step_y;
	if (r.side == 0)
	{
		h.dist = r.side_dist.x - r.delta.x;
		h.wall_x = r.pos.y + h.dist * r.dir.y;
	}
	else
	{
		h.dist = r.side_dist.y - r.delta.y;
		h.wall_x = r.pos.x + h.dist * r.dir.x;
	}
	h.wall_x -= floor(h.wall_x);
	return (h);
}
