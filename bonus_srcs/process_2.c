/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:24:36 by suchua            #+#    #+#             */
/*   Updated: 2023/01/12 19:47:24 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

//to handle case for 2 somehow it doesnt work zzzz
void	child_1(t_pipex p)
{
	char	*first_arg;
	char	**second_arg;

	dup2(p.fd2[1], 1);
	close(p.fd2[0]);
	dup2(p.infile, 0);
	close(p.fd2[1]);
	second_arg = ft_split(p.cmd[0], 32);
	first_arg = get_first_arg(p, second_arg[0]);
	execve(first_arg, second_arg, p.env);
}

void	child_2(t_pipex p)
{
	char	*first_arg;
	char	**second_arg;

	dup2(p.fd2[0], 0);
	close(p.fd2[1]);
	dup2(p.outfile, 1);
	close(p.fd2[0]);
	second_arg = ft_split(p.cmd[1], 32);
	first_arg = get_first_arg(p, second_arg[0]);
	execve(first_arg, second_arg, p.env);
}

void	do_it2(t_pipex p)
{
	int	pid1;
	int	pid2;

	if (pipe(p.fd2) == -1)
		error_msg("Error piping !!\n");
	pid1 = fork();
	if (pid1 == -1)
	{
		error_msg("Error opening fork !\n");
	}
	if (pid1 == 0)
		child_1(p);
	pid2 = fork();
	if (pid2 == -1)
	{
		error_msg("Error opening fork !\n");
	}
	if (pid2 == 0)
		child_2(p);
	close(p.fd2[0]);
	close(p.fd2[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
