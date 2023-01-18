/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:52:16 by suchua            #+#    #+#             */
/*   Updated: 2023/01/18 18:45:53 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_path(t_pipex *p, char **env)
{
	int		i;

	i = 0;
	while (ft_strncmp("PATH", env[i], 4))
		++i;
	p->path = ft_split(env[i] + 5, ':');
}

void	init(t_pipex *p, int ac, char **av, char **env)
{
	if (pipe(p->fd) == -1)
		error_msg("Pipe", -1);
	p->outfile = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0000644);
	if (p->outfile == -1)
		error_msg("Outfile", 1);
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

	if (ac != 5 || av == NULL)
		error_msg("Invalid number of arguments.\n", 1);
	pipex.infile = open(av[1], O_RDONLY);
	if (pipex.infile == -1)
		error_msg("Infile", 0);
	init(&pipex, ac, av, env);
	do_it(pipex);
	free_all(&pipex);
	return (0);
}
