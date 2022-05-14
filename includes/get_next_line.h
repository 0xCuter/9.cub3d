/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:20:02 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/11 15:14:37 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

char			*get_next_line(int fd);

char			*get_line(char *lines);
char			*ft_strjoin_modified(char *s1, char *s2);
char			*ft_substr_modified(char *s, unsigned int start,
					unsigned int len);
unsigned int	ft_strlen_modified(const char *s);

#endif
