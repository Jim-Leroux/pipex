/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:48:22 by jileroux          #+#    #+#             */
/*   Updated: 2022/10/11 15:52:32 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != 0)
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	index;

	index = 0;
	while (src[index] && src[index] != '\n')
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = src[index];
	index++;
	dest[index] = '\0';
	return (dest);
}

char	*ft_strcpy_after_backslash_n(char *dest, const char *src)
{
	int	index_1;
	int	index_2;

	index_1 = 0;
	index_2 = 0;
	while (src[index_1] && src[index_1] != '\n')
		index_1++;
	if (src[index_1] == '\n')
		index_1++;
	while (src[index_1])
	{
		dest[index_2] = src[index_1];
		index_1++;
		index_2++;
	}
	dest[index_2] = '\0';
	return (dest);
}

char	*ft_strjoin(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2)) + 1);
	if (new_line == NULL)
		return (NULL);
	while (str1 && str1[i])
	{
		new_line[i] = str1[i];
		i++;
	}
	while (str2 && str2[j])
	{
		new_line[i + j] = str2[j];
		j++;
	}
	new_line[i + j] = '\0';
	if (str1)
		free(str1);
	return (new_line);
}
