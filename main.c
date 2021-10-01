/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:20:20 by emgarcia          #+#    #+#             */
/*   Updated: 2021/09/29 18:51:15 by emgarcia         ###   ########.fr       */
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

char	*ft_findpath(char **envp)
{
	size_t	i;

	i = -1;
	while (envp[++i])
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
			&& envp[i][2] == 'T' && envp[i][3] == 'H')
			return (envp[i]);
	return (NULL);
}

char	**ft_parsepaths(char **envp)
{
	size_t	i;
	char	*paths;
	char	**spaths;
	char	*aux;

	paths = ft_substr(ft_findpath(envp), 5, 61);
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

void	ft_pipex(int fd1, int fd2, char **argv, char **envp)
{
	int		end[2];
	pid_t	pid;
	char	**mycmd1;
	char	**mycmd2;

	mycmd1 = ft_split(argv[2], ' ');
	mycmd2 = ft_split(argv[3], ' ');
	pipe(end);
	pid = fork();
	if (pid < 0)
		return (perror("Fork : "));
	if (!pid)
		ft_child(fd1, mycmd1, envp, end);
	else
		ft_parent(fd2, mycmd2, envp, end);
}

int	main(int argc, char *argv[], char **envp)
{
	int	fd1;
	int	fd2;

	if (argc == 2)
		printf("%s\n", argv[1]);
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 < -1)
		return (0);
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd2 < -1)
		return (0);
	ft_pipex(fd1, fd2, argv, envp);
	return (0);
}
