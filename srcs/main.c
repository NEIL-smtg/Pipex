/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:52:16 by suchua            #+#    #+#             */
/*   Updated: 2023/01/12 19:53:34 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_path(t_pipex *p, char **env)
{
	int		i;

	i = 0;
	while (ft_strncmp("PATH", env[i], 4))
		++i;
	p->path = ft_split(env[i], ':');
}

void	init(t_pipex *p, int ac, char **av, char **env)
{
	if (pipe(p->fd) == -1)
		error_msg("Error opening pipe !\n");
	p->infile = open(av[1], O_RDONLY);
	p->outfile = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0000644);
	p->env = env;
	p->cmd = ft_calloc(3, sizeof(char *));
	p->cmd[0] = ft_strdup(av[2]);
	p->cmd[1] = ft_strdup(av[3]);
	p->cmd[2] = 0;
	set_path(p, env);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;
	int		fd;

	if (ac < 5)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		error_msg("Error opening file !!\n");
	close(fd);
	init(&pipex, ac, av, env);
	do_it(pipex);
	free_all(&pipex);
	return (0);
}
