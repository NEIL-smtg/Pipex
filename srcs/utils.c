/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:45:56 by suchua            #+#    #+#             */
/*   Updated: 2023/01/18 17:17:44 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_msg(char *s, int code)
{
	perror(s);
	exit(code);
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
