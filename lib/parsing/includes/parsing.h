/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rueapen <rueapen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:50:26 by rueapen           #+#    #+#             */
/*   Updated: 2026/10/10 22:50:26 by rueapen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../../game.h"
# include "../gnl/get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void	init_map(t_game *game, char *path);
void	build_map_grid(t_game *game);
void	free_parsing(t_game *game);
void	parse_file(t_game *game, char *filename);
char	*parse_line(t_game *game, char *line);
char	*parse_color(t_color *color, int *found, char *rest);
char	*parse_texture(t_game *game, char *id, char *rest);
char	*add_map_line(t_game *game, char *line);
char	*find_player(t_game *game);
char	*check_map_walls(t_game *game);
char	*check_identifiers(t_game *game);
char	*validate_map(t_game *game);
int		has_cub_extension(char *path);
int		is_map_line(char *line);
int		all_ids_found(t_game *game);
int		is_player(char c);
int		is_number(char *str);
char	*find_char(char *str, char c);
char	*skip_spaces(char *str);
void	strip_eol(char *str);
void	free_split(char **split);
void	error_exit(t_game *game, char *message);

#endif
