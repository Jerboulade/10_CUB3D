/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:02:05 by jcarere           #+#    #+#             */
/*   Updated: 2022/11/08 10:37:13 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../minilibx_macos/mlx.h"
# include "../libft/lib_includes/libft.h"
# include <math.h>
# include <errno.h>
# include <string.h>
/*
** MASK VALUE: TEXTURE
*/
# define NO 1
# define SO 2
# define EA 4
# define WE 8
# define FLOOR 16
# define CEILING 32
/*
** ERROR VALUE: PARSING
*/
# define ERR_USAGE 1
# define ERR_INVALID 2
# define ERR_NOFILE 3
# define ERR_INVALID_COLOR 4
# define ERR_DUP 5
# define ERR_MAP_EMPTY_LINE 6
# define ERR_INVALID_CHAR 7
# define ERR_MULT_SPAWN 8
# define ERR_INVALID_MAP 9
# define ERR_MISCONFIG 10
# define ERR_TEX_FORMAT 11
# define ERR_TEX_RES 12
/*
** PRINTABLE COLORS
*/
# define CYAN "\033[0;36m"
# define GREEN "\033[0;32m"
# define MAG "\033[0;35m"
# define RED "\033[0;31m"
# define ORANGE "\033[0;33m"
# define BG_ORANGE "\033[0;43m"
# define RESET "\033[0m"
# define WHITE 0X00FFFFFF
/*
** CONFIG
*/
# define WIN_W 1280
# define WIN_H 900
# define WIN_HH 450
# define RES 64
# define SPEED 0.2
# define ON_KEYDOWN 2
/*
** KEYS
*/
# define Z_KEY 13
# define Q_KEY 0
# define S_KEY 1
# define D_KEY 2
# define RIGHT_KEY 124
# define LEFT_KEY 123
# define SPACE 49
# define ESC_KEY 53

typedef struct s_image
{
	void		*ptr;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_image;

typedef struct s_vector2
{
	float		x;
	float		y;
}				t_vector2;

typedef struct s_ray
{
	t_vector2	pos;
	t_vector2	dir;
	t_vector2	size;
	t_vector2	delta;
	t_vector2	step;
	t_vector2	cast;
	char		hit_side;
	char		hit_door;
	int			col_h;
	int			col_start;
	int			col_end;
	float		dist;
	float		wall_x;
	t_vector2	tex;
	t_vector2	floor_dist;
	int			floor_x;
	int			floor_y;
}				t_ray;

typedef struct s_scene
{
	t_image		*proj;
	t_vector2	cam;
	t_vector2	dir;
	t_vector2	plan;
}				t_scene;

typedef struct s_texture
{
	char		mask;
	char		*no_path;
	char		*so_path;
	char		*ea_path;
	char		*we_path;
	char		*f_path;
	char		*c_path;
	char		*door_path;
	int			floor;
	int			ceiling;
}				t_texture;

typedef struct s_info
{
	int			line;
	int			col;
	char		spawn;
	char		**map;
	t_texture	*tx;
}				t_info;

typedef struct s_game
{
	t_list		*file;
	t_info		*info;
	void		*mlx_ptr;
	void		*win_ptr;
	t_scene		*scene;
	t_image		*bg;
	t_image		*shader;
	t_image		*shader_tex;
	t_image		*no_tex;
	t_image		*so_tex;
	t_image		*ea_tex;
	t_image		*we_tex;
	t_image		*c_tex;
	t_image		*f_tex;
	t_image		*door_tex;
	char		radar;
}				t_game;

/*
** main.c
*/
void	exit_free(t_game *game);
int		head(int ac, char **av);
int		main(int ac, char **av);
/*
** init.c
*/
t_list	*get_file(int fd, t_list *lst);
t_game	*init_game(int fd);
/*
** parse_file.c
*/
int		format_info_lines(t_list *node);
int		parse_file(t_game *game);
/*
** parse_info.c
*/
int		parse_color(t_game *game, char *sequence, int type);
int		set_texture(t_game *game, int type, char *cur_line, char *path);
int		check_duplicate_for_pretty_message(t_game *game, char *elem);
int		check_texture(t_game *game, char *cur_line, char **tab);
int		parse_info(t_game *game, char *cur_line);
/*
** parse_map.c
*/
void	built_map_tab(t_game *game, t_list *start, int i);
int		check_line_size(t_game *game, char *line);
void	remove_trailing_space(char *line);
int		parse_map(t_game *game, t_list *start);
/*
** check_map_config.c
*/
int		check_east_and_west_pos(char *line, int j, int len);
int		check_north_pos(t_game *game, int i, int j, int len);
int		check_south_pos(t_game *game, int i, int j, int len);
int		check_pos(t_game *game, int i, int j, int len);
int		check_map_config(t_game *game);
/*
** colors.c
*/
void	set_color(t_game *game, int color[3], int type);
int		tex_color(t_image *tex, int x, int y);
void	set_pixel_color(t_image *img, int x, int y, int color);
int		get_tex_color(t_game *game, t_ray *ray);
void	get_floor_pixel(t_game *game, t_ray *r, int x, int y);
/*
** render_params.c
*/
void	get_floor_dist(t_ray *r);
void	get_floor_coord(t_ray *ray, int y);
void	get_colomn_param(t_ray *r);
void	get_ray_size(t_ray *ray);
void	cast_ray(t_game *game, t_ray *ray);
/*
** raycast.c
*/
void	render_colomn(t_game *game, t_ray *r, int x);
void	ray_cast(t_game *game, int x);
void	render(t_game *g);
/*
** action.c
*/
int		detect_tile(t_game *game);
void	modify_detection(t_game *game, char new);
void	check_action(t_game *game);
void	print_action(t_game *game);
/*
** event.c
*/
void	move(t_game *game, float step_x, float step_y);
void	rotate(t_scene *pos, float speed);
int		event(int key, t_game *game);
/*
** init_images.c
*/
void	init_background(t_image *bg, int floor, int ceiling);
void	init_shader(t_image *shader);
t_image	*init_image(t_game *game);
t_image	*init_texture(t_game *game, char *path);
/*
** launch.c
*/
void	get_scene_start_coord(t_game *game);
void	get_scene_params(t_game *game);
int		prepare_images(t_game *g);
int		launch_scene(t_game *game);
/*
** tool.c
*/
void	set_vector(t_vector2 *vector, float x, float y);
int		print_error_map(t_game *game, int i_err, int j_err, int ret);
int		print_message(int ret);
int		print_error(char *object, int ret_val);
int		is_space_or_one(char c);
/*
** is_check.c
*/
int		is_spawn_char(char c);
int		is_valid_char(t_game *game, char c);
int		is_valid_color(int color[3]);
int		is_empty_line(char *line);
int		is_existing_texture(char *path);
/*
** free.c
*/
void	free_tab(char **tab);
void	free_texture(t_texture *tx);
void	free_map(t_info *info);
void	*free_game(t_game *game);
#endif
