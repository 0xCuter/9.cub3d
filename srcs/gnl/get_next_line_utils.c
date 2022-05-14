/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:20:05 by vvandenb          #+#    #+#             */
/*   Updated: 2021/12/13 12:01:34 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Returns the next line as a new string
// (Returns a NULL pointer if lines is a NULL pointer)
char	*get_line(char *lines)
{
	char	*line;
	int		line_len;

	if (lines == NULL)
		return (NULL);
	line_len = 0;
	while (lines[line_len] && lines[line_len] != '\n')
		++line_len;
	if (lines[line_len] == '\n')
		line = malloc((++line_len + 1) * sizeof(char));
	else
		line = malloc((line_len + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	line[line_len] = 0;
	while (line_len-- > 0)
		line[line_len] = lines[line_len];
	return (line);
}

// ft_strjoin auxilary function
// Copies the value of the strings "src" to "dest"
// Returns a pointer to the "dest"'s last copied char
static char	*copy_str(char *src, char *dest)
{
	while (*src)
	{
		*dest = *src;
		++src;
		++dest;
	}
	return (dest);
}

// Returns a new string resulting from the concatenation of "lines"
// to "line_read", and then frees "lines"
// (Returns "lines" if "line_read" is a NULL pointer)
char	*ft_strjoin_modified(char *lines, char *line_read)
{
	char	*lines_p;
	char	*line_read_p;
	char	*p;
	char	*rp;
	int		p_len;

	if (line_read == NULL)
		return ((char *) lines);
	p_len = 1;
	lines_p = (char *) lines;
	while (lines_p && *lines_p++)
		++p_len;
	line_read_p = (char *) line_read;
	while (*line_read_p++)
		++p_len;
	p = malloc(p_len * sizeof(char));
	if (p == NULL)
		return (NULL);
	rp = p;
	if (lines)
		p = copy_str((char *) lines, p);
	p = copy_str((char *) line_read, p);
	*p = 0;
	free(lines);
	return (rp);
}

// ft_substr auxilary function
static char	*ft_substr2(char *lines, char *rs, unsigned int start, int len)
{
	int	c;

	c = 0;
	while (c != len && lines[start + c])
	{
		rs[c] = lines[start + c];
		++c;
	}
	rs[c] = 0;
	free(lines);
	return (rs);
}

// Returns a new string copied from "lines" from "start" with a length of
// "len", and frees "lines"
// (Returns a NULL pointer if "lines" is a NULL pointer)
// (Returns an empty string if "start" is greater than "lines"'s length)
char	*ft_substr_modified(char *lines, unsigned int start, unsigned int len)
{
	char			*rs;
	unsigned int	s_len;

	s_len = ft_strlen_modified(lines);
	if (lines == NULL)
		return (NULL);
	if (len > s_len)
		len = s_len;
	if (start > s_len)
	{
		rs = malloc(sizeof(char));
		*rs = 0;
		free(lines);
		return (rs);
	}
	if (start + len > s_len)
		len = s_len - start;
	rs = malloc((len + 1) * sizeof(char));
	if (rs == NULL)
	{
		free(lines);
		return (NULL);
	}
	return (ft_substr2(lines, rs, start, len));
}
