/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:52:26 by suchua            #+#    #+#             */
/*   Updated: 2023/01/10 19:53:08 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../Libft/libft.h"
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**env;
	char	**path;
	int		fd[2];
	char	**cmd;
	char	*p1_first_arg;
	char	**p1_second_arg;
	char	*p2_first_arg;
	char	**p2_second_arg;
}	t_pipex;


//utils
void	error_msg(char *s);
void	free_all(t_pipex *p);

//process
void	do_it(t_pipex p);

#endif