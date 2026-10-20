/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rueapen <rueapen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:00:26 by rueapen           #+#    #+#             */
/*   Updated: 2025/05/30 15:54:08 by rueapen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	trim_set(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		start;
	int		end;
	char	*str;
	int		i;

	if (!s1 || !set)
		return (0);
	start = 0;
	while (s1[start] && (trim_set(s1[start], (char *)set)) == 1)
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= start && (trim_set(s1[end], (char *)set)) == 1)
		end--;
	str = (char *)malloc(sizeof(char) * (end - start + 2));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (start <= end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}

/* int		main(void)
{
	char *str = "*****test*****";
	char	*set = "* ";
	printf("%s", ft_strtrim(str, set));
} */