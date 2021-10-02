/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:04:59 by emgarcia          #+#    #+#             */
/*   Updated: 2021/10/02 20:12:49 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_defaultpath(void)
{
	char	*aux;
	char	*line;

	line = ft_strjoin("/usr/local/bin:/usr/bin:", "/bin:/usr/sbin:/sbin:");
	aux = line;
	line = ft_strjoin(line, "/usr/local/munki:/Library/Frameworks/Mono.");
	free(aux);
	aux = line;
	line = ft_strjoin(line, "framework/Versions/Current/Commands");
	free(aux);
	return (line);
}
