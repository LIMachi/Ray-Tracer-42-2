/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_handler.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:35:24 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/14 15:53:12 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_HANDLER_H
# define GL_HANDLER_H

# include <rt_incs.h>

# define GL_M_SCALE		0
# define GL_M_TRANS		1
# define GL_M_CAM_ROT	2
# define GL_M_CAM_POS	3
# define GL_M_PROJ		4
# define GL_M_WVP		0x01
# define GL_M_VP		0x02
# define GL_M_WV		0x04
# define GL_M_WP		0x08
# define GL_M_W			0x10
# define GL_M_V			0x20

# define GL_IND_VB		0
# define GL_POS_VB		1
# define GL_NORMAL_VB	2
# define GL_TEX_VB		3
# define GL_WVP_VB		4
# define GL_WORLD_VB	5

/*
**	ratio is WIDTH / HEIGHT
*/

# define T_GL_S(x, y)	(t_gl_shader){0, x, y}
# define S_GLS			sizeof(t_gl_shader)
# define GL_AB			GL_ARRAY_BUFFER
# define GL_EAB			GL_ELEMENT_ARRAY_BUFFER
# define GL_VS			GL_VERTEX_SHADER
# define GL_FS			GL_FRAGMENT_SHADER

typedef struct			s_gl_shader
{
	GLuint	id;
	GLuint	type;
	char	*file;
}						t_gl_shader;

t_gl_shader				gl_shader(GLuint type, char *file);
GLuint					create_program(int shader_count, t_gl_shader *shaders);
int						compile_shader(t_gl_shader *shader);
void					gl_compile_log(GLuint shader, char *name);
void					validate(GLuint program);

#endif
