/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynini <ynini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:52:08 by ynini             #+#    #+#             */
/*   Updated: 2025/02/26 04:59:30 by ynini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	count_word(char const *s, char c)
{
	size_t	i;
	size_t	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			word++;
		while (s[i] != c && s[i])
			i++;
	}
	return (word);
}

void	free_arr(char **arr, int len)
{
	int	i;

	i = len;
	while (i >= 0)
		free(arr[i--]);
	free (arr);
}

static char	**fill_arr(char **arr, char const *s, char c, int i)
{
	int	j;
	int	start;

	j = 0;
	while (s[j])
	{
		while (s[j] == c && s[j])
			j++;
		if (s[j])
		{
			start = j;
			while (s[j] && s[j] != c)
				j++;
			arr[i] = ft_substr(s, start, j - start);
			if (arr[i] == NULL)
			{
				free_arr(arr, i - 1);
				return (NULL);
			}
			i++;
		}
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		word_count;

	if (s == NULL)
		return (NULL);
	word_count = count_word(s, c);
	arr = malloc(sizeof(char *) * (word_count + 1));
	if (!arr)
		return (NULL);
	if (word_count == 0)
	{
		arr[0] = NULL;
		return (arr);
	}
	return (fill_arr(arr, s, c, 0));
}
