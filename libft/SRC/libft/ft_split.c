/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rueapen <rueapen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:21:52 by rueapen           #+#    #+#             */
/*   Updated: 2025/05/30 14:48:58 by rueapen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **tab, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	set_check(char c, char charset)
{
	if (c == charset)
	{
		return (1);
	}
	else
		return (0);
}

static int	ft_count_words(char *str, char set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (set_check(str[i], set) == 0)
		{
			count++;
			while (str[i] && set_check(str[i], set) == 0)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*split_words(char *str, char set)
{
	int		i;
	char	*dest;

	i = 0;
	while (str[i] && set_check(str[i], set) == 0)
	{
		i++;
	}
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (str[i] && set_check(str[i], set) == 0)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char *str, char set)
{
	int		count;
	char	**tab;

	count = ft_count_words(str, set);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!str || !tab)
		return (NULL);
	int (i) = 0;
	int (j) = 0;
	while (str[i])
	{
		if (set_check(str[i], set) == 0)
		{
			tab[j] = split_words(&str[i], set);
			if (!tab[j])
				return (ft_free(tab, j));
			while (str[i] && set_check(str[i], set) == 0)
				i++;
			j++;
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (tab);
}

/*   int	main(void)
{
	int i = 0;
	char str[] = "tripouille";
	char charset = 0;
	char **split_words = ft_split(str, charset);
	while (i < ft_count_words(str, charset))
	{
		printf("%s\n", split_words[i]);
		i++;
	}
	free(split_words);
	return (0);
}  */