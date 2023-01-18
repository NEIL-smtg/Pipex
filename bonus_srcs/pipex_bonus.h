/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:59:40 by suchua            #+#    #+#             */
/*   Updated: 2023/01/18 18:47:52 by suchua           ###   ########.fr       */
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
	int		here_doc;
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

//heredoc
void	handle_here_doc(t_pipex *p, int ac, char *limiter);

//utils
void	error_msg(char *s, int code);
void	close_pipe(t_pipex *p, int j);
void	close_all_pipess(t_pipex *p);
void	free_all(t_pipex *p);

//process
void	execute(t_pipex *p);
char	*get_first_arg(t_pipex p, char *cmd);

#endif