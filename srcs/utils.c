/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:45:56 by suchua            #+#    #+#             */
/*   Updated: 2023/01/10 18:36:05 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_msg(char *s)
{
	write(2, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}

void	free_all(t_pipex *p)
{
	int	i;

	i = -1;
	while (p->path[++i])
		free(p->path[i]);
	free(p->path);
	i = -1;
	while (p->cmd[++i])
		free(p->cmd[i]);
	free(p->cmd);
	close(p->fd[0]);
	close(p->fd[1]);
	close(p->infile);
	close(p->outfile);
}
