/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavas-g <anavas-g@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:08:27 by anavas-g          #+#    #+#             */
/*   Updated: 2024/04/29 10:48:35 by anavas-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd	cmd;
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_error("Error: Wrong number of arguments\n");
		return (-1);
	}
	else
	{
		if (ft_strlen(argv[2]) == 0 || ft_strlen(argv[3]) == 0)
		{
			ft_error("Error: Command is empty\n");
			return (-1);
		}
		cmd.cmd1 = &argv[2];
		cmd.cmd2 = &argv[3];
		cmd.infile = argv[1];
		cmd.outfile = argv[4];
		execute(&pipex, &cmd, envp);
	}
}
/*valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all
 -s ./pipex "file.txt" "grep -i 'drwxr'" "wc -l" "outfile"*/
