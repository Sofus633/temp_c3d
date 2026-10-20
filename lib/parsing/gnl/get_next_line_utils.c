/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rueapen <rueapen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:39:43 by rueapen           #+#    #+#             */
/*   Updated: 2025/09/12 18:21:58 by rueapen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_read_fail(char *buffer, char *save)
{
	free(buffer);
	free(save);
	return (NULL);
}

char	*gnl_join(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (NULL);
	s3 = malloc(sizeof(char) * (gnl_len(s1) + gnl_len(s2) + 1));
	if (!s3)
		return (gnl_free(s1));
	while (s1 && s1[++j])
		s3[++i] = s1[j];
	j = -1;
	while (s2 && s2[++j])
		s3[++i] = s2[j];
	s3[++i] = '\0';
	free(s1);
	return (s3);
}

size_t	gnl_len(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	gnl_has_nl(char *s, int c)
{
	int	len;

	len = gnl_len(s);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return (1);
		len--;
	}
	return (0);
}
