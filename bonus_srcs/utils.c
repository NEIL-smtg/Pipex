/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:06:57 by suchua            #+#    #+#             */
/*   Updated: 2023/01/12 19:21:25 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_msg(char *s)
{
	write(2, s, ft_strlen(s));
	exit(EXIT_FAILURE);
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
