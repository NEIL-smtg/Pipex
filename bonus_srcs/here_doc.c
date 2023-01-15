/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:13:57 by suchua            #+#    #+#             */
/*   Updated: 2023/01/15 17:18:03 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	process_line(char *line, char *limiter)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n' && len - 1 == ft_strlen(limiter))
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
			return (1);
	return (0);
}

void	handle_here_doc(t_pipex *p, int ac, char *limiter)
{
	int		fd;
	char	*line;

	if (ac < 6)
		error_msg("Lack of arguments for here_doc !\n");
	p->here_doc = 1;
	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd == -1)
		error_msg("Error opening .heredoc_tmp !!\n");
	while (1)
	{
		ft_printf("heredoc> ");
		line = get_next_line(0);
		if (process_line(line, limiter))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	p->infile = open(".heredoc_tmp", O_RDONLY);
	if (p->infile == -1)
		error_msg("Error opening infile !!\n");
}
