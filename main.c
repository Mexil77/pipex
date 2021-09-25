/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:20:20 by emgarcia          #+#    #+#             */
/*   Updated: 2021/09/25 19:03:50 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char const *argv[])
{
	size_t	i;

	i = 0;
	while (argv[++i])
		printf("%s\n", argv[i]);
	if (argc == 2)
		printf("%s\n", argv[1]);
	printf("pipex\n");
	return (0);
}
