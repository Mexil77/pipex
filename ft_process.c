/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 20:16:01 by emgarcia          #+#    #+#             */
/*   Updated: 2021/10/01 20:50:56 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parent(int fd2, char **mycmd2, char **envp, int *end)
{
	char	*cmd;
	size_t	i;
	char	**paths;
	int		status;

	waitpid(-1, &status, 0);
	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	paths = ft_parsepaths(envp);
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], mycmd2[0]);
		if (cmd && !access(cmd, R_OK))
		{
			dup2(fd2, STDOUT_FILENO);
			execve(cmd, mycmd2, envp);
			free(cmd);
		}
	}
	close(fd2);
	ft_putstr_fd(ft_strjoin("zsh: command not found: ", mycmd2[0]), 1);
	exit (EXIT_FAILURE);
}

void	ft_child(int fd1, char **mycmd1, char **envp, int *end)
{
	char	*cmd;
	size_t	i;
	char	**paths;

	close(end[0]);
	dup2(fd1, STDIN_FILENO);
	close(fd1);
	paths = ft_parsepaths(envp);
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], mycmd1[0]);
		if (cmd && !access(cmd, R_OK))
		{
			dup2(end[1], STDOUT_FILENO);
			execve(cmd, mycmd1, envp);
			free(cmd);
		}
	}
	close(end[1]);
	ft_putstr_fd(ft_strjoin("zsh: command not found: ", mycmd1[0]), 1);
	exit (EXIT_FAILURE);
}
