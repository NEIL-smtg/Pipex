/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:03:20 by suchua            #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2023/01/10 01:05:06 by suchua           ###   ########.fr       */
=======
/*   Updated: 2023/01/10 18:00:45 by suchua           ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../Libft/libft.h"
# include "../Libft/ft_printf/ft_printf.h"
# include "../Libft/gnl/get_next_line_bonus.h"
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
<<<<<<< Updated upstream
	int		fd[2];
	char	**env;
	char	**path;
	char	**cmd;
	char	*first_arg;
	char	**second_arg;
}	t_pipex;

# define FIRST 0
# define SECOND 1
=======
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
>>>>>>> Stashed changes

#endif