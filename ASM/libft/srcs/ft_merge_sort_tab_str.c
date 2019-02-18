/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sort_tab_str.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 19:14:18 by erli              #+#    #+#             */
/*   Updated: 2019/01/21 13:25:26 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_sort_tab_3(char **tab)
{
	if (ft_strcmp(tab[0], tab[1]) < 0 && ft_strcmp(tab[0], tab[2]) < 0)
	{
		if (ft_strcmp(tab[2], tab[1]) < 0)
			ft_swap_str(tab + 1, tab + 2);
	}
	else if (ft_strcmp(tab[1], tab[0]) < 0 && ft_strcmp(tab[1], tab[2]) < 0)
	{
		if (ft_strcmp(tab[0], tab[2]) > 0)
		{
			ft_swap_str(tab, tab + 1);
			ft_swap_str(tab + 1, tab + 2);
		}
		else
			ft_swap_str(tab + 1, tab);
	}
	else if (ft_strcmp(tab[0], tab[1]) > 0)
		ft_swap_str(tab + 2, tab);
	else
	{
		ft_swap_str(tab + 1, tab);
		ft_swap_str(tab, tab + 2);
	}
}

static	char	**ft_small_sort(char **tab, int len)
{
	if (len == 1)
		return (tab);
	else if (len == 2)
	{
		if (ft_strcmp(tab[0], tab[1]) > 0)
			ft_swap_str(tab, tab + 1);
		return (tab);
	}
	else
		ft_sort_tab_3(tab);
	return (tab);
}

static	char	**ft_merge(char **tab1, int len1, char **tab2, int len2)
{
	char	*tab3[len1];
	int		i;
	int		i1;
	int		i2;

	i = 0;
	while (i < len1)
	{
		tab3[i] = tab1[i];
		i++;
	}
	i = 0;
	i1 = 0;
	i2 = 0;
	while (i < len1 + len2)
	{
		if (i1 == len1)
			tab1[i++] = tab2[i2++];
		else if ((i2 == len2) || (ft_strcmp(tab3[i1], tab2[i2]) <= 0))
			tab1[i++] = tab3[i1++];
		else
			tab1[i++] = tab2[i2++];
	}
	return (tab1);
}

static	char	**ft_merge_sort(char **tab, int len)
{
	char	**tab1;
	char	**tab2;
	int		len1;
	int		len2;

	if (len <= 3)
		return (ft_small_sort(tab, len));
	len1 = len / 2;
	len2 = len - len1;
	tab1 = ft_merge_sort(tab, len1);
	tab2 = ft_merge_sort(tab + len1, len2);
	return (ft_merge(tab1, len1, tab2, len2));
}

void			ft_merge_sort_tab_str(char **src, char **dest, size_t len)
{
	char	**tab;
	size_t	i;

	if (len == 0)
		return ;
	if (src != dest)
	{
		i = 0;
		while (i < len)
		{
			dest[i] = src[i];
			i++;
		}
	}
	tab = dest;
	ft_merge_sort(tab, len);
}
