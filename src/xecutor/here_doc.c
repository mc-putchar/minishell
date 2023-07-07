/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:16:56 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/07 06:13:27 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
** Create a unique path for the here_doc file checking if it already exists.
** If it exists, add next number to the end of the file name.
** @returns: allocated path to the here_doc file.
*/
static char	*create_here_doc_file(void)
{
	char	*path;
	t_ui	instance;
	char	*temp;

	instance = 0;
	temp = ft_itoa2(instance);
	path = ft_strjoin(HERE_DOC_FILE, temp);
	free(temp);
	while (!access(path, F_OK))
	{
		free(path);
		instance++;
		temp = ft_itoa2(instance);
		path = ft_strjoin(HERE_DOC_FILE, temp);
		free(temp);
	}
	return (path);
}

void	here_doc_reader(int fd, char *token)
{
	char			*line;
	t_termios		term_backup;
	bool const		expand = !ft_memchr(token, '"', ft_strlen(token));
	char			*delim;
	char			*tmp;

	ft_bzero(&term_backup, sizeof(term_backup));
	g_shell.term_backup = &term_backup;
	setup_terminal(&term_backup);
	if (!expand)
		delim = ft_strtrim(token, "\"");
	else
		delim = ft_strdup(token);
	line = read_line("> ");
	while (line && ft_strncmp(line, delim, ft_strlen(delim)))
	{
		if (expand && ft_memchr(line, '$', ft_strlen(line)))
		{
			tmp = arg_expansion(line);
			ft_dprintf(fd, "%s\r\n", tmp);
			free(tmp);
		}
		else
			ft_dprintf(fd, "%s\r\n", line);
		free(line);
		line = read_line("> ");
	}
	free(line);
	free(delim);
	reset_terminal(&term_backup);
}

/*
** Read from stdin until the delimiter is found.
** @param:		char *delimiter	- the delimiter to stop reading.
** @returns:	file descriptor to the here_doc file.
*/
int	here_doc(t_cmd *cmd)
{
	int				fd;
	int				ret;
	char			*path;

	path = create_here_doc_file();
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_dprintf(STDERR_FILENO, MISH": %s: %s\n",
				path, strerror(errno)), -1);
	here_doc_reader(fd, cmd->i_file);
	if (close(fd))
		ft_dprintf(STDERR_FILENO, MISH": %s: %s\n", path, strerror(errno));
	ret = open(path, O_RDONLY);
	if (ret == -1)
		ft_dprintf(STDERR_FILENO, MISH": %s: %s\n", path, strerror(errno));
	if (unlink(path))
		ft_dprintf(STDERR_FILENO, MISH": %s: %s\n", path, strerror(errno));
	free(path);
	return (ret);
}
