/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_liststr_manip.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:14:42 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 15:03:31 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_liststr	*lststr_create(char **cont, int len)
{
	t_liststr *new;

	if (!(new = (t_liststr *)malloc(sizeof(t_liststr))))
	{
		free(*cont);
		return (NULL);
	}
	new->content = *cont;
	new->len = len;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int			lststr_addback(t_liststr **list, char **cont, int len)
{
	t_liststr *elem;
	t_liststr *bubble;

	if (list == NULL)
	{
		free(*cont);
		return (lststr_dellall(list));
	}
	if (!(elem = lststr_create(cont, len)))
		return (lststr_dellall(list));
	if (*list == NULL)
		*list = elem;
	else
	{
		bubble = *list;
		while (bubble->next != NULL)
			bubble = bubble->next;
		bubble->next = elem;
		elem->prev = bubble;
	}
	return (1);
}

int			lststr_dellall(t_liststr **list)
{
	t_liststr *bubble;
	t_liststr *prev;

	if (list != NULL && *list != NULL)
	{
		bubble = *list;
		while (bubble->next != NULL)
			bubble = bubble->next;
		while (bubble != NULL)
		{
			prev = bubble->prev;
			free(bubble->content);
			free(bubble);
			bubble = prev;
		}
		*list = NULL;
	}
	return (-1);
}

int			lststr_len(t_liststr *list)
{
	int len;

	len = 0;
	while (list != NULL)
	{
		len += list->len;
		list = list->next;
	}
	return (len);
}

int			lststr_unload(t_liststr **list)
{
	int			len;
	char		*str;
	int			i;
	int			j;
	t_liststr	*bubble;

	if (list == NULL || *list == NULL)
		return (0);
	len = lststr_len(*list);
	bubble = *list;
	if (!(str = (char *)ft_memalloc_c(sizeof(char) * (len + 1), 0)))
		return (-1);
	i = 0;
	while (bubble != NULL)
	{
		j = 0;
		while (j < bubble->len && bubble->content != NULL)
			str[i++] = bubble->content[j++];
		bubble = bubble->next;
	}
	lststr_dellall(list);
	return (write_free(1, &str, len));
}
