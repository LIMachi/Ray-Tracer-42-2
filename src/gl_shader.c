/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_shader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 07:48:53 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/04 07:48:54 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		gl_compile_log(GLuint shader, char *name)
{
	char	*log_info;
	GLint	size;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
	log_info = ft_malloc(size + 1);
	glGetShaderInfoLog(shader, size, NULL, log_info);
	ft_dprintf(2, "Error compiling shader ! source name : %s\nLog (%d):\n%s",
		name, size, log_info);
	ft_free(log_info);
}

int		compile_shader(t_gl_shader *shader)
{
	char	*source;
	GLuint	id;
	int		success;
	int		fd;

	if ((fd = open(shader->file, O_RDONLY)) == -1)
		return (-1);
	source = ft_readfile(fd);
	close(fd);
	id = glCreateShader(shader->type);
	shader->id = id;
	glShaderSource(id, 1, (const GLchar *const *)&source, NULL);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
		gl_compile_log(id, shader->file);
	return (success);
}

t_gl_shader	gl_shader(GLuint type, char *name)
{
	return ((t_gl_shader){0, type, name});
}
