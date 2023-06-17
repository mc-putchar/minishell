/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:34:01 by dlu               #+#    #+#             */
/*   Updated: 2023/06/08 09:31:01 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Free the buffer and update with prev with replacement. */
static char	*update_prev(char **prev, char *replace, char **buffer)
{
	if (*buffer != NULL)
	{
		free(*buffer);
		*buffer = NULL;
	}
	if (*prev != NULL)
	{
		free(*prev);
		*prev = replace;
	}
	return (*prev);
}

/* Return the next line, and update the prev to next byte (both copy and free).
 * Prev str has to include a '\n' at index, unless it's at the end.
 * Return NULL if any malloc fails, with all allocated resources freed. */
static char	*process_prev(char **prev, int index, int end, char **buffer)
{
	char	*line;
	char	*tmp;

	if (end && !ft_strlen(*prev))
		return (update_prev(prev, NULL, buffer));
	if ((*prev)[index] == '\n')
	{
		line = ft_substr(*prev, 0, index + 1);
		tmp = ft_substr(*prev, index + 1, ft_strlen(*prev) - index - 1);
		update_prev(prev, tmp, buffer);
		if (!tmp)
			return (free(line), free(*buffer), NULL);
	}
	else
	{
		line = ft_substr(*prev, 0, index);
		update_prev(prev, NULL, buffer);
	}
	if (!line)
		return (update_prev(prev, NULL, buffer));
	return (line);
}

/* Process next line overhead, protect against faulty BUFFER_SIZE (0). */
static char	*process_next_line(int fd, char **prev)
{
	ssize_t	read_bytes;
	char	*buffer;

	buffer = (char *) malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer)
		return (update_prev(prev, NULL, &buffer));
	while (nl_index(*prev, 0) < 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (!append_buffer(prev, buffer, read_bytes))
			return (update_prev(prev, NULL, &buffer));
		if (read_bytes < BUFFER_SIZE)
			return (process_prev(prev, nl_index(*prev, 1), 1, &buffer));
	}
	return (process_prev(prev, nl_index(*prev, 0), 0, &buffer));
}

/* Get the next line of a file descriptor. */
char	*get_next_line(int fd)
{
	static char	*prev;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!prev)
	{
		prev = (char *) malloc(sizeof(char));
		if (!prev)
			return (NULL);
		prev[0] = '\0';
	}
	return (process_next_line(fd, &prev));
}
