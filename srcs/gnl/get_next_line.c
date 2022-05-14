/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:20:07 by vvandenb          #+#    #+#             */
/*   Updated: 2021/12/15 11:03:28 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Returns a string's length
// (Returns -1 if given a NULL pointer)
unsigned int	ft_strlen_modified(const char *s)
{
	int	c;

	if (s == NULL)
		return (-1);
	c = 0;
	while (*s++)
		++c;
	return (c);
}

// Allocates and sets memory to 0
static void	*ft_calloc(int count, int size)
{
	void	*array;
	char	*p;
	int		size_total;

	size_total = count * size;
	array = malloc(size_total);
	if (array == NULL)
		return (NULL);
	p = (char *) array;
	while (size_total)
	{
		*p = 0;
		++p;
		--size_total;
	}
	return (array);
}

// Returns the index of the first occurence of a newline, or the string's
// length if a newline is not found
// (Returns -1 if given a NULL pointer)
static unsigned int	ft_str_nl(const char *s)
{
	unsigned int	c;

	if (s == NULL)
		return (-1);
	c = 0;
	while (s[c])
	{
		if (s[c] == '\n')
			return (c);
		++c;
	}
	return (c);
}

// Reads from "fd" and appends to "lines" until a newline is read
// or until "read" reaches the end of "fd"
// Returns the last "read" value
static int	read_next_line(char **lines, int fd, int r)
{
	char		*line_read;

	while (r > 0 && ft_str_nl(*lines) == ft_strlen_modified(*lines))
	{
		line_read = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (line_read == NULL)
			return (-1);
		r = read(fd, line_read, BUFFER_SIZE);
		*lines = ft_strjoin_modified(*lines, line_read);
		free(line_read);
		if (*lines == NULL)
			return (-1);
	}
	return (r);
}

// Main function
char	*get_next_line(int fd)
{
	static char	*lines = NULL;
	int			r;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	r = read_next_line(&lines, fd, BUFFER_SIZE);
	if (r < 0 || lines == NULL || lines[0] == 0)
	{
		free(lines);
		lines = NULL;
		return (NULL);
	}
	line = get_line(lines);
	lines = ft_substr_modified(lines, ft_str_nl(lines) + 1,
			ft_strlen_modified(lines));
	return (line);
}
