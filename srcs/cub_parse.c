/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 19:19:05 by sucho             #+#    #+#             */
/*   Updated: 2020/09/05 01:13:00 by sucho            ###   ########.fr       */
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

static void	cub_parse_res(t_cub *cub, char **temp)
{
	int i;

	char **color_temp;
	if ((char)temp[0][0] == 'R')
	{
		i = 0;
		cub->res_w = temp[1][i++] - '0';
		while(temp[1][i])
			cub->res_w = (cub->res_w * 10) + (temp[1][i++] - '0');
		i = 0;
		cub->res_h = temp[2][i++] - '0';
		while(temp[2][i])
			cub->res_h = (cub->res_h * 10) + (temp[2][i++] - '0');
	}
	else if ((char)temp[0][0] == 'S')
		cub->sprite_path = temp[1];
	else if ((char)temp[0][0] == 'F')
	{
		i = 0;
		color_temp = ft_split(temp[1],',');
		while (i < 3)
			cub->floor_color = cub->floor_color * 256 + ft_atoi(color_temp[i++]);
	}
	else if ((char)temp[0][0] == 'C')
	{	
		i = 0;
		color_temp = ft_split(temp[1],',');
		while (i < 3)
			cub->ceiling_color = cub->ceiling_color * 256 + ft_atoi(color_temp[i++]);
	}
}

static void	cub_parse_img(t_cub *cub, char **temp)
{
	if ((char)temp[0][0] == 'N')
		cub->no_path = temp[1];
	else if ((char)temp[0][0] == 'E')
		cub->ea_path = temp[1];
	else if ((char)temp[0][0] == 'W')
		cub->we_path = temp[1];
	else if ((char)temp[0][0] == 'S')
		cub->so_path = temp[1];
	else
	{
		printf("error detected");
		exit(0);
	}
}

static void	cub_parse_map(t_cub *cub, char **cub_temp)
{
	int i;
	int j;

	i = 0;
	char **temp;
	while (i < 8)
	{
		j = 0;
		temp = ft_split(cub_temp[i], ' ');
		if (ft_strlen(temp[j]) == 2)
		{
			cub_parse_img(cub, temp);
		}
		else 
		{
			cub_parse_res(cub, temp);
		}
		i++;
	}	
}

static int	cub_check_image_path(t_cub *cub, char **cub_temp)
{
	// no, so, we, ea, s, f, c
	int	i;
	i = 0;
	
	if (!((char)cub_temp[i++][0] == 'R'))
		return (0);
	if (!((char)cub_temp[i][0] == 'N' && (char)cub_temp[i++][1] == 'O'))
		return (0);
	if (!((char)cub_temp[i][0] == 'S' && (char)cub_temp[i++][1] == 'O'))
		return (0);
	if (!((char)cub_temp[i][0] == 'W' && (char)cub_temp[i++][1] == 'E'))
		return (0);
	if (!((char)cub_temp[i][0] == 'E' && (char)cub_temp[i++][1] == 'A'))
		return (0);
	if (!((char)cub_temp[i++][0] == 'S'))
		return (0);
	if (!((char)cub_temp[i++][0] == 'F'))
		return (0);
	if (!((char)cub_temp[i++][0] == 'C'))
		return (0);
	return (1);
}

void			cub_parse(t_cub *cub, char *path)
{
	char	*cub_oneline;
	char	**cub_temp;
	int		line_count;
	int		i;
	cub_oneline = read_map_oneline(path);
	cub_temp = ft_split(cub_oneline, '\n');

	if (!cub_check_image_path(cub, cub_temp))
	{
		printf("map parsing error\n");
		exit(0);
	}
	line_count = 0;
	while (cub_temp[line_count])
		line_count++;
	printf("line count: %d\n", line_count);
	cub_parse_map(cub, cub_temp);
	printf("%s\n",cub->no_path);
	printf("%s\n",cub->so_path);
	printf("%s\n",cub->ea_path);
	printf("%s\n",cub->we_path);
	printf("res: %d\t%d\n",cub->res_w, cub->res_h);
	printf("color: %x\t%x\n",cub->floor_color, cub->ceiling_color);
	line_count-=8;
	printf("line count: %d\n", line_count);
	i = 0;
	if (!(cub->map = (char **)malloc(sizeof(char *) * (line_count+1))))
		return ;
	while (i < line_count)
	{
		cub->map[i] = ft_strdup(cub_temp[i+8]);
		i++;
	}
	i = 0;
	while (i < line_count)
		printf("%s\n", cub->map[i++]);
	printf("map_count = %d\n", i);
	i = 0;
	while (cub->map[i])
		printf("%s\n", cub->map[i++]);
	printf("cub->map count = %d\n", i);

}
