/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cascrizz <cascrizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:51:12 by cascrizz          #+#    #+#             */
/*   Updated: 2026/10/10 22:51:12 by cascrizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector2.h"
#include <math.h>

void	v_rotate(t_vector2 *v, double angle)
{
	double	old_x;

	old_x = v->x;
	v->x = v->x * cos(angle) - v->y * sin(angle);
	v->y = old_x * sin(angle) + v->y * cos(angle);
}
