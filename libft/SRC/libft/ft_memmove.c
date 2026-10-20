/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rueapen <rueapen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:08:35 by rueapen           #+#    #+#             */
/*   Updated: 2025/05/30 15:11:37 by rueapen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t					i;
	unsigned char			*tdest;
	const unsigned char		*tsrc;

	if (!dst && !src)
		return (NULL);
	tdest = (unsigned char *)dst;
	tsrc = (const unsigned char *)src;
	i = 0;
	if (tdest > tsrc)
	{
		while (len-- > 0)
		{
			tdest[len] = tsrc[len];
		}
	}
	else
	{
		while (i < len)
		{
			tdest[i] = tsrc[i];
			i++;
		}
	}
	return (dst);
}
