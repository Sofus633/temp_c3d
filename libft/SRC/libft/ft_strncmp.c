/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rueapen <rueapen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:53:36 by rueapen           #+#    #+#             */
/*   Updated: 2025/05/19 20:24:05 by rueapen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/* #include <stdio.h>

int	main(void)
{
	char s[] = "ABCD";
	char s1[] = "ABCE";

	printf("%d\n", ft_strncmp(s, s1, 5));
	printf("%d\n", strncmp(s, s1, 5));
		printf("%d\n", ft_strncmp(s, s1, 3));
	printf("%d\n", strncmp(s, s1, 3));
} */
