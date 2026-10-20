/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rueapen <rueapen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:48:43 by rueapen           #+#    #+#             */
/*   Updated: 2025/05/30 15:00:08 by rueapen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_decimals(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			i;
	char		*str;
	int long	nb;

	nb = (long)n;
	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	i = count_decimals(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	str[i--] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		str[i--] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
/*
int	main(void)
{
	int	a = 1234;
	int b = 0;
	int c = -2147483648;
	int d = -2;

	printf("%s\n %s\n %s\n %s\n", ft_itoa(a), ft_itoa(b), ft_itoa(c),
		ft_itoa(d));
	char *res = ft_itoa(0);
	printf("test : %s", res);
	free(res);
} */