/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cascrizz <cascrizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:51:12 by cascrizz          #+#    #+#             */
/*   Updated: 2026/10/10 22:51:12 by cascrizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "lib/vector/vector2.h"

# define KEY_COUNT 6
# define K_W 0
# define K_S 1
# define K_A 2
# define K_D 3
# define K_LEFT 4
# define K_RIGHT 5
# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3

typedef struct s_image
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_player
{
	t_vector2	pos;
	t_vector2	dir;
	t_vector2	plane;
}	t_player;

typedef struct s_ray
{
	t_vector2	pos;
	t_vector2	dir;
	t_vector2	delta;
	t_vector2	side_dist;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
}	t_ray;

typedef struct s_hit
{
	double	dist;
	double	wall_x;
	int		side;
	int		step_x;
	int		step_y;
}	t_hit;

typedef struct s_column
{
	t_image	*tex;
	double	step;
	double	tex_pos;
	int		tex_x;
	int		line_h;
	int		start;
	int		end;
}	t_column;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_image		buffer;
	t_image		tex[4];
	t_player	player;
	int			keys[KEY_COUNT];
	long		last_time;
	int			floor_color;
	int			ceil_color;
	int			**map;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	t_color		floor;
	t_color		ceiling;
	int			no_found;
	int			so_found;
	int			we_found;
	int			ea_found;
	int			f_found;
	int			c_found;
	char		**map_lines;
	int			map_height;
	int			map_width;
	int			map_started;
	int			player_x;
	int			player_y;
	char		player_dir;
}	t_game;

#endif
