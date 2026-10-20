/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cascrizz <cascrizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:51:12 by cascrizz          #+#    #+#             */
/*   Updated: 2026/10/10 22:51:12 by cascrizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <X11/keysym.h>
# include "mlx.h"
# include "libft.h"
# include "game.h"
# include "lib/parsing/includes/parsing.h"

# define WIDTH 1024
# define HEIGHT 768
# define MOVE_SPEED 3.0
# define ROT_SPEED 2.5
# define MARGIN 0.2
# define PLANE_LEN 0.66
# define MAX_DT 0.05

void			clean_exit(t_game *g, int code);
void			engine_error(t_game *g, char *msg);
int				close_window(t_game *g);
void			put_pixel(t_image *img, int x, int y, int color);
unsigned int	tex_pixel(t_image *tex, int x, int y);
int				rgb_to_int(t_color c);
void			load_textures(t_game *g);
int				key_press(int keycode, t_game *g);
int				key_release(int keycode, t_game *g);
void			init_player(t_game *g);
void			update_player(t_game *g, double dt);
int				is_wall(t_game *g, double x, double y);
void			move_player(t_game *g, double dx, double dy);
t_hit			cast_ray(t_game *g, int x);
void			render_frame(t_game *g);
long			get_time_us(void);
int				game_loop(t_game *g);

#endif
