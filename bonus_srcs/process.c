/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:10:48 by suchua            #+#    #+#             */
/*   Updated: 2023/01/11 19:18:47 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_first_arg(t_pipex p, char *cmd)
{
	int		i;
	char	*tmp;
	char	*arg;

	i = -1;
	while (p.path[++i])
	{
		tmp = ft_strjoin(p.path[i], "/");
		arg = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(arg, 0) == 0)
			return (arg);
		free(arg);
	}
	return (NULL);
}

void	handle_dup(t_pipex p)
{
	if (p.pipex_index == 0)
	{
		dup2(p.infile, 0);
		dup2(p.fd[p.pipex_index][1], 1);
	}
	else if (p.pipex_index == p.pipe_size - 1)
	{
		dup2(p.fd[p.pipex_index - 1][0], 0);
		dup2(p.outfile, 1);
	}
	else
	{
		dup2(p.fd[p.pipex_index - 1][0], 0);
		dup2(p.fd[p.pipex_index][1], 1);
	}
}

void	do_it(t_pipex p)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		error_msg("Error forking process !\n");
	if (!pid)
	{
		handle_dup(p);
		close_pipe(&p, p.pipex_index);
		p.second_arg = ft_split(p.cmd[p.pipex_index], 32);
		p.first_arg = get_first_arg(p, p.second_arg[0]);
		execve(p.first_arg, p.second_arg, p.env);
	}
	close_pipe(&p, p.pipex_index);
	waitpid(pid, NULL, 0);
}

void	execute(t_pipex *p)
{
	int	i;

	while (p->pipex_index < p->pipe_size)
	{
		do_it(*p);
		++(p->pipex_index);
	}
}
