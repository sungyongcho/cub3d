/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 19:19:05 by sucho             #+#    #+#             */
/*   Updated: 2020/09/04 16:56:01 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char 	*read_map_oneline(const char *path)
{
	char *map;
	char *line;
	int fd;

	fd = open(path,O_RDONLY);
	map = ft_strdup("");
	while (get_next_line(fd, &line)> 0)
	{
		map = ft_strjoin(map,line);
		map = ft_strjoin(map,"\n");
		free(line);
	}
	return (map);
}
static int	cub_check_image_path(t_cub *cub, char **cub_temp)
{
	// no, so, we, ea, s, f, c
	int	i;
	i = 0;

	if (!(ft_strchr(cub_temp[i++], "R")))
		return (0);
	if (!(ft_strchr(cub_temp[i++], "NO")))
		return (0);
	if (!(ft_strchr(cub_temp[i++], "SO")))
		return (0);
	if (!(ft_strchr(cub_temp[i++], "WE")))
		return (0);
	if (!(ft_strchr(cub_temp[i++], "EA")))
		return (0);
	if (!(ft_strchr(cub_temp[i++], "S")))
		return (0);
	if (!(ft_strchr(cub_temp[i++], "F")))
		return (0);
	if (!(ft_strchr(cub_temp[i++], "C")))
		return (0);
	return (1);
}
void			cub_parse(t_cub *cub, char *path)
{
	char	*cub_oneline;
	char	**cub_temp;
	cub_oneline = read_map_oneline(path);
	cub_temp = ft_split(cub_oneline, '\n');

	if (!cub_check_image_path(cub, cub_temp))
	{
		printf("map parsing error\n");
		exit(0);
	}
	int i = 0;
	while (cub_temp[i])
	{
		printf("%d\n",i++);
	}
}
