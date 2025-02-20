/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:50:12 by lumugot           #+#    #+#             */
/*   Updated: 2024/11/30 15:56:14 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **argv, char **env, int *fd)
{
	int	in_file;

	in_file = open(argv[1], O_RDONLY, 0777);
	if (in_file == -1)
	{
		perror("Error !");
		exit(0);
	}
	dup2(in_file, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	execute(argv[2], env);
}

void	parent(char **argv, char **env, int *fd)
{
	int	out_file;

	out_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out_file == -1)
	{
		perror("Error !");
		exit(0);
	}
	dup2(fd[0], 0);
	dup2(out_file, 1);
	close(fd[1]);
	close(fd[0]);
	execute(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		perror("Error Arguments !");
	if (pipe(fd) == -1)
	{
		perror("Error creating pipe !");
		exit(-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error PID !");
		exit(-1);
	}
	if (pid == 0)
		child(argv, env, fd);
	waitpid(pid, NULL, 0);
	parent(argv, env, fd);
}
