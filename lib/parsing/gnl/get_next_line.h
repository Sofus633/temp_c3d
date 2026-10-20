/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rueapen <rueapen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:04:50 by rueapen           #+#    #+#             */
/*   Updated: 2025/09/12 18:16:32 by rueapen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		gnl_has_nl(char *s, int c);
char	*gnl_read_fail(char *buffer, char *save);
char	*gnl_free(char *str);
char	*gnl_cut_line(char *stash);
char	*gnl_rest(char *stash);
char	*gnl_join(char *s1, char *s2);
char	*read_line(int fd, char *save);
char	*get_next_line(int fd);
size_t	gnl_len(const char *str);

#endif
