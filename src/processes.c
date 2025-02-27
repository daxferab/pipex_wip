/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:56:08 by daxferna          #+#    #+#             */
/*   Updated: 2025/02/28 19:29:37 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	child_process(int *pipe, char **argv, char **envp) //Ejecuta cmd1 en infile y escribe en fdpipe[1]
{
	int fdin;

	close(pipe[0]);
	fdin = open(argv[1], O_RDONLY, 0644);
	if (fdin == -1)
		error(4);
	dup2(fdin, STDIN_FILENO);
	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[1]);
	close(fdin);
	execute(envp, argv[1]);
}

int	parent_process(int *pipe, char **argv, char **envp) //Ejecuta cmd2 en fdpipe[0] y escribe en outfile
{
	int	pid2;
	int	fdout;

	wait(NULL);
	pid2 = fork();
	if (pid2 == -1)
		error(3);
	wait(NULL);
	if (pid2 == 0)
	{
		close(pipe[1]);
		fdout = open(argv[4], O_WRONLY | O_CREAT , 0644);
		if (fdout == -1)
		error(5);
		dup2(pipe[0], STDIN_FILENO);
		dup2(fdout, STDOUT_FILENO); //TODO: Proteger dup2
		close(pipe[0]);
		close(fdout);
		execute(envp, argv[2]);
	}
	return (0);
}
