/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:13:28 by jileroux          #+#    #+#             */
/*   Updated: 2022/12/19 15:05:33 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_get_path(char **envp, char *argv)
{
	char	*path;
	char	**path_list;
	char	**tab;

	path = NULL;
	path_list = NULL;
	tab = ft_split(argv, ' ');
	path = ft_find_path(envp);
	path_list = split_and_add_slash(path);
	free(path);
	path = ft_check_path(path_list, tab);
	ft_free_list(tab);
	ft_free_list(path_list);
	return (path);
}

char	*ft_find_path(char **envp)
{
	int	index;

	index = 0;
	while (envp[index])
	{
		if (ft_strnstr(envp[index], "PATH", 4) != NULL)
			return (ft_strdup(&envp[index][5]));
		index++;
	}
	return (NULL);
}

char	**split_and_add_slash(char *path)
{
	int		index;
	char	**path_list;
	char	*temp;

	index = 0;
	path_list = NULL;
	path_list = ft_split(path, ':');
	while (path_list[index])
	{
		temp = ft_strjoint(path_list[index], "/");
		free(path_list[index]);
		path_list[index] = temp;
		index++;
	}
	return (path_list);
}

char	*ft_check_path(char **path_list, char **cmd)
{
	int		index;
	char	*cmd_path;

	index = 0;
	cmd_path = NULL;
	if (access(cmd[0], F_OK | X_OK) == 0)
		return (ft_strdup(cmd[0]));
	while (path_list[index])
	{
		cmd_path = ft_strjoint(path_list[index], cmd[0]);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		index++;
	}
	return (NULL);
}
