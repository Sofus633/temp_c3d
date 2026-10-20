/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cascrizz <cascrizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:51:12 by cascrizz          #+#    #+#             */
/*   Updated: 2026/10/10 22:51:12 by cascrizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	set_vectors(t_player *p, double dx, double dy)
{
	p->dir.x = dx;
	p->dir.y = dy;
	p->plane.x = -dy * PLANE_LEN;
	p->plane.y = dx * PLANE_LEN;
}

void	init_player(t_game *g)
{
	g->player.pos.x = g->player_x + 0.5;
	g->player.pos.y = g->player_y + 0.5;
	if (g->player_dir == 'N')
		set_vectors(&g->player, 0, -1);
	else if (g->player_dir == 'S')
		set_vectors(&g->player, 0, 1);
	else if (g->player_dir == 'E')
		set_vectors(&g->player, 1, 0);
	else
		set_vectors(&g->player, -1, 0);
}

static void	rotate_player(t_game *g, double angle)
{
	v_rotate(&g->player.dir, angle);
	v_rotate(&g->player.plane, angle);
}

void	update_player(t_game *g, double dt)
{
	double		speed;
	int			fwd;
	int			side;
	t_vector2	d;

	fwd = g->keys[K_W] - g->keys[K_S];
	side = g->keys[K_D] - g->keys[K_A];
	speed = MOVE_SPEED * dt;
	if (fwd && side)
		speed *= M_SQRT1_2;
	d = g->player.dir;
	if (fwd || side)
		move_player(g, (d.x * fwd - d.y * side) * speed,
			(d.y * fwd + d.x * side) * speed);
	if (g->keys[K_RIGHT] != g->keys[K_LEFT])
		rotate_player(g, (g->keys[K_RIGHT] - g->keys[K_LEFT])
			* ROT_SPEED * dt);
}
