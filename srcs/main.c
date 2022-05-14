/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:09:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/11 16:21:45 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_map(char *map_file, t_map *map)
{
	size_t	i;
	int		fd;
	char	*buf;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
	{
		perror("MAP");
		exit(fd);
	}
	buf = get_next_line(fd);
	map->len = ft_strlen(buf) - 1;
	map->img.img = mlx_new_image(map->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	map->img.addr = mlx_get_data_addr(map->img.img,
			&map->img.bits_per_pixel,
			&map->img.line_len,
			&map->img.endian);
	map->map = malloc((map->len * map->len) * sizeof(char));
	if (map == NULL)
		return;
	i = 0;
	while (buf)
	{
		ft_strlcpy(map->map + i, buf, map->len + 1);
		free(buf);
		buf = get_next_line(fd);
		i += map->len;
	}
}

static void	draw_map(t_map *map)
{
	size_t	i;
	size_t	j;
	char	value;
	int		color;

	i = 0;
	while (i < map->len)
	{
		j = 0;
		while (j < map->len)
		{
			value = map->map[j + i * map->len];
			if (value == '1')
				color = rgb(255, 0, 0);
			else
				color = rgb(255, 255, 255);
			img_pixel_put(&map->img, j, i, color);
			++j;
		}
		++i;
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img.img, 0, 0);
}

int	main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	map;

	if (argc == 2)
	{
		mlx_ptr = mlx_init();
		if (mlx_ptr == NULL)
			exit(-1);
		win_ptr = mlx_new_window(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "FdF");
		if (win_ptr == NULL)
			exit(-1);
		map.mlx_ptr = mlx_ptr;
		map.win_ptr = win_ptr;
		init_map(argv[1], &map);
		draw_map(&map);
		init_loop(mlx_ptr, win_ptr);
	}
	else if (argv && argv[0]) {
		printf("Usage: %s <map.cub3D>\n", argv[0]);
		exit(1);
	}
	return (0);
}
