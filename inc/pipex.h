/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavas-g <anavas-g@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:35:12 by anavas-g          #+#    #+#             */
/*   Updated: 2024/04/29 10:49:39 by anavas-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft/ft_printf.h"
# include "../lib/libft/get_next_line.h"
# include "../lib/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		fd_pipe[2];
	pid_t	pid;
}	t_pipex;

typedef struct s_cmd
{
	char	**cmd1;
	char	**cmd2;
	char	*infile;
	char	*outfile;
}	t_cmd;

int		create_pipe(int *fd);
void	execute(t_pipex *pipex, t_cmd *cmd, char *envp[]);
void	child_routine(t_pipex *pipex, t_cmd *cmd, char *envp[]);
void	parent_routine(t_pipex *pipex, t_cmd *cmd, char *envp[]);
char	*get_envp(char *name, char **envp);
char	*get_path(char *cmd, char **envp);
void	ft_error(char *str);
void	free_dbl_ptr(char **ptr);

#endif