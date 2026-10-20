/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cascrizz <cascrizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:51:12 by cascrizz          #+#    #+#             */
/*   Updated: 2026/10/10 22:51:12 by cascrizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_wall(t_game *g, double x, double y)
{
	int	ix;
	int	iy;

	if (!g->map || x < 0 || y < 0)
		return (1);
	ix = (int)x;
	iy = (int)y;
	if (ix >= g->map_width || iy >= g->map_height)
		return (1);
	return (g->map[iy][ix] != 0);
}

static int	is_blocked(t_game *g, double x, double y)
{
	if (is_wall(g, x - MARGIN, y - MARGIN))
		return (1);
	if (is_wall(g, x + MARGIN, y - MARGIN))
		return (1);
	if (is_wall(g, x - MARGIN, y + MARGIN))
		return (1);
	if (is_wall(g, x + MARGIN, y + MARGIN))
		return (1);
	return (0);
}

void	move_player(t_game *g, double dx, double dy)
{
	t_vector2	*p;

	p = &g->player.pos;
	if (!is_blocked(g, p->x + dx, p->y))
		p->x += dx;
	if (!is_blocked(g, p->x, p->y + dy))
		p->y += dy;
}
