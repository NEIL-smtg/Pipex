/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:06:57 by suchua            #+#    #+#             */
/*   Updated: 2023/01/18 18:47:41 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_msg(char *s, int code)
{
	perror(s);
	exit(code);
}

void	close_pipe(t_pipex *p, int j)
{
	int	i;

	i = -1;
	while (++i < j)
	{
		close(p->fd[i][0]);
		close(p->fd[i][1]);
	}
}

void	close_all_pipess(t_pipex *p)
{
	int	i;

	i = -1;
	while (++i < p->pipe_size)
	{
		close(p->fd[i][0]);
		close(p->fd[i][1]);
	}
}

void	free_all(t_pipex *p)
{
	int	i;

	i = -1;
	while (p->cmd[++i])
		free(p->cmd[i]);
	if (p->cmd)
		free(p->cmd);
	i = -1;
	while (p->path[++i])
		free(p->path[i]);
	if (p->path)
		free(p->path);
	i = -1;
	while (++i < p->pipe_size)
		free(p->fd[i]);
	free(p->fd);
	close(p->infile);
	close(p->outfile);
}
