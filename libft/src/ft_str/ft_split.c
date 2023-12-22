/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <jmorcom-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:36:03 by jmorcom-          #+#    #+#             */
/*   Updated: 2022/10/19 10:35:16 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/libft.h"

int	ft_checksep(char str, char c)
{
	int	i;

	if (!str || str == c)
		i = 1;
	else
		i = 0;
	return (i);
}

int	ft_wordcount(char *str, char c)
{
	int	count;
	int	state;

	count = 0;
	state = 1;
	while (*str)
	{
		if (ft_checksep(*str, c) && state == 0)
			state = 1;
		if (state == 1 && !ft_checksep(*str, c))
		{
			state = 0;
			count++;
		}
		str++;
	}
	return (count);
}

char	*ft_word(char *str, char c)
{
	char	*strs;
	int		size;
	int		i;
	int		j;

	size = 0;
	i = 0;
	j = 0;
	while (!ft_checksep(str[i], c) && str[i])
	{
		size++;
		i++;
	}
	strs = malloc(sizeof(char) * size + 1);
	if (!strs)
		exit(0);
	while (i > 0)
	{
		strs[j] = *str;
		str++;
		j++;
		i--;
	}
	strs[j] = '\0';
	return (strs);
}

char	**ft_split(char *str, char c)
{
	int		size;
	char	**tab;
	int		i;

	if (!str)
		return ((void *) 0);
	size = ft_wordcount(str, c);
	i = 0;
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		exit(0);
	while (i < size)
	{
		while (ft_checksep(*str, c))
			str++;
		tab[i] = ft_word(str, c);
		while (*str && !ft_checksep(*str, c))
			str++;
		i++;
	}
	tab[i] = 0;
	return (tab);
}
