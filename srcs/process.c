/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:44:47 by suchua            #+#    #+#             */
/*   Updated: 2023/01/18 19:26:10 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_arg_preprocessing(t_pipex p, char *exe)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(exe, '/');
	while (split[i])
		++i;
	if (i != 0)
	{
		free(exe);
		exe = ft_strdup(split[i - 1]);
	}
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

char	*get_first_arg(t_pipex p, char *exe)
{
	int		i;
	char	*tmp;
	char	*arg;

	if (access(exe, 0) == 0)
		return (exe);
	else
		first_arg_preprocessing(p, exe);
	i = 0;
	while (p.path[i])
	{
		tmp = ft_strjoin(p.path[i], "/");
		arg = ft_strjoin(tmp, exe);
		free(tmp);
		if (!access(arg, 0))
			return (arg);
		free(arg);
		++i;
	}
	return (NULL);
}

void	child_1(t_pipex p)
{
	dup2(p.fd[1], 1);
	close(p.fd[0]);
	dup2(p.infile, 0);
	close(p.fd[1]);
	p.p1_second_arg = ft_split(p.cmd[0], 32);
	p.p1_first_arg = get_first_arg(p, p.p1_second_arg[0]);
	if (p.p1_first_arg == NULL)
	{
		free_all(&p);
		error_msg("Command not found\n", 1);
	}
	if (execve(p.p1_first_arg, p.p1_second_arg, p.env) == -1)
	{
		free_all(&p);
		error_msg("Command not found\n", 1);
	}
}

void	child_2(t_pipex p)
{
	dup2(p.fd[0], 0);
	close(p.fd[1]);
	dup2(p.outfile, 1);
	close(p.fd[0]);
	p.p2_second_arg = ft_split(p.cmd[1], 32);
	p.p2_first_arg = get_first_arg(p, p.p2_second_arg[0]);
	if (p.p2_first_arg == NULL)
	{
		free_all(&p);
		error_msg("Command not found\n", 1);
	}
	if (execve(p.p2_first_arg, p.p2_second_arg, p.env) == -1)
	{
		free_all(&p);
		error_msg("Command not found\n", 1);
	}
}

void	do_it(t_pipex p)
{
	int	pid1;
	int	pid2;

	p.p1_first_arg = NULL;
	p.p2_first_arg = NULL;
	pid1 = fork();
	if (pid1 == -1)
	{
		free_all(&p);
		error_msg("Error opening fork !\n", -1);
	}
	if (pid1 == 0)
		child_1(p);
	pid2 = fork();
	if (pid2 == -1)
	{
		free_all(&p);
		error_msg("Error opening fork !\n", -1);
	}
	if (pid2 == 0)
		child_2(p);
	close(p.fd[0]);
	close(p.fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
