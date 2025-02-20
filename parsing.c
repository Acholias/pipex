/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:49:56 by lumugot           #+#    #+#             */
/*   Updated: 2024/12/19 14:32:40 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char **env)
{
	char	**path;
	char	*part_cmd;
	char	*path_part;
	int		index;

	index = 0;
	while (ft_strnstr(env[index], "PATH=", 5) == 0)
		index++;
	path = ft_split(env[index] + 5, ':');
	index = 0;
	while (path[index++])
	{
		path_part = ft_strjoin(path[index], "/");
		part_cmd = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(part_cmd, F_OK) == 0)
			return (part_cmd);
		free(part_cmd);
	}
	index = 0;
	while (path[index++])
		free(path[index]);
	free(path);
	return (0);
}

void	execute(char *argv, char **env)
{
	char	**cmd;
	char	*path;
	int		index;

	if (!argv)
	{
		perror("Error parsing command !");
		exit(-1);
	}
	index = 0;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], env);
	if (!path)
	{
		while (cmd[index])
		{
			free(cmd[index]);
			index++;
		}
		free(cmd);
		perror("Error executing command !");
	}
	if (execve(path, cmd, env) == 1)
		perror ("Error !");
}
