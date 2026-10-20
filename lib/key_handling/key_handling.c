/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cascrizz <cascrizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:51:12 by cascrizz          #+#    #+#             */
/*   Updated: 2026/10/10 22:51:12 by cascrizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	key_index(int keycode)
{
	if (keycode == XK_w)
		return (K_W);
	if (keycode == XK_s)
		return (K_S);
	if (keycode == XK_a)
		return (K_A);
	if (keycode == XK_d)
		return (K_D);
	if (keycode == XK_Left)
		return (K_LEFT);
	if (keycode == XK_Right)
		return (K_RIGHT);
	return (-1);
}

int	key_press(int keycode, t_game *g)
{
	int	i;

	if (keycode == XK_Escape)
		clean_exit(g, 0);
	i = key_index(keycode);
	if (i >= 0 && i < KEY_COUNT)
		g->keys[i] = 1;
	return (0);
}

int	key_release(int keycode, t_game *g)
{
	int	i;

	i = key_index(keycode);
	if (i >= 0 && i < KEY_COUNT)
		g->keys[i] = 0;
	return (0);
}
