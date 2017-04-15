/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_objects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 05:39:28 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/14 15:19:53 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static void		release_shaders(GLuint program, int count, t_gl_shader *shaders)
{
	int		i;

	i = 0;
	while (i < count)
	{
		glDetachShader(program, shaders[i].id);
		glDeleteShader(shaders[i].id);
		i++;
	}
}

static GLuint	gl_link_info(GLuint program)
{
	int		success;
	char	*log_info;
	GLint	size;

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);
		log_info = ft_malloc(size + 1);
		glGetProgramInfoLog(program, size, NULL, log_info);
		ft_printf("Error linking program\n%s", log_info);
		ft_free(log_info);
		return (0);
	}
	return (program);
}

void			validate(GLuint program)
{
	char	*log_info;
	GLint	size;

	glValidateProgram(program);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);
	log_info = ft_malloc(size + 1);
	glGetProgramInfoLog(program, size, NULL, log_info);
	ft_printf("program validation :\n%s", log_info);
	ft_free(log_info);
}

GLuint			create_program(int shader_count, t_gl_shader *shaders)
{
	GLuint	program;
	int		i;
	int		success;

	i = 0;
	program = glCreateProgram();
	while (i < shader_count)
	{
		success = compile_shader(&shaders[i]);
		if (!success)
		{
			release_shaders(program, i, shaders);
			glDeleteProgram(program);
			return (0);
		}
		glAttachShader(program, shaders[i].id);
		i++;
	}
	glLinkProgram(program);
	release_shaders(program, shader_count, shaders);
	return (gl_link_info(program));
}
