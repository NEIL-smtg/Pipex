/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:57:46 by suchua            #+#    #+#             */
/*   Updated: 2023/01/12 19:53:31 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	set_infile(t_pipex *p, char **av)
{
	p->infile = open(av[1], O_RDONLY);
	if (p->infile == -1)
		error_msg("Error opening infile !!\n");
}

void	set_path(t_pipex *p, char **env)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", env[i], 4))
		++i;
	p->path = ft_split(env[i], ':');
}

void	set_cmd(t_pipex *p, char **av, int ac)
{
	int	j;

	j = 0;
	p->cmd = ft_calloc(ac - 2, sizeof(char *));
	while (j + 2 < ac - 1)
	{
		p->cmd[j] = ft_strdup(av[j + 2]);
		++j;
	}
	p->cmd[j] = 0;
	p->pipe_size = j;
}

void	init(t_pipex *p, int ac, char **av, char **env)
{
	int	i;

	p->pipex_index = 0;
	p->outfile = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0000644);
	if (p->outfile == -1)
	{
		close(p->infile);
		error_msg("Error creating/opening outfile !!\n");
	}
	p->env = env;
	set_path(p, env);
	set_cmd(p, av, ac);
	if (p->pipe_size == 2)
		return ;
	p->fd = malloc(p->pipe_size * sizeof(int *));
	i = -1;
	while (p->fd[++i])
	{
		p->fd[i] = malloc(2 * sizeof(int));
		if (pipe(p->fd[i]) == -1)
		{
			close_pipe(p, i);
			error_msg("Error piping !\n");
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac < 5)
		return (0);
	if (!ft_strncmp("here_doc", av[1], 9))
		handle_here_doc(&pipex, ac);
	else
		pipex.here_doc = 0;
	if (!pipex.here_doc)
		set_infile(&pipex, av);
	init(&pipex, ac, av, env);
	execute(&pipex);
	close(pipex.infile);
	close(pipex.outfile);
	return (0);
}
