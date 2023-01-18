/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:10:48 by suchua            #+#    #+#             */
/*   Updated: 2023/01/18 21:13:30 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	first_arg_preprocessing(t_pipex p, char *exe)
{
	char	**split;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	split = ft_split(exe, '/');
	while (split[i])
		++i;
	if (i != 0)
	{
		free(exe);
		exe = ft_strdup(split[i - 1]);
		flag = 1;
	}
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	return (flag);
}

char	*get_first_arg(t_pipex p, char *cmd)
{
	int		i;
	char	*tmp;
	char	*arg;

	if (access(cmd, 0) == 0)
		return (ft_strdup(cmd));
	else
		first_arg_preprocessing(p, cmd);
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
		dup2(p.fd[0][1], 1);
	}
	else if (p.pipex_index == p.pipe_size || p.pipex_index == p.pipe_size - 1)
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
		error_msg("Fork error !\n", 1);
	if (!pid)
	{
		handle_dup(p);
		close_all_pipess(&p);
		p.second_arg = ft_split(p.cmd[p.pipex_index], 32);
		p.first_arg = get_first_arg(p, p.second_arg[0]);
		if (!p.first_arg)
		{
			free_all(&p);
			error_msg("Command not found\n", 1);
		}
		if (execve(p.first_arg, p.second_arg, p.env) == -1)
		{
			free_all(&p);
			error_msg("Command not found\n", 1);
		}
	}
}

void	execute(t_pipex *p)
{
	if (p->pipe_size == 1)
	{
		p->pipex_index = -1;
		while (p->pipex_index < p->pipe_size)
		{
			++(p->pipex_index);
			do_it(*p);
		}
	}
	else
	{
		p->pipex_index = 0;
		while (p->pipex_index < p->pipe_size)
		{
			do_it(*p);
			++(p->pipex_index);
		}
	}
	waitpid(-1, NULL, 0);
}
