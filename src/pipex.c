/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavas-g <anavas-g@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:21:40 by anavas-g          #+#    #+#             */
/*   Updated: 2024/04/28 23:00:12 by anavas-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	execute(t_pipex *pipex, t_cmd *cmd, char *envp[])
{
	create_pipe(pipex->fd_pipe);
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pipex->pid != 0)
		child_routine(pipex, cmd, envp);
	wait(&pipex->pid);
	parent_routine(pipex, cmd, envp);
}

// child_routine() is the functions that will be executed by the child process.
void	child_routine( t_pipex *pipex, t_cmd *cmd, char *envp[])
{
	int		fd_infile;
	char	*str_cmd;
	int		status;

	fd_infile = open(cmd->infile, O_RDONLY);
	if (fd_infile == -1)
	{
		perror("open infile");
		exit(EXIT_FAILURE);
	}
	dup2(fd_infile, STDIN_FILENO);
	dup2(pipex->fd_pipe[1], STDOUT_FILENO);
	close(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[1]);
	str_cmd = get_path(cmd->cmd1[0], envp);
	status = execve(str_cmd, ft_split(cmd->cmd1[0], ' '), envp);
	if (status == -1)
	{
		perror("execveX");
		ft_error("Error: execve Xfailed\n");
	}
}

// parent_routine() is the function that will be executed by the parent process.
void	parent_routine(t_pipex *pipex, t_cmd *cmd, char *envp[])
{
	int		fd_outfile;
	char	*str_cmd;

	fd_outfile = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile == -1)
	{
		perror("open outfile");
		exit(EXIT_FAILURE);
	}
	dup2(pipex->fd_pipe[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	close(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[1]);
	str_cmd = get_path(cmd->cmd2[0], envp);
	execve(str_cmd, ft_split(cmd->cmd2[0], ' '), envp);
}
