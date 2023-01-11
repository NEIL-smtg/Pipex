/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:59:40 by suchua            #+#    #+#             */
/*   Updated: 2023/01/11 18:20:57 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../Libft/libft.h"
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		**fd;
	int		pipe_size;
	char	**cmd;
	char	**path;
	char	**env;
	int		infile;
	int		outfile;
	int		pipex_index;
	char	*first_arg;
	char	**second_arg;
}	t_pipex;

//utils
void	error_msg(char *s);
void	close_pipe(t_pipex *p, int j);

//process
void	execute(t_pipex *p);

#endif