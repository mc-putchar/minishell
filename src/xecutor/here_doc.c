/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:16:56 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/08 19:42:18 by mcutura          ###   ########.fr       */
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

static int	output_line(int fd, char **line, bool expand)
{
	char	*expanded;

	if (!expand)
	{
		if (ft_dprintf(fd, "%s\r\n", *line) > 0)
			return (EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
	expanded = arg_expansion(*line);
	if (!expanded)
		return (ft_dprintf(STDERR_FILENO, "%s: %s\n", MISH, strerror(errno)), \
			EXIT_FAILURE);
	if (ft_dprintf(fd, "%s\r\n", expanded) > 0)
		return (free(expanded), EXIT_SUCCESS);
	return (free(expanded), EXIT_FAILURE);
}

static void	here_doc_reader(int fd, char *token)
{
	char			*line;
	t_termios		term_backup;
	size_t const	toklen = ft_strlen(token);
	bool const		expand = !ft_memchr(token, '"', toklen);

	ft_bzero(&term_backup, sizeof(term_backup));
	setup_terminal(&term_backup);
	if (!expand)
		token = ft_strtrim(token, "\"");
	line = read_line("> ");
	while (line && ft_strncmp(line, token, toklen))
	{
		if (output_line(fd, &line, expand && \
			ft_memchr(line, '$', ft_strlen(line))))
			break ;
		free(line);
		line = read_line("> ");
	}
	free(line);
	if (!expand)
		free(token);
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
