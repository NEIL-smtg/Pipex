/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:03:02 by suchua            #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2023/01/10 01:19:21 by suchua           ###   ########.fr       */
=======
/*   Updated: 2023/01/10 18:26:32 by suchua           ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

<<<<<<< Updated upstream
void	error_msg(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	set_path(t_pipex *p, char **env)
{
	int		i;

	p->env = env;
=======
void	set_path(t_pipex *p, char **env)
{
	int		i;
	char	*tmp;

>>>>>>> Stashed changes
	i = 0;
	while (ft_strncmp("PATH", env[i], 4))
		++i;
	p->path = ft_split(env[i], ':');
}

<<<<<<< Updated upstream
void	init(t_pipex *p, char **env, char **av, int ac)
{
	int	i;

	p->infile = open(av[1], O_RDONLY);
	if (p->infile < 0)
		error_msg("File does not exist !\n");
	p->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (p->outfile < 0)
	{
		close(p->infile);
		error_msg("Error open output file !!\n");
	}
	set_path(p, env);
	p->cmd = ft_calloc(3, sizeof(char *));
	i = -1;
	while (++i < 2)
		p->cmd[i] = ft_strdup(av[i + 2]);
	p->cmd[i] = 0;
}

char	*get_mpath(t_pipex *p, char *arg2)
{
	int		i;
	char	*tmp;
	char	*cmd;

	i = -1;
	while (p->path[++i])
	{
		tmp = ft_strjoin(p->path[i], "/");
		cmd = ft_strjoin(tmp, arg2);
		if (!access(cmd, 0))
			return (cmd);
		free(tmp);
		free(cmd);
	}
	return (NULL);
}

int	first_child(t_pipex p)
{
	dup2(p.fd[1], 1);
	close(p.fd[0]);
	dup2(p.infile, 0);
	close(p.fd[1]);
	p.second_arg = ft_split(p.cmd[0], 32);
	p.first_arg = get_mpath(&p, p.second_arg[0]);
	execve(p.first_arg, p.second_arg, p.env);
}

int	second_child(t_pipex p)
{
	dup2(p.fd[0], 0);
	close(p.fd[1]);
	dup2(p.outfile, 1);
	close(p.fd[0]);
	p.second_arg = ft_split(p.cmd[1], 32);
	p.first_arg = get_mpath(&p, p.second_arg[0]);
	execve(p.first_arg, p.second_arg, p.env);
}

void	do_it(t_pipex p)
{
	int		pid1;
	int		pid2;
	int		res1;
	int		res2;

	if (pipe(p.fd) == -1)
		error_msg("Pipe error !\n");
	pid1 = fork();
	if (pid1 == -1)
		error_msg("fork error !\n");
	if (pid1 == 0)
		res1 = first_child(p);
	if (res1 == -1)
		ft_printf("fuck");
	pid2 = fork();
	if (pid2 == -1)
		error_msg("fork error !\n");
	if (pid2 == 0)
		res2 = second_child(p);
	if (res2 == -1)
		ft_printf("fuck2");
}

void	free_everything(t_pipex *p)
=======
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
>>>>>>> Stashed changes
{
	t_pipex	pipex;
	int		fd;

<<<<<<< Updated upstream
	i = -1;
	while (p->path[++i])
		free(p->path[i]);
	free(p->path);
	free(p->cmd[0]);
	free(p->cmd[1]);
	free(p->cmd);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac < 5)
		return (0);
	init(&pipex, env, av, ac);
	do_it(pipex);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	free_everything(&pipex);
=======
	if (ac < 5)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		error_msg("Error opening file !!\n");
	close(fd);
	init(&pipex, ac, av, env);
	do_it(pipex);
	free_all(&pipex);
>>>>>>> Stashed changes
	return (0);
}
