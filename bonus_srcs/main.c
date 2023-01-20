/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:57:46 by suchua            #+#    #+#             */
/*   Updated: 2023/01/19 02:14:19 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	set_infile(t_pipex *p, char **av)
{
	p->infile = open(av[1], O_RDONLY);
	if (p->infile == -1)
		error_msg("Infile", 0);
}

void	set_path(t_pipex *p, char **env)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", env[i], 4))
		++i;
	p->path = ft_split(env[i] + 5, ':');
}

void	set_cmd(t_pipex *p, char **av, int ac)
{
	int	j;

	j = 0;
	p->cmd = ft_calloc(ac - 2, sizeof(char *));
	while (j + 2 + p->here_doc < ac - 1)
	{
		p->cmd[j] = ft_strdup(av[j + 2 + p->here_doc]);
		++j;
	}
	p->cmd[j] = 0;
	if (j == 2)
		p->pipe_size = j - 1;
	else
		p->pipe_size = j;
}

void	init(t_pipex *p, int ac, char **av, char **env)
{
	int	i;

	p->outfile = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0000644);
	if (p->outfile == -1)
	{
		close(p->infile);
		error_msg("Outfile", 1);
	}
	p->env = env;
	set_path(p, env);
	set_cmd(p, av, ac);
	p->fd = malloc(p->pipe_size * sizeof(int *));
	i = -1;
	while (++i < p->pipe_size)
	{
		p->fd[i] = malloc(2 * sizeof(int));
		if (pipe(p->fd[i]) == -1)
		{
			close_pipe(p, i);
			error_msg("Pipe", 1);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac < 5 || av == NULL)
		error_msg("Invalid number of arguments.\n", 1);
	if (!ft_strncmp("here_doc", av[1], 9))
		handle_here_doc(&pipex, ac, av[2]);
	else
		pipex.here_doc = 0;
	if (!pipex.here_doc)
		set_infile(&pipex, av);
	init(&pipex, ac, av, env);
	execute(&pipex);
	free_all(&pipex);
	return (0);
}
