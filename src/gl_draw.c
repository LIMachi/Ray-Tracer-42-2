/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 07:44:37 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/14 15:19:24 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	init_shaders(GLuint vao, GLuint *program, char *vs, char *fs)
{
	t_gl_shader	*t;
	t_gl_shader	s;
	GLint		pos;
	int			n;

	t = NULL;
	n = 0;
	s = gl_shader(GL_VS, vs);
	ft_pushback((void **)&t, S_GLS, n++, &s);
	s = gl_shader(GL_FS, fs);
	ft_pushback((void **)&t, S_GLS, n++, &s);
	glBindVertexArray(vao);
	*program = create_program(n, t);
	pos = glGetAttribLocation(*program, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
	pos = glGetAttribLocation(*program, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat),
		(void*)(2 * sizeof(GLfloat)));
	pos = glGetAttribLocation(*program, "texcoord");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat),
		(void*)(5 * sizeof(GLfloat)));
	glBindVertexArray(0);
}

void	init_texture(GLuint vao, GLuint *tex, int w, int h)
{
	glBindVertexArray(vao);
	glGenTextures(1, tex);
	glBindTexture(GL_TEXTURE_2D, *tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, 0);
	glBindVertexArray(0);
}

void	init_vao(GLuint *vao)
{
	GLuint			vbo;
	GLuint			ebo;
	const GLuint	elems[] = {0, 1, 2, 2, 3, 0};
	const GLfloat	vertices[] = {
		-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f};

	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elems), elems, GL_STATIC_DRAW);
	glBindVertexArray(0);
}
