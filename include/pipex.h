/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:42:29 by jileroux          #+#    #+#             */
/*   Updated: 2022/12/15 16:21:18 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../include/get_next_line.h"

enum	e_fd{
	DEFAULT = -1,
	IN,
	OUT,
	MAX_FD,
	HERE_DOC
};

typedef struct s_args {
	int				fds[MAX_FD];
	int				redir_type;
	char			*cmd;
	char			**options;
	char			**envp;
	char			*file;
	int				here_doc;
	pid_t			pid;
	struct s_args	*next;
}	t_args;

int		stack_args(int argc, char **argv, char **envp, t_args **args_list);
t_args	*lst_new(void *content, char **envp);
t_args	*ft_lstadd_back(t_args **lst, t_args *new);
t_args	*ft_lstlast(t_args *lst);
void	print_list(t_args *args_list);
int		open_file(char **argv, t_args **args_list);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
size_t	ft_stringlen(const char *s);
char	*ft_find_path(char **envp);
char	*ft_strjoint(char *s1, char *s2);
char	**split_and_add_slash(char *path);
char	*ft_check_path(char **path_list, char **cmd);
void	ft_free_list(char **path_list);
char	*ft_get_path(char **envp, char *argv);
int		ft_count(char const *s, char c);
int		ft_size(char const *s, char c, int i);
void	*ft_free(char **s, int j);
char	**ft_empty_malloc(void);
char	**ft_split(char const *s, char c);
int		define_pipe(t_args *args_list);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *tab, int c, size_t n);
int		close_fd(t_args *args_list);
int		pipex_logic(t_args *args_list, char **envp);
int		dup_and_exec(t_args *args_list, char **envp);
void	free_list(t_args *args_list);
int		ft_strcmp(const char *s1, const char *s2);
int		write_in_file(char **argv, int fd, char *readed_line);
int		go_pipex(t_args *args_list, char **envp);
int		here_doc_logic(char **argv);
int		parsing(int argc, char **argv, char **envp);
int		parsing_file(int argc, char **argv);
int		parsing_cmd(int argc, char **argv, char **envp);

#endif
