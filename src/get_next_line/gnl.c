/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:48:25 by jileroux          #+#    #+#             */
/*   Updated: 2022/12/14 14:28:36 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd, int to_free)
{
	static char	*str_static = NULL;
	char		*str_temporary;

	if (to_free == 0)
	{
		free(str_static);
		return (NULL);
	}
	if (fd < 0 || read(fd, &str_temporary, 0) < 0 || BUFFER_SIZE < 1)
		return (NULL);
	str_static = ft_read_line(fd, str_static);
	if (str_static == NULL)
		return (NULL);
	str_temporary = ft_get_line(str_static);
	if (str_temporary == NULL)
		return (NULL);
	str_static = ft_save_line(str_static);
	return (str_temporary);
}

char	*ft_read_line(int fd, char *str_static)
{
	int		end_of_file;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	end_of_file = 0;
	while (ft_strchr(str_static))
	{
		end_of_file = read(fd, buffer, BUFFER_SIZE);
		if (end_of_file == 0)
		{
			if (str_static && str_static[0] != '\0')
				break ;
			free(str_static);
			free(buffer);
			return (NULL);
		}
		buffer[end_of_file] = '\0';
		str_static = ft_strjoin(str_static, buffer);
	}
	free(buffer);
	return (str_static);
}

char	*ft_get_line(char *str)
{
	int		index;
	char	*readed_line;

	readed_line = NULL;
	index = 0;
	while (str[index] && str[index] != '\n')
		index++;
	readed_line = malloc(sizeof(char) * index + 2);
	if (readed_line == NULL)
		return (NULL);
	readed_line = ft_strcpy(readed_line, str);
	return (readed_line);
}

char	*ft_save_line(char *str)
{
	int		index;
	int		str_length;
	char	*saved_line;

	index = 0;
	saved_line = NULL;
	str_length = ft_strlen(str);
	while (str[index] && str[index] != '\n')
		index++;
	str_length = str_length - index;
	saved_line = malloc(sizeof(char) * str_length + 2);
	if (saved_line == NULL)
		return (NULL);
	saved_line = ft_strcpy_after_backslash_n(saved_line, str);
	free(str);
	return (saved_line);
}
