/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sort_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 19:14:18 by erli              #+#    #+#             */
/*   Updated: 2019/01/16 15:38:40 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_sort_tab_3(int *tab)
{
	if (tab[0] < tab[1] && tab[0] < tab[2])
	{
		if (tab[2] < tab[1])
			ft_swap_int(tab + 1, tab + 2);
	}
	else if (tab[1] < tab[0] && tab[1] < tab[2])
	{
		if (tab[0] > tab[2])
		{
			ft_swap_int(tab, tab + 1);
			ft_swap_int(tab + 1, tab + 2);
		}
		else
			ft_swap_int(tab + 1, tab);
	}
	else if (tab[0] > tab[1])
		ft_swap_int(tab + 2, tab);
	else
	{
		ft_swap_int(tab + 1, tab);
		ft_swap_int(tab, tab + 2);
	}
}

static	int		*ft_small_sort(int *tab, int len)
{
	if (len == 1)
		return (tab);
	else if (len == 2)
	{
		if (tab[0] > tab[1])
			ft_swap_int(tab, tab + 1);
		return (tab);
	}
	else
		ft_sort_tab_3(tab);
	return (tab);
}

static	int		*ft_merge(int *tab1, int len1, int *tab2, int len2)
{
	int	tab3[len1];
	int i;
	int i1;
	int i2;

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
		else if ((i2 == len2) || (tab3[i1] <= tab2[i2]))
			tab1[i++] = tab3[i1++];
		else
			tab1[i++] = tab2[i2++];
	}
	return (tab1);
}

static	int		*ft_merge_sort(int *tab, int len)
{
	int *tab1;
	int	*tab2;
	int len1;
	int len2;

	if (len <= 3)
		return (ft_small_sort(tab, len));
	len1 = len / 2;
	len2 = len - len1;
	tab1 = ft_merge_sort(tab, len1);
	tab2 = ft_merge_sort(tab + len1, len2);
	return (ft_merge(tab1, len1, tab2, len2));
}

void			ft_merge_sort_tab(int *src, int *dest, size_t len)
{
	int *tab;

	if (len == 0)
		return ;
	if (src != dest)
		ft_memmove(dest, src, sizeof(int) * len);
	tab = dest;
	ft_merge_sort(tab, len);
}
