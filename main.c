/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:20:20 by emgarcia          #+#    #+#             */
/*   Updated: 2021/09/27 22:45:13 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_freeall(char **mycmd, char **spaths)
{
	size_t	i;

	i = -1;
	while (spaths[++i])
		free(spaths[i]);
	free(spaths);
	i = -1;
	while (mycmd[++i])
		free(mycmd[i]);
	free(mycmd);
}

char	**ft_parsepaths(char **envp)
{
	size_t	i;
	char	*paths;
	char	**spaths;
	char	*aux;

	paths = ft_substr(envp[13], 5, 61);
	spaths = ft_split(paths, ':');
	free(paths);
	i = -1;
	while (spaths[++i])
	{
		aux = spaths[i];
		spaths[i] = ft_strjoin(spaths[i], "/");
		free(aux);
	}
	return (spaths);
}

void	ft_child(int fd1, char **mycmd1, char **envp, int *end)
{
	char	*cmd;
	size_t	i;
	char	**paths;

	dup2(fd1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	printf("Llegue\n");
	close(end[0]);
	paths = ft_parsepaths(envp);
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], mycmd1[0]);
		if (cmd)
		{
			execve(cmd, mycmd1, envp);
			free(cmd);
		}
	}
}

void	ft_parent(int fd2, char **mycmd2, char **envp, int *end)
{
	char	*cmd;
	size_t	i;
	char	**paths;
	int		status;

	waitpid(-1, &status, 0);
	dup2(fd2, STDIN_FILENO);
	dup2(end[0], STDOUT_FILENO);
	close(end[1]);
	paths = ft_parsepaths(envp);
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], mycmd2[0]);
		if (cmd)
		{
			execve(cmd, mycmd2, envp);
			free(cmd);
		}
	}
}

void	ft_pipex(int fd1, char **argv, char **envp)
{
	int		end[2];
	pid_t	parent;
	char	**mycmd1;

	if (!fd1)
		printf("fd1 : %d\n", fd1);
	mycmd1 = ft_split(argv[2], ' ');
	pipe(end);
	parent = fork();
	if (parent < 0)
		return (perror("Fork : "));
	if (!parent)
	{
		ft_child(fd1, mycmd1, envp, end);
	}
	//else
		//ft_parent(fd2, mycmd2, envp, end);
	//ft_freeall(mycmd1, paths);
}

int	main(int argc, char *argv[], char **envp)
{
	int		fd1;

	if (argc == 2)
		printf("%s\n", argv[1]);
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 < -1)
		return (0);
	ft_pipex(fd1, argv, envp);
	close(fd1);
	return (0);
}
