/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rueapen <rueapen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:50:26 by rueapen           #+#    #+#             */
/*   Updated: 2026/10/10 22:50:26 by rueapen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	count_char(char *str, char c)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

static int	get_component(char *token)
{
	char	*trimmed;
	int		value;

	trimmed = ft_strtrim(token, " ");
	if (trimmed == NULL)
		return (-1);
	value = -1;
	if (is_number(trimmed))
		value = ft_atoi(trimmed);
	free(trimmed);
	if (value > 255)
		return (-1);
	return (value);
}

static char	*fill_color(t_color *color, char **tok)
{
	if (tok[0] == NULL || tok[1] == NULL
		|| tok[2] == NULL || tok[3] != NULL)
		return ("Invalid RGB format, expected R,G,B");
	color->r = get_component(tok[0]);
	color->g = get_component(tok[1]);
	color->b = get_component(tok[2]);
	if (color->r < 0 || color->g < 0 || color->b < 0)
		return ("RGB values must be integers between 0 and 255");
	return (NULL);
}

char	*parse_color(t_color *color, int *found, char *rest)
{
	char	**tok;
	char	*error;

	if (*found)
		return ("Duplicate color identifier");
	if (count_char(rest, ',') != 2)
		return ("Invalid RGB format, expected R,G,B");
	tok = ft_split(rest, ',');
	if (tok == NULL)
		return ("Malloc failed");
	error = fill_color(color, tok);
	free_split(tok);
	if (error == NULL)
		*found = 1;
	return (error);
}
