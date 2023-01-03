/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:48:17 by jileroux          #+#    #+#             */
/*   Updated: 2022/12/14 14:28:53 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h>
# include <unistd.h>

int		ft_strchr(char *s);
int		ft_strlen(char *str);
char	*ft_get_line(char *str);
char	*ft_save_line(char *str);
char	*get_next_line(int fd, int to_free);
char	*ft_strjoin(char *str1, char *str2);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_read_line(int fd, char *str_static);
char	*ft_strcpy_after_backslash_n(char *dest, const char *src);

#endif
