/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavas-g <anavas-g@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:21:40 by anavas-g          #+#    #+#             */
/*   Updated: 2024/04/28 23:01:58 by anavas-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	create_pipe(int *fd)
{
	if (pipe((int *)fd) == -1)
	{
		perror("Pipe: ");
		ft_error("Error: Pipe failed\n");
		return (1);
	}
	return (0);
}

void	free_dbl_ptr(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

char	*get_envp(char *name, char **envp)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		sub = ft_substr(envp[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (envp[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	*executable;
	char	**paths;
	char	*path;
	char	**s_cmd;

	i = -1;
	paths = ft_split(get_envp("PATH", envp), ':');
	s_cmd = ft_split(cmd, ' ');
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		executable = ft_strjoin(path, s_cmd[0]);
		free(path);
		if (access(executable, F_OK | X_OK) == 0)
		{
			free_dbl_ptr(s_cmd);
			return (executable);
		}
		free(executable);
	}
	free_dbl_ptr(paths);
	free_dbl_ptr(s_cmd);
	return (cmd);
}
