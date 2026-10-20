/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cascrizz <cascrizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:51:12 by cascrizz          #+#    #+#             */
/*   Updated: 2026/10/10 22:51:12 by cascrizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static t_image	*pick_texture(t_game *g, t_hit *h)
{
	if (h->side == 1 && h->step_y < 0)
		return (&g->tex[TEX_NO]);
	if (h->side == 1)
		return (&g->tex[TEX_SO]);
	if (h->step_x > 0)
		return (&g->tex[TEX_EA]);
	return (&g->tex[TEX_WE]);
}

static int	compute_tex_x(t_hit *h, t_image *tex)
{
	int	tx;

	tx = (int)(h->wall_x * tex->width);
	if (tx >= tex->width)
		tx = tex->width - 1;
	if (tx < 0)
		tx = 0;
	if ((h->side == 0 && h->step_x < 0) || (h->side == 1 && h->step_y > 0))
		tx = tex->width - tx - 1;
	return (tx);
}

static void	setup_column(t_game *g, t_hit *h, t_column *c)
{
	if (h->dist < 1e-4)
		h->dist = 1e-4;
	c->line_h = (int)(HEIGHT / h->dist);
	if (c->line_h < 1)
		c->line_h = 1;
	c->start = HEIGHT / 2 - c->line_h / 2;
	c->end = c->start + c->line_h;
	c->tex = pick_texture(g, h);
	c->tex_x = compute_tex_x(h, c->tex);
	c->step = (double)c->tex->height / c->line_h;
	c->tex_pos = 0;
	if (c->start < 0)
	{
		c->tex_pos = -c->start * c->step;
		c->start = 0;
	}
	if (c->end > HEIGHT)
		c->end = HEIGHT;
}

static void	draw_column(t_game *g, int x, t_column *c)
{
	int	y;

	y = 0;
	while (y < c->start)
	{
		put_pixel(&g->buffer, x, y, g->ceil_color);
		y++;
	}
	while (y < c->end)
	{
		put_pixel(&g->buffer, x, y,
			tex_pixel(c->tex, c->tex_x, (int)c->tex_pos));
		c->tex_pos += c->step;
		y++;
	}
	while (y < HEIGHT)
	{
		put_pixel(&g->buffer, x, y, g->floor_color);
		y++;
	}
}

void	render_frame(t_game *g)
{
	int			x;
	t_hit		h;
	t_column	c;

	x = 0;
	while (x < WIDTH)
	{
		h = cast_ray(g, x);
		setup_column(g, &h, &c);
		draw_column(g, x, &c);
		x++;
	}
}
