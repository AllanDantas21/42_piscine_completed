/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldantas <aldantas@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 00:21:53 by aldantas          #+#    #+#             */
/*   Updated: 2026/02/12 23:53:28 by aldantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hexdump.h"

static void	ft_error(char *filename, char *err)
{
	write(2, "ft_hexdump: ", 12);
	while (*filename)
		write(2, filename++, 1);
	write(2, ": ", 2);
	while (*err)
		write(2, err++, 1);
	write(2, "\n", 1);
}

static size_t	get_all_bytes(char *file_name)
{
	int		fd;
	size_t	size;
	int		bytes_read;
	char	buffer[BUFFER_SIZE];

	fd = open(file_name, O_RDONLY);
	size = 0;
	if (fd == -1)
	{
		ft_error(file_name, strerror(errno));
		return (0);
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		size += bytes_read;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	close(fd);
	return (size);
}

static int	ft_hexdump(int argc, char *argv[])
{
	size_t	size;

	size = 0;
	if (argc == 2)
	{
		size = get_all_bytes(argv[1]);
		ft_hexdump_no_opt(argv[1], size);
	}
	if (argc == 3 && !ft_strcmp(argv[1], "-C"))
	{
		size = get_all_bytes(argv[2]);
		ft_hexdump_opt(argv[2], size);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc <= 1 || argc >= 4)
		return (write(2, "Error\n", 6), 0);
	ft_hexdump(argc, argv);
	return (0);
}
