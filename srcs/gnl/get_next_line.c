/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:52:19 by scuter            #+#    #+#             */
/*   Updated: 2021/08/24 18:59:15 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*clean_stack(char *stack)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!stack)
		return (NULL);
	while (stack[i] && stack[i] != '\n')
		i++;
	if (!stack[i])
	{
		free(stack);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(stack) - i + 1));
	if (!str)
		return (NULL);
	i++;
	while (stack[i])
		str[j++] = stack[i++];
	str[j] = '\0';
	free(stack);
	return (str);
}

static char	*get_line(char *stack)
{
	char	*str;
	int		i;

	i = 0;
	if (!stack || stack[0] == 0)
		return (NULL);
	while (stack[i] && stack[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (stack[i] && stack[i] != '\n')
	{
		str[i] = stack[i];
		i++;
	}
	if (stack[i] == '\n')
	{
		str[i] = stack[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ret_line(char **stack)
{
	char			*line;

	line = get_line(*stack);
	*stack = clean_stack(*stack);
	if (line)
		return (line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		*stack;
	char			*buff;
	int				ret;

	ret = 1;
	if ((fd < 0 || fd > 255) || BUFFER_SIZE < 1)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (!has_newline(stack) && ret != 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[ret] = '\0';
		stack = str_join(stack, buff);
	}
	free(buff);
	return (ret_line(&stack));
}
