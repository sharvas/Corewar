/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:50:33 by erli              #+#    #+#             */
/*   Updated: 2019/02/18 14:19:01 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static	int	asm_check_file(char *file, int *fd)
{
	int	len;

	if (file == 0)
		return (-1);
	len = ft_strlen(file);
	if (len < 3 || ft_strcmp(file + len - 2, ".s") != 0)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(" has an incorrect format,", 2);
		return (ft_msg_int(2, " <sourcefile.s> format needed.\n", -1));
	}
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		ft_putstr_fd("Cannot read source file ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(".\n", 2);
		perror("asm");
		return (-1);
	}
	return (1);
}

static	int	asm_get_options(char *options, int argc, char **argv, char **output)
{
	int	a;
	int	i;

	a = 0;
	i = 1;
	while (i < argc && argv[i][a++] == '-')
	{
		while (argv[i][a] != '\0')
		{
			if (argv[i][a] == 'c')
				*options = (*options | 1);
			else if (argv[i][a] == 'o')
				*options = (*options | 2);
			else
				return (ft_msg_int(2, "Wrong options.\n", argc));
			a++;
		}
		a = 0;
		i++;
	}
	if ((*options & 2) == 2 && i < argc)
		*output = argv[i++];
	return (i);
}

int			main(int argc, char **argv)
{
	int		i;
	int		fd;
	char	options;
	char	*output;

	output = NULL;
	options = 0;
	if (B_SIZE < 2)
		return (ft_msg_int(2, "Error, MEM_SIZE must at least be 12\n", 0));
	if (argc == 1)
		return (ft_msg_int(1, "Usage : ./asm <sourcefile.s>\n", 0));
	i = asm_get_options(&options, argc, argv, &output);
	if (i >= argc)
		return (ft_msg_int(1, "Usage : ./asm -c/o <dest> <sourcefile.s>\n", 0));
	while (i < argc)
	{
		if (asm_check_file(argv[i], &fd) > 0)
		{
			asm_assemble(fd, argv[i], options, output);
			close(fd);
		}
		i++;
	}
	return (0);
}
