/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 03:24:00 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/06 19:40:53 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	error(int code)
{
	if (code == 1)
	{
		ft_putstr_fd("Error. Wrong number of arguments\n", 2);
		ft_putstr_fd("Correct usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
	}
	if (code == 2)
		ft_putstr_fd("Error. Pipe failed\n", 2);
	if (code == 3)
		ft_putstr_fd("Error. Fork failed\n", 2);
	if (code == 4)
		ft_putstr_fd("Error. Couldn't read infile\n", 2);
	if (code == 5)
		ft_putstr_fd("Error. Couldn't read outfile\n", 2);
	if (code == 6)
		ft_putstr_fd("Error. Command not found\n", 2);
	if (code == 7)
		ft_putstr_fd("Error. Dup2 failed\n", 2);
	if (code == 8)
		ft_putstr_fd("Error. Execution failed", 2);
	exit(1);
}
