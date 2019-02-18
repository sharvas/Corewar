/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_dest_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:51:15 by erli              #+#    #+#             */
/*   Updated: 2019/02/18 13:57:46 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

static	void	asm_merge_path(char *filename, char *output_path, char *path)
{
	int		len_out;

	len_out = ft_strlen(output_path);
	ft_strcpy(path, output_path);
	if (path[len_out - 1] != '/')
	{
		path[len_out] = '/';
		path[len_out + 1] = '\0';
	}
	len_out = ft_strlen(path);
	ft_strncpy(path + len_out, filename,
		ft_strlen(filename) - 2);
	ft_strncpy(path + ft_strlen(path), ".cor", 5);
}

static	int		asm_fuse_other(char *filename, char *output_path, int len)
{
	int		fd;
	char	path[len + 4];

	ft_bzero(path, len + 4);
	asm_merge_path(filename, output_path, path);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Cannot write output file ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(".\n", 2);
		perror("asm");
		return (-1);
	}
	ft_putstr("Writing output program to ");
	ft_putstr(path);
	ft_putstr(".\n");
	return (fd);
}

static	int		asm_dest_other_path(char *file, char *output_path)
{
	char *filename;

	filename = ft_strrchr(file, '/');
	if (filename == 0)
		filename = file;
	else
		filename = filename + 1;
	return (asm_fuse_other(filename, output_path,
		ft_strlen(filename) + ft_strlen(output_path)));
}

int				asm_dest_path(char *file, int len, char *output_path)
{
	int		fd;
	char	path[len + 3];

	if (output_path != NULL)
		return (asm_dest_other_path(file, output_path));
	ft_strncpy(path, file, len - 2);
	ft_strncpy(path + len - 2, ".cor", 5);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Cannot write output file ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(".\n", 2);
		perror("asm");
		return (-1);
	}
	ft_putstr("Writing output program to ");
	ft_putstr(path);
	ft_putstr(".\n");
	return (fd);
}
