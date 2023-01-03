/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:11:28 by jileroux          #+#    #+#             */
/*   Updated: 2022/12/14 14:38:29 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	here_doc_logic(char **argv)
{
	int		fd;
	char	*readed_line;

	readed_line = NULL;
	fd = open(".temp_file_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (write_in_file(argv, fd, readed_line) == 0)
		return (0);
	close (fd);
	fd = open(".temp_file_tmp", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close (fd);
	return (0);
}

int	write_in_file(char **argv, int fd, char *readed_line)
{
	char	*limiter;

	limiter = ft_strjoint(argv[1], "\n");
	while (1)
	{
		write (STDIN_FILENO, ">>", 2);
		readed_line = get_next_line(STDIN_FILENO, 1);
		if (ft_strcmp(readed_line, limiter) == 0)
		{
			get_next_line(STDIN_FILENO, 0);
			free(limiter);
			free(readed_line);
			break ;
		}
		write (fd, readed_line, ft_stringlen(readed_line));
		free(readed_line);
	}
	return (1);
}
