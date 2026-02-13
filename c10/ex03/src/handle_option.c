/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_option.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldantas <aldantas@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:49:04 by aldantas          #+#    #+#             */
/*   Updated: 2026/02/12 23:53:33 by aldantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hexdump.h"

static void	ft_print_address(unsigned long addr)
{
	const char	*hex = "0123456789abcdef";
	char		address[8];
	int			i;

	i = 7;
	while (i >= 0)
	{
		address[i] = hex[addr % 16];
		addr /= 16;
		i--;
	}
	i = 0;
	while (i < 8)
	{
		write(1, &address[i], 1);
		i++;
	}
	write(1, "  ", 2);
}

static void	ft_hex_content(unsigned char *addr, unsigned int limit)
{
	const char		*hex = "0123456789abcdef";
	unsigned int	i;

	i = 0;
	while (i < 16)
	{
		if (i < limit)
		{
			write(1, &hex[addr[i] / 16], 1);
			write(1, &hex[addr[i] % 16], 1);
			if (i == 7)
				write(1, "  ", 2);
			else
				write(1, " ", 1);
		}
		i++;
	}
	write(1, " ", 1);
}

static void	ft_print_chars(unsigned char *addr, unsigned int limit)
{
	unsigned int	i;

	i = 0;
	write(1, "|", 1);
	while (i < limit)
	{
		if (addr[i] >= 32 && addr[i] <= 126)
			write(1, &addr[i], 1);
		else
			write(1, ".", 1);
		i++;
	}
	write(1, "|", 1);
}

static unsigned int	adjust_limit(unsigned int i, unsigned int size)
{
	if (i + 16 > size)
		return (size - i);
	return (16);
}

void	ft_hexdump_opt(char *file_name, unsigned int size)
{
	char			addr[BUFFER_SIZE];
	int				fd;
	unsigned int	i;
	unsigned int	limit;

	fd = open(file_name, O_RDONLY);
	if (fd == -1 || size < 1)
		return ;
	i = 0;
	while (i < size)
	{
		if (read(fd, addr, BUFFER_SIZE) == -1)
		{
			close(fd);
			return ;
		}
		limit = adjust_limit(i, size);
		ft_print_address((unsigned long)i);
		ft_hex_content((unsigned char *)addr, limit);
		ft_print_chars((unsigned char *)addr, limit);
		write(1, "\n", 1);
		i += limit;
	}
	close(fd);
}
