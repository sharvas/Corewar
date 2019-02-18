/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:29:01 by erli              #+#    #+#             */
/*   Updated: 2018/12/05 15:51:49 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

static	size_t	count_words(const char *src, char c)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (src[i] == c && src[i] != '\0')
		i++;
	while (src[i] != c && src[i] != '\0')
	{
		n++;
		while (src[i] != c && src[i] != '\0')
			i++;
		while (src[i] == c && src[i] != '\0')
			i++;
	}
	return (n);
}

static	void	count_words_len(const char *src, char c, size_t *tab)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (src[i] == c && src[i] != '\0')
		i++;
	while (src[i] != c && src[i] != '\0')
	{
		tab[n] = 0;
		while (src[i] != c && src[i] != '\0')
		{
			i++;
			tab[n]++;
		}
		n++;
		while (src[i] == c && src[i] != '\0')
			i++;
	}
}

static	size_t	fill_words(const char *src, char c, size_t *tab, char **split)
{
	size_t	i;
	size_t	n;
	size_t	j;

	i = 0;
	n = 0;
	while (src[i] == c && src[i] != '\0')
		i++;
	while (src[i] != c && src[i] != '\0')
	{
		j = 0;
		if (!(split[n] = (char *)malloc(sizeof(char) * (tab[n] + 1))))
			return (0);
		while (src[i] != c && src[i] != '\0')
		{
			split[n][j] = src[i];
			i++;
			j++;
		}
		split[n][j] = '\0';
		n++;
		while (src[i] == c && src[i] != '\0')
			i++;
	}
	return (1);
}

char			**ft_strsplit(const char *src, char c)
{
	size_t	n_words;
	size_t	i;
	size_t	*words_len;
	char	**split;

	if (src == NULL)
		return (NULL);
	n_words = count_words(src, c);
	if (!(words_len = (size_t *)malloc(sizeof(size_t) * n_words)))
		return (NULL);
	count_words_len(src, c, words_len);
	if (!(split = (char **)malloc(sizeof(char *) * (n_words + 1))))
		return (NULL);
	i = fill_words(src, c, words_len, split);
	if (i == 0)
		return (NULL);
	split[n_words] = 0;
	free(words_len);
	return (split);
}
