/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:23:04 by bbresil           #+#    #+#             */
/*   Updated: 2023/10/25 20:36:46 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int		ft_putchar2(int c);
int		ft_strlen2(char *str);
int		ft_printf(const char *str, ...);
int		ft_putptr(unsigned long ptr, char *base, int option);
int		ft_putstr_fd2(char *s, int fd);
int		ft_format_converter(va_list args, char c);
int		ft_putnbr_base_u(unsigned int nbr, char *base);
int		ft_putnbr_base(int nbr, char *base);

#endif
