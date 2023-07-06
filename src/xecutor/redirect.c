/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:33:59 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/06 04:51:43 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_in(t_cmd *cmd)
{
	int		fd;

	if (cmd->i_type == REDIR_IN)
		fd = open(cmd->i_file, O_RDONLY);
	else if (cmd->i_type == HERE_DOC)
		fd = redirect_here(cmd);
	else
		return (EXIT_FAILURE);
	if (fd == -1)
		return (EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (EXIT_FAILURE);
	(void)close(fd);
	return (EXIT_SUCCESS);
}

int	redirect_out(t_cmd *cmd)
{
	int		fd;

	if (cmd->o_type == REDIR_OUT)
		fd = open(cmd->o_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->o_type == APPEND)
		fd = open(cmd->o_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (EXIT_FAILURE);
	if (fd == -1)
		return (EXIT_FAILURE);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (EXIT_FAILURE);
	(void)close(fd);
	return (EXIT_SUCCESS);
}

int	redirect_here(t_cmd *cmd)
{
	int		fd;
	size_t	len;
	char	*line;

	fd = open(HERE_DOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (fd);
	len = ft_strlen(cmd->i_file);
	line = get_delim(STDIN_FILENO, '\n');
	while (ft_strncmp(line, cmd->i_file, len))
	{
		ft_dprintf(fd, "%s\n", line);
		free(line);
		line = get_delim(STDIN_FILENO, '\n');
	}
	free(line);
	close(fd);
	fd = open(HERE_DOC_FILE, O_RDONLY);
	unlink(HERE_DOC_FILE);
	return (fd);
}
