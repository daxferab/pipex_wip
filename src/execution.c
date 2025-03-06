/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:58:43 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/06 19:40:16 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*get_path(char **envp, char	*cmd)
{
	char	*line;
	char	**path_split;
	char	*path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	line = ft_strdup(envp[i] + 5);
	path_split = ft_split(line, ':');
	cmd = ft_strjoin("/", cmd);
	i = 0;
	while (path_split[i])
	{
		path = ft_strjoin(path_split[i], cmd);
		if (access(path, X_OK) == 0)
			return (free_split(path_split), free(line), free(cmd), path);
		free(path);
		i++;
	}
	return (free_split(path_split), free(line), free(cmd), NULL);
}

void	execute(char **envp, char *argv)
{
	char	*path;
	char	**cmd;

	if (!ft_strncmp(argv, "", 1))
		error(6);
	cmd = ft_split(argv, ' ');
	path = get_path(envp, cmd[0]);
	if (path == NULL)
	{
		free_split(cmd);
		error(6);
	}
	if (execve(path, cmd, envp) == -1)
	{
		free_split(cmd);
		free(path);
		error(8);
	}
}
