/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:22:16 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/31 14:33:57 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

//Structure representing a point with ints
typedef struct s_point {
	int	x;
	int	y;
}	t_point;

//Structure representing a point with floats
typedef struct s_fpoint {
	float	x;
	float	y;
}	t_fpoint;

//Structure representing an mlx image
typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_img;

//Structure representing a texture
typedef struct s_texture {
	t_img	img;
	t_point	size;
}	t_texture;

//utils_exit.c
//	Prints error with `perror(s)` and exits `exit(i)`
void	exit_perror(char *s, int i);
//	Prints error on `STDERR` and exits `exit(i)`
void	exit_error(char *s, int i);
//	Same as `exit_error()` but also closes `fd`
void	exit_close_error(char *s, int i, int fd);

//utils_math.c
//	Returns the distance between two points
float	distance(t_fpoint *p1, t_fpoint *p2);
//	"Fixes" an angle greater than 2PI or less than 0
void	fix_angle(float *angle);

//utils.c
//	Same as `open()`, but exits on error
int		safe_open(char *file_name, int flags);
//	Same as `close()`, but exits on error
void	safe_close(int fd);
//	Checks if a string is all spaces
int		str_isspace(char *str);
//	Frees a two-dimensional array
void	free_tab(char **tab);

#endif
